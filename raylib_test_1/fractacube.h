#ifndef FRACTACUBE_H
#define FRACTACUBE_H

#include <vector>

#include "cube_type.h"
#include "vec_3_int.h"

class fractacube
{
private:
  vec_3_int m_pos_int
  { 0, 0, 0};

  const std::vector <std::vector <std::vector <bool>>> m_pattern
  // -3: 29
  { { {1, 1, 0, 1, 0, 1, 1}, // 5
      {1, 0, 0, 1, 0, 0, 1}, // 3
      {0, 0, 1, 1, 1, 0, 0}, // 3
      {1, 1, 1, 1, 1, 1, 1}, // 6
      {0, 0, 1, 1, 1, 0, 0}, // 3
      {1, 0, 0, 1, 0, 0, 1}, // 3
      {1, 1, 0, 1, 0, 1, 1} }, // 5
  // -2: 9
    { {1, 0, 0, 1, 0, 0, 1}, // 3
      {0, 0, 0, 0, 0, 0, 0}, // 0
      {0, 0, 0, 0, 0, 0, 0}, // 0
      {1, 0, 0, 1, 0, 0, 1}, // 3
      {0, 0, 0, 0, 0, 0, 0}, // 0
      {0, 0, 0, 0, 0, 0, 0}, // 0
      {1, 0, 0, 1, 0, 0, 1} }, // 3
  // -1: 21
    { {0, 0, 1, 1, 1, 0, 0}, // 3
      {0, 0, 0, 0, 0, 0, 0}, // 0
      {1, 0, 1, 1, 1, 0, 1}, // 5
      {1, 0, 1, 1, 1, 0, 1}, // 5
      {1, 0, 1, 1, 1, 0, 1}, // 5
      {0, 0, 0, 0, 0, 0, 0}, // 0
      {0, 0, 1, 1, 1, 0, 0} }, // 3
  // 0: 36
    { {1, 1, 1, 1, 1, 1, 1}, // 7
      {1, 0, 0, 1, 0, 0, 1}, // 3
      {1, 0, 1, 1, 1, 0, 1}, // 5
      {1, 1, 1, 0, 1, 1, 1}, // 6
      {1, 0, 1, 1, 1, 0, 1}, // 5
      {1, 0, 0, 1, 0, 0, 1}, // 3
      {1, 1, 1, 1, 1, 1, 1} }, // 7
  // 1: 21
    { {0, 0, 1, 1, 1, 0, 0}, // 3
      {0, 0, 0, 0, 0, 0, 0}, // 0
      {1, 0, 1, 1, 1, 0, 1}, // 5
      {1, 0, 1, 1, 1, 0, 1}, // 5
      {1, 0, 1, 1, 1, 0, 1}, // 5
      {0, 0, 0, 0, 0, 0, 0}, // 0
      {0, 0, 1, 1, 1, 0, 0} }, // 3
  // 2: 9
    { {1, 0, 0, 1, 0, 0, 1}, // 3
      {0, 0, 0, 0, 0, 0, 0}, // 0
      {0, 0, 0, 0, 0, 0, 0}, // 0
      {1, 0, 0, 1, 0, 0, 1}, // 3
      {0, 0, 0, 0, 0, 0, 0}, // 0
      {0, 0, 0, 0, 0, 0, 0}, // 0
      {1, 0, 0, 1, 0, 0, 1} }, // 3
  // 3: 29
    { {1, 1, 0, 1, 0, 1, 1}, // 5
      {1, 0, 0, 1, 0, 0, 1}, // 3
      {0, 0, 1, 1, 1, 0, 0}, // 3
      {1, 1, 1, 1, 1, 1, 1}, // 7
      {0, 0, 1, 1, 1, 0, 0}, // 3
      {1, 0, 0, 1, 0, 0, 1}, // 3
      {1, 1, 0, 1, 0, 1, 1} } }; // 5 };

  const int m_division
  { static_cast<int>(m_pattern.size()) };

  const int m_jumps
  { m_division - 1 };

  const float m_scale
  { 0.9f };

  cube_type m_type
  { cube_type::none };

public:
  fractacube()
  noexcept;

  fractacube(const int x, const int y, const int z,
                         const cube_type c_type)
  noexcept;

  void set_pos_type(const int x, const int y, const int z,
                      const cube_type c_type)
  noexcept;

  Vector3 get_position()
  { return m_pos_int.get_Vector3(); }

  void display(Vector3 &position,
               const Vector3 &forward,
               Color &cube_color,
               Color &edge_color,
               const float cam_angle,
               const float sight,
               const float decay,
               const float multiplier)
  noexcept;
};

float repos(const int pos, const int extra)
noexcept;

#endif // FRACTACUBE_H
