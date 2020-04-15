#ifndef DUNGEON_LOOP_H
#define DUNGEON_LOOP_H

#include <raylib.h>

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

  const float fps
  { 60.0f };

  const float multiplier
  { 100.0f };

  const float speed
  { 5.0f };

  const float velocity
  { multiplier*speed/fps };

  const float angle
  { 2.0f };

  const float theta
  { angle/fps };

  const float side
  { multiplier*1.0f };

  const float wrap
  { multiplier*20.0f };

  const float decay
  { 0.9f };

  const float sight
  { multiplier*20.0f };

  const Vector3 cube_dims
  { side, side, side };

  const float dist_min
  { multiplier*3.0f };

  const float dist_max
  { multiplier*20.0f };


  const bool m_randomode
  { false };

  const int m_cube_amount
  { 1000 };

  std::vector <Vector3> m_cube_positions;

  Vector3 m_cube_position
  { 0.0f, 0.0f, 0.0f };
  // { ranpos(rand, dist_min, dist_max) };

  const Camera m_camera;

public:
  dungeon_loop();

  void run();

  key_bindings(const float velocity,
               const float theta)
  noexcept;

};

#endif // DUNGEON_LOOP_H
