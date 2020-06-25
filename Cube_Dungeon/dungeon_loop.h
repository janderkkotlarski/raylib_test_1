#ifndef DUNGEON_LOOP_H
#define DUNGEON_LOOP_H

#include <vector>
#include <cmath>

#include <raylib.h>
#include <raymath.h>
#include <rlights.h>

#include "misc_functions.h"
#include "raylib_functions.h"
#include "fractacube.h"
#include "action.h"
#include "synchrogear.h"

#if defined(PLATFORM_DESKTOP)
  #define GLSL_VERSION            100
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
  #define GLSL_VERSION            330
#endif

const int fps
{ 10000 };

class dungeon_loop
{
private:

  /// parameters

  const int m_screen_width
  { 1200 };

  const int m_screen_height
  { 800 };

  const float m_period
  { 1.0f };

  float m_time
  { 0.0f };

  float m_delta_time
  { 0.5f };

  float m_hale_scale
  { 1.0f };

  const float m_speed
  { 1.0f*m_period };

  float m_velocity
  { m_speed*GetFrameTime() };

  const float m_angle
  { PI/(2.0f*m_period) };

  float m_theta
  { m_angle*GetFrameTime() };

  const std::vector <std::vector <float>> m_start_directs
  { {1.0f, 0.0f, 0.0f},
    {0.0f, -1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f} };

  int m_level
  { 0 };

  const int m_end_level
  { 10 };

  const int m_max_dungeon_radius
  { 99 };

  int m_dungeon_radius
  { 6 };

  unsigned m_dungeon_span
  { 2*(unsigned)m_dungeon_radius + 1};

  float m_wrap
  { m_dungeon_radius + 0.5f };

  int m_wall_perc
  { 40 };

  std::vector <std::vector <float>> m_directions
  { m_start_directs };

  std::vector <float> m_movement
  { 0.0f, 0.0f, 0.0f };

  std::vector <float> m_start_posit
  { 1.0f - (float)m_dungeon_radius, 0.0f, 0.0f };

  std::vector <float> m_position
  { m_start_posit };

  std::vector <int> m_pos_int
  { vector_float2int(m_position) };

  std::vector <int> m_coord_int
  { m_pos_int };

  std::vector <int> m_index_int
  { 0, 0, 0 };  

  std::vector <unsigned> m_dungeon_index
  { 0, 0, 0 };

  const std::vector <int> m_cube_pos
  { 2, 0, 0 };

  cube_type m_internal_type
  { cube_type::none };

  const int m_frames
  { 48 };

  int m_frame
  { 0 };

  unsigned m_cube_index
  { 0 };

  std::vector <std::vector <int>> m_collides_pos
  { m_pos_int, m_pos_int,
    m_pos_int, m_pos_int,
    m_pos_int, m_pos_int };

  std::vector <int> m_cube_dungeon_pos
  { m_cube_pos[0] + m_dungeon_radius,
    m_cube_pos[1] + m_dungeon_radius,
    m_cube_pos[2] + m_dungeon_radius };

  const unsigned char m_light_intensity
  { 63 };

  std::vector <float> m_ambient_profile
  { 0.2f, 0.2f, 10.0f, 1.0f };

  std::vector <float> m_rambient_profile
  { 10.0f, 0.2f, 0.2f, 1.0f };

  int m_fog_density_loc
  { 0 };

  int m_frog_density_loc
  { 0 };

  int m_dark_density_loc
  { 0 };

  std::vector <float> m_cube_vein_profile
  { 0.1f, 0.0f, 0.2f, 1.0f };

  const float m_fog_density
  { 0.3f };

  const int m_horizon
  { 4 };

  const float m_sight
  { float(m_horizon) };

  const float m_dist_min
  { 3.0f };

  const float m_dist_max
  { 20.0f };

  std::vector <std::vector <std::vector <cube_type>>> m_type_volume;

  action m_act
  { action::none };

  cube_type m_collide_type
  { cube_type::none };

  std::vector <unsigned> m_direction_shift
  { 0, 0, 0 };

  float m_screen_opacity
  { 0.0f };

  fractacube m_fracta_cube;

  std::vector <float> m_spectral_profile
  { 1.0f, 0.5f, 0.75f, 1.0f };

  std::vector <float> m_chromatic_profile
  { 1.0f, 0.75f, 0.5f, 1.0f };

  float m_candy_factor
  { 1.0f };

  bool m_candy_up
  { false };

  std::vector <float> m_dark_profile
  { 0.1f, 0.02f, 0.2f, 1.0f};

  Color m_dark_color
  { 15, 0, 31, 0 };

  float m_dark_opacity
  { 0.0f };

  bool m_dark_up
  { true };

  const float m_cam_angle_average
  { 75.0f };

  const float m_cam_angle_deviation
  { 70.0f };

  float m_cam_angle
  { m_cam_angle_average - 0.0f*m_cam_angle_deviation };

  const float m_cam_field
  { -0.001f };

  const bool m_synchro
  { false };

  bool m_game
  { true };

  bool m_loop
  { true };

  bool m_reset
  { false };

  bool m_test
  { false };

  bool m_display_info
  { false };

  const bool m_simple
  { false };

  std::vector <std::vector <int>> m_int_vectors;

  std::vector <int> m_int_dump
  { 0, 0, 0 };

  const std::vector <std::vector <synchrogear>> m_music_tracks
  { music_tracks_generator() };

  unsigned m_track_index
  { 0 };

  /// functions

  void camera_position(Camera &camera)
  noexcept;

  void camera_init(Camera &camera)
  noexcept;

  void player_init()
  noexcept;

  void level_init()
  noexcept;

  int dungeon_wrap(const int coord)
  noexcept;

  unsigned dungeon_warp(const int coord)
  noexcept;

  void perform_action()
  noexcept;

  int coordinator(const float pos)
  noexcept;

  std::vector <std::vector <int>> director()
  noexcept;

  void collide()
  noexcept;

  void play_actions(std::vector<Sound> &track_samples)
  noexcept;

  void other_actions()
  noexcept;

  void test_cheats()
  noexcept;

  void player_move(Camera &camera)
  noexcept;

  void infos()
  noexcept;

  void frame_update(std::vector <Model> &cube_models)
  noexcept;

  void cube_drawing(std::vector<Model> &cube_models,
                    std::vector<Model> &dark_models,
                    Model &model)
  noexcept;

  void coord_transform(const std::vector<int> &counters,
                       const int index)
  noexcept;

  void transition()
  noexcept;

  void game_loop(Camera &camera, std::vector <Model> &cube_models, std::vector <Model> &dark_models,
                 Model &model,
                 std::vector <Shader> &fog_shaders, std::vector <Shader> &dark_shaders,
                 Shader &shader,
                 const int fog_density_loc,
                 std::vector<Sound> &track_samples)
  noexcept;

public:

  dungeon_loop()
  noexcept;

  void run_window();
};



#endif // DUNGEON_LOOP_H
