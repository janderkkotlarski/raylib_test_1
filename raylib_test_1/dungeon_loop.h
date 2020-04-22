#ifndef DUNGEON_LOOP_H
#define DUNGEON_LOOP_H

#include <vector>

#include <raylib.h>

#include "fractacube.h"
#include "action.h"

const int fps
{ 60 };

class dungeon_loop
{
private:
  bool m_test
  { true };

  Vector3 m_position
  { 0.0f, 0.0f, 0.0f };

  bool m_move
  { false };

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

  const float m_side
  { m_multiplier*1.0f };

  std::vector <Vector3> m_directions
  { {1.0f, 0.0f, 0.0f},
    {0.0f, -1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f} };

  const int m_dungeon_radius
  { 1 };

  const int m_dungeon_span
  { 2*m_dungeon_radius + 1};

  const float m_wrap
  { m_multiplier*(m_dungeon_radius + 0.5f) };

  const float m_decay
  { 0.9f };

  const int m_horizon
  { 3 };

  const float m_sight
  { float(m_horizon)*m_multiplier };

  Color m_cube_color
  { 127, 127, 127, 255};

  Color m_edge_color
  { 255, 255, 255, 255};

  const Vector3 m_cube_dims
  { m_side, m_side, m_side };

  const float m_dist_min
  { 3.0f*m_multiplier };

  const float m_dist_max
  { 20.0f*m_multiplier };

  std::vector <std::vector <std::vector <cube_type>>> m_type_volume;

  fractacube m_fracta_cube;

  const bool m_randomode
  { false };

  const int m_cube_amount
  { 1000 };

  Vector3 m_cube_pos
  { 1.0f, 0.0f, 1.0f };

  std::vector <Vector3> m_cube_positions;

  std::vector <fractacube> m_fracta_cubes;

  Vector3 m_cube_position
  { 0.0f, 0.0f, 0.0f };
  // { ranpos(rand, dist_min, dist_max) };

  Camera m_camera;

  const float m_cam_angle
  { 100.0f };

  const float m_cam_field
  { -0.001f };

  bool m_loop
  { true };

  float m_min_distance
  { -1.0f };

  Vector3 m_min_difference
  { -1.0f, 0.0f, 0.0f };

  bool m_display_info
  { true };

  const bool m_simple
  { true };

  void stereoscope_init()
  noexcept;

  void camera_init()
  noexcept;

  void dungeon_init()
  noexcept;

public:
  dungeon_loop()
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

  void info_display()
  noexcept;

  void infos()
  noexcept;

  void display_pos(const int pos_x,
                   const int pos_y,
                   const int pos_z)
  noexcept;

  void run();

};



#endif // DUNGEON_LOOP_H
