#ifndef DUNGEON_LOOP_H
#define DUNGEON_LOOP_H

#include <vector>

#include <raylib.h>

#include "fractacube.h"

const int fps
{ 60 };

class dungeon_loop
{
private:
  Vector3 m_forward
  { 1.0f, 0.0f, 0.0f };

  Vector3 m_backward
  { -1.0f, 0.0f, 0.0f };

  Vector3 m_rightward
  { 0.0f, -1.0f, 0.0f };

  Vector3 m_leftward
  { 0.0f, 1.0f, 0.0f };

  Vector3 m_upward
  { 0.0f, 0.0f, 1.0f };

  Vector3 m_downward
  { 0.0f, 0.0f, -1.0f };

  Vector3 m_position
  { 0.0f, 0.0f, 0.0f };

  const float m_multiplier
  { 100.0f };

  const float m_speed
  { 1.0f };

  const float m_velocity
  { m_multiplier*m_speed/fps };

  const float m_angle
  { 2.0f };

  const float m_theta
  { m_angle/fps };

  const float m_side
  { m_multiplier*1.0f };

  const int m_dungeon_radius
  { 15 };

  const int m_dungeon_span
  { 2*m_dungeon_radius + 1};

  const float m_wrap
  { m_multiplier*(m_dungeon_radius + 0.5f) };

  const float m_decay
  { 0.2f };

  const int m_horizon
  { 2 };

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

  std::vector <Vector3> m_cube_positions;

  std::vector <fractacube> m_fracta_cubes;

  Vector3 m_cube_position
  { 0.0f, 0.0f, 0.0f };
  // { ranpos(rand, dist_min, dist_max) };

  Camera m_camera;

  const float m_cam_angle
  { 100.0f };

  const float m_cam_field
  { 0.3f };

  bool m_loop
  { true };

  float m_min_distance
  { -1.0f };

  Vector3 m_min_difference
  { -1.0f, 0.0f, 0.0f };

public:
  dungeon_loop()
  noexcept;

  void play_key_bindings()
  noexcept;

  void info_display()
  noexcept;

  void display_pos(const int pos_x,
                   const int pos_y,
                   const int pos_z)
  noexcept;

  void run();

};



#endif // DUNGEON_LOOP_H
