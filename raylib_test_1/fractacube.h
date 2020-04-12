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
  { { {1, 0, 1},
      {0, 1, 0},
      {1, 0, 1} },
    { {0, 1, 0},
      {1, 0, 1},
      {0, 1, 0} },
    { {1, 0, 1},
      {0, 1, 0},
      {1, 0, 1} } };

  const int m_division
  { static_cast<int>(m_pattern.size()) };

  const float m_scale
  { 0.9f };

  cube_type m_type
  { cube_type::none };

public:
  fractacube(const int x, const int y, const int z,
             const cube_type c_type)
  noexcept;
};

#endif // FRACTACUBE_H
