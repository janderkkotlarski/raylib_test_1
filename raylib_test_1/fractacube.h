#ifndef FRACTACUBE_H
#define FRACTACUBE_H

#include <vector>

#include "cube_type.h"
#include "vec_3_int.h"

class fractacube
{
private:
  const vec_3_int m_pos_int;

  const std::vector <std::vector <std::vector <bool>>> m_pattern
  // -3:
  { { {1, 1, 0, 1, 0, 1, 1},
      {1, 0, 0, 1, 0, 0, 1},
      {0, 0, 1, 1, 1, 0, 0},
      {1, 1, 1, 0, 1, 1, 1},
      {0, 0, 1, 1, 1, 0, 0},
      {1, 0, 0, 1, 0, 0, 1},
      {1, 1, 0, 1, 0, 1, 1} },
  // -2:
    { {1, 0, 0, 1, 0, 0, 1},
      {0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 1, 0, 0, 0},
      {1, 0, 1, 1, 1, 0, 1},
      {0, 0, 0, 1, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0},
      {1, 0, 0, 1, 0, 0, 1} },
  // -1:
    { {0, 0, 1, 1, 1, 0, 0},
      {0, 0, 0, 1, 0, 0, 0},
      {1, 0, 0, 0, 0, 0, 1},
      {1, 1, 0, 1, 0, 1, 1},
      {1, 0, 0, 0, 0, 0, 1},
      {0, 0, 0, 1, 0, 0, 0},
      {0, 0, 1, 1, 1, 0, 0} },
  // 0:
    { {1, 1, 1, 0, 1, 1, 1},
      {1, 0, 1, 1, 1, 0, 1},
      {1, 1, 0, 1, 0, 1, 1},
      {0, 1, 1, 0, 1, 1, 0},
      {1, 1, 0, 1, 0, 1, 1},
      {1, 0, 1, 1, 1, 0, 1},
      {1, 1, 1, 0, 1, 1, 1} },
  // 1:
    { {0, 0, 1, 1, 1, 0, 0},
      {0, 0, 0, 1, 0, 0, 0},
      {1, 0, 0, 0, 0, 0, 1},
      {1, 1, 0, 1, 0, 1, 1},
      {1, 0, 0, 0, 0, 0, 1},
      {0, 0, 0, 1, 0, 0, 0},
      {0, 0, 1, 1, 1, 0, 0} },
  // 2:
    { {1, 0, 0, 1, 0, 0, 1},
      {0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 1, 0, 0, 0},
      {1, 0, 1, 1, 1, 0, 1},
      {0, 0, 0, 1, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0},
      {1, 0, 0, 1, 0, 0, 1} },
    { {1, 1, 0, 1, 0, 1, 1},
      {1, 0, 0, 1, 0, 0, 1},
      {0, 0, 1, 1, 1, 0, 0},
      {1, 1, 1, 0, 1, 1, 1},
      {0, 0, 1, 1, 1, 0, 0},
      {1, 0, 0, 1, 0, 0, 1},
      {1, 1, 0, 1, 0, 1, 1} } };

  const int m_division
  { static_cast<int>(m_pattern.size()) };

  const int m_jumps
  { m_division - 1 };

  const float m_scale
  { 0.9f };

  cube_type m_type
  { cube_type::none };

public:
  fractacube(const int x, const int y, const int z,
                         const cube_type c_type)
  noexcept;

  void display(Vector3 &position,
               const Vector3 &forward,
               Color &cube_color,
               Color &edge_color,
               const float cam_angle,
               const float sight,
               const float decay,
               const float multiplier)
  noexcept;

  void display()
  noexcept;
};

float repos(const int pos, const int extra)
noexcept;

#endif // FRACTACUBE_H
