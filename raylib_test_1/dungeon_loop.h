#ifndef DUNGEON_LOOP_H
#define DUNGEON_LOOP_H

#include <vector>

#include <raylib.h>

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
  { 5.0f };

  const float m_velocity
  { m_multiplier*m_speed/fps };

  const float m_angle
  { 2.0f };

  const float m_theta
  { m_angle/fps };

  const float m_side
  { m_multiplier*1.0f };

  const int m_dungeon_radius
  { 10 };

  const float m_wrap
  { m_multiplier*(m_dungeon_radius + 0.5f) };

  const float m_decay
  { 0.6f };

  const float m_sight
  { m_multiplier*20.0f };

  Color m_cube_color
  { 127, 127, 127, 255};

  Color m_edge_color
  { 255, 255, 255, 255};

  const Vector3 m_cube_dims
  { m_side, m_side, m_side };

  const float m_dist_min
  { m_multiplier*3.0f };

  const float m_dist_max
  { m_multiplier*20.0f };

  const bool m_randomode
  { true };

  const int m_cube_amount
  { 1000 };

  std::vector <Vector3> m_cube_positions;

  Vector3 m_cube_position
  { 0.0f, 0.0f, 0.0f };
  // { ranpos(rand, dist_min, dist_max) };

  Camera m_camera;

  const float m_cam_angle
  { 100.0f };

  const float m_cam_field
  { -0.00001f };

  bool m_loop
  { true };

public:
  dungeon_loop()
  noexcept;

  void play_key_bindings()
  noexcept;

  void info_display()
  noexcept;

  void run();

};



#endif // DUNGEON_LOOP_H
