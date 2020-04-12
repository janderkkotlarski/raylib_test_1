#include "fractacube.h"

fractacube::fractacube(const int x, const int y, const int z,
                       const cube_type c_type)
noexcept
  : m_pos_int(x, y, z), m_type(c_type)
{}
