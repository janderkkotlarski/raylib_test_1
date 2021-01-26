#ifndef DUNGEON_LOOP_H
#define DUNGEON_LOOP_H

#include <vector>
#include <cmath>

#include "raylib.h"
#include <raymath.h>
// #include <rlights.h>

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

  const Rectangle m_start_rect
  { 0.0f, 0.0f, 1.0f*m_screen_width, 1.0f*m_screen_height };

  const Color m_start_color
  { 0, 0, 0, 195 };

  const float m_period
  { 0.5f };

  const float m_change_period
  { 2.0f*m_period };

  const float m_transit_period
  { 4.0f*m_period };

  float m_time
  { 0.0f };

  float m_delta_time
  { GetFrameTime() };

  float m_total_time
  { 0.0f };

  float m_max_time
  { 4.0f };

  float m_cube_scale
  { 1.0f };

  const float m_speed
  { 1.0f/m_period };

  float m_velocity
  { m_speed*m_delta_time };

  const float m_angle
  { PI/(2.0f*m_period) };

  float m_theta
  { m_angle*m_delta_time };

  const std::vector <std::vector <float>> m_start_directs
  { {1.0f, 0.0f, 0.0f},
    {0.0f, -1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f} };

  int m_level
  { 0 };

  const int m_end_level
  { 10 };

  const int m_life_level
  { -100 };

  const int m_max_dungeon_radius
  { 49 };

  int m_dungeon_radius
  { 6 };

  float m_float_radius
  { (float)m_dungeon_radius };

  int m_dungeon_span
  { 2*m_dungeon_radius + 1};

  std::vector <std::vector <float>> m_directions
  { m_start_directs };

  std::vector <float> m_movement
  { 0.0f, 0.0f, 0.0f };

  std::vector <int> m_start_posint
  { 1, m_dungeon_radius, m_dungeon_radius };

  std::vector <float> m_position
  { vector_int2float(m_start_posint) };

  std::vector <int> m_pos_int
  { vector_float2int(m_position) };

  std::vector <float> m_destination
  { vector_add(m_position, m_movement) };

  std::vector <int> m_destint
  { vector_float2int(m_destination) };

  std::vector <int> m_coord_int
  { m_pos_int };

  std::vector <int> m_index_int
  { 0, 0, 0 };

  std::vector <int> m_next_pos_int
  { -1, -1, -1 };

  cube_type m_internal_type
  { cube_type::none };

  const int m_frames
  { 48 };

  int m_frame
  { 0 };

  unsigned m_cube_index
  { 0 };

  const unsigned char m_light_intensity
  { 63 };

  std::vector <float> m_ambient_profile
  { 0.2f, 0.2f, 0.2f, 1.0f };

  int m_fog_density_loc
  { 0 };

  int m_dark_density_loc
  { 0 };

  std::vector <float> m_cube_vein_profile
  { 0.5f, 0.0f, 1.0f, 1.0f };

  const float m_fog_density
  { 0.6f };

  const int m_horizon
  { 3 };

  const float m_dist_min
  { 3.0f };

  const float m_dist_max
  { 20.0f };

  std::vector <std::vector <std::vector <cube_type>>> m_type_volume;

  action m_act
  { action::none };

  cube_type m_collide_type
  { cube_type::none };

  cube_type m_hale_type
  { cube_type::none };

  std::vector <int> m_hale_index
  { 0, 0, 0 };

  int m_hale_sign
  { 0 };

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

  float m_dark_opacity
  { 0.0f };

  bool m_dark_up
  { true };

  const float m_cam_angle
  { 75.0f };

  const float m_cam_field
  { 0.1f };

  const bool m_synchro
  { false };

  bool m_game
  { true };

  bool m_loop
  { true };

  bool m_reset
  { false };

  const std::vector <std::vector <synchrogear>> m_music_tracks
  { music_tracks_generator() };

  unsigned m_track_index
  { 0 };

  const bool m_demo
  { true };

  const bool m_display_fps
  { true };

  const bool m_ez_mode
  { true };

  const bool m_developer
  { false };

  /// functions

  void camera_position(Camera &camera)
  noexcept;

  void camera_init(Camera &camera)
  noexcept;

  void level_init()
  noexcept;

  int dungeon_wrap(const int coord)
  noexcept;

  void perform_action()
  noexcept;

  void action_prep()
  noexcept;

  void action_start(std::vector <Sound> &track_samples)
  noexcept;

  void action_end()
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

  void cube_drawing(std::vector<Model> &cube_models,
                    std::vector<Model> &dark_models,
                    Model &model)
  noexcept;

  void coord_transform(const std::vector<int> &counters,
                       const int index)
  noexcept;

  void transition()
  noexcept;

  void cube_lighting()
  noexcept;

  void game_loop(Camera &camera, std::vector <Model> &cube_models, std::vector <Model> &dark_models,
                 Model &model,
                 std::vector <Shader> &fog_shaders, std::vector <Shader> &dark_shaders,
                 Shader &shader,
                 std::vector<Sound> &track_samples)
  noexcept;

public:

  dungeon_loop()
  noexcept;

  void run_window();
};



#endif // DUNGEON_LOOP_H
