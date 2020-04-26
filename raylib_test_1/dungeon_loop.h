#ifndef DUNGEON_LOOP_H
#define DUNGEON_LOOP_H

#include <vector>
#include <cmath>

#include <raylib.h>
#include <raymath.h>
#include <rlights.h>

#include "fractacube.h"
#include "action.h"

#if defined(PLATFORM_DESKTOP)
  #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
  #define GLSL_VERSION            100
#endif

const int fps
{ 60 };

class dungeon_loop
{
private:

  /// parameters

  const int m_screen_width
  { 1200 };

  const int m_screen_height
  { 600 };

  action m_act
  { action::none };

  const float m_period
  { 0.5f };

  float m_time
  { 0.0f };

  float m_delta_time
  { 1.0f };

  const float m_multiplier
  { 100.0f };

  const float m_speed
  { 1.0f*m_multiplier/m_period };

  float m_velocity
  { m_speed*GetFrameTime() };

  const float m_angle
  { PI/(2.0f*m_period) };

  float m_theta
  { m_angle*GetFrameTime() };

  const std::vector <Vector3> m_start_directs
  { {1.0f, 0.0f, 0.0f},
    {0.0f, -1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f} };

  const int m_dungeon_radius
  { 10 };

  const int m_free
  { 2 };

  std::vector <Vector3> m_directions
  { m_start_directs };

  const Vector3 m_start_posit
  { 1.0f - (float)m_dungeon_radius, 0.0f, 0.0f };

  Vector3 m_position
  { Vector3Scale(m_start_posit, m_multiplier) };

  std::vector <int> m_pos_int
  { pos_intifier() };

  std::vector <int> m_coord_int
  { m_pos_int };

  std::vector <int> m_index_int
  { 0, 0, 0 };  

  std::vector <unsigned> m_dungeon_index
  { 0, 0, 0 };

  const std::vector <int> m_cube_pos
  { 2, 0, 0 };

  std::vector <std::vector <int>> m_collides_pos
  { m_pos_int, m_pos_int,
    m_pos_int, m_pos_int,
    m_pos_int, m_pos_int };

  std::vector <int> m_cube_dungeon_pos
  { m_cube_pos[0] + m_dungeon_radius,
    m_cube_pos[1] + m_dungeon_radius,
    m_cube_pos[2] + m_dungeon_radius };

  const int m_dungeon_span
  { 2*m_dungeon_radius + 1};

  const float m_wrap
  { m_multiplier*(m_dungeon_radius + 0.5f) };

  const float m_decay
  { 0.5f };

  const float m_fog_color[4]
  { 0.0f, 0.0f, 0.0f, 1.0f };

  const float m_fog_density
  { 0.005f };

  const int m_horizon
  { 4 };

  const float m_sight
  { float(m_horizon)*m_multiplier };

  const float m_dist_min
  { 3.0f*m_multiplier };

  const float m_dist_max
  { 20.0f*m_multiplier };

  std::vector <std::vector <std::vector <cube_type>>> m_type_volume;

  cube_type m_collide_type
  { cube_type::none };

  float m_screen_opacity
  { 0.0f };

  const int m_wall_perc
  { 1*60 };

  fractacube m_fracta_cube;

  Vector3 m_spectral_profile
  { 1.0f, 0.5f, 0.75f };

  Vector3 m_chromal_profile
  { 1.0f, 0.75f, 0.5f };

  Vector3 m_dark_profile
  { 0.1f, 0.02f, 0.2f};

  const float m_cam_angle
  { 100.0f };

  const float m_cam_field
  { -0.001f };

  bool m_game
  { true };

  bool m_loop
  { true };

  bool m_test
  { false };

  bool m_display_info
  { false };

  const bool m_simple
  { false };

  std::vector <std::vector <int>> m_int_vectors;

  std::vector <int> m_int_dump
  { 0, 0, 0 };

  /// functions
  ///

  std::vector <int> pos_intifier()
  noexcept;

  void stereoscope_init(Shader &distortion)
  noexcept;

  void fog_init(Model &cube_model,
                Shader &fogger,
                const int fog_density_loc)
  noexcept;

  void camera_init(Camera &camera)
  noexcept;

  void dungeon_init()
  noexcept;

  void dungeon_fill()
  noexcept;

  void begin_end()
  noexcept;

  int dungeon_wrap(const int coord)
  noexcept;

  int dungeon_warp(const int coord)
  noexcept;

  void movetate()
  noexcept;

  int coordinator(const float pos)
  noexcept;

  std::vector <std::vector <int>> director()
  noexcept;

  void collide()
  noexcept;

  void play_actions()
  noexcept;

  void other_actions()
  noexcept;

  void player_move(Camera &camera,
                   Shader &fogger,
                   const int fog_density_loc)
  noexcept;

  void infos()
  noexcept;

  void pos_direct_display()
  noexcept;

  void cube_drawing(Model &cube_model)
  noexcept;

  void coord_transform(const std::vector<int> &counters,
                       const int index)
  noexcept;

  void game_loop(Camera &camera, Model &cube_model, Shader &fogger, Light &light, const int fog_density_loc)
  noexcept;

public:
  dungeon_loop()
  noexcept;

  void run_window();
};



#endif // DUNGEON_LOOP_H
