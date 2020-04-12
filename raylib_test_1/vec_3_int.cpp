#include "vec_3_int.h"

vec_3_int::vec_3_int(const int x,
                     const int y,
                     const int z)
noexcept
  : m_x(x), m_y(y), m_z(z)
{}

vec_3_int::vec_3_int(const float x,
                     const float y,
                     const float z)
noexcept
  : m_x(x), m_y(y), m_z(z)
{}

vec_3_int::vec_3_int(const raylib::Vector3 &vec)
noexcept
  : m_x(round(vec.x)), m_y(round(vec.y)), m_z(round(vec.z))
{}



