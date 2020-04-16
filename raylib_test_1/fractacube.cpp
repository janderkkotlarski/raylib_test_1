#include "fractacube.h"

#include <raymath.h>

#include "misc_functions.h"

fractacube::fractacube()
noexcept
{}

fractacube::fractacube(const int x, const int y, const int z,
                       const cube_type c_type)
noexcept
  : m_pos_int(x, y, z), m_type(c_type)
{}

void fractacube::set_pos_type(const int x, const int y, const int z,
                              const cube_type c_type)
noexcept
{
  m_pos_int = vec_3_int{x, y, z};
  m_type = c_type;
}

void fractacube::display(Vector3 &position,
                         const Vector3 &forward,
                         Color &cube_color,
                         Color &edge_color,
                         const float cam_angle,
                         const float sight,
                         const float decay,
                         const float multiplier)
noexcept
{
  const int edge
  { m_division / 2 };

  const int extra
  { m_division - 1 % 2 };

  /*
  for (int count_x { extra - edge}; count_x <= edge; ++count_x)
  {
    for (int count_y { extra - edge}; count_y <= edge; ++count_y)
    {
      for (int count_z { extra - edge}; count_z <= edge; ++count_z)
      {
        Vector3 sub_pos
        { float(count_x) - float(extra)*0.5f,
          float(count_y) - float(extra)*0.5f,
          float(count_z) - float(extra)*0.5f };

        Vector3 cube_pos
        { Vector3Add(sub_pos, m_pos_int.get_Vector3()) };

        const float side
        { multiplier*m_scale/float(m_division) };

        Vector3 cube_dims
        { side, side, side };

        display_cube(position, cube_pos, cube_dims, forward, cube_color, edge_color,
                     cam_angle, sight, decay, multiplier);

      }
    }
  }
  */

  for (int count_x { 0 }; count_x < m_division; ++count_x)
  {
    for (int count_y { 0 }; count_y < m_division; ++count_y)
    {
      for (int count_z { 0 }; count_z < m_division; ++count_z)
      {
        if (m_pattern[count_x][count_y][count_z])
        {
          const float factor
          { multiplier*m_scale/float(m_division) };

          Vector3 sub_pos
          { factor*repos(count_x, extra),
            factor*repos(count_y, extra),
            factor*repos(count_z, extra) };

          Vector3 cube_pos
          { Vector3Add(sub_pos, Vector3Scale(m_pos_int.get_Vector3(), multiplier)) };

          const float side
          { multiplier*m_scale*m_scale/float(m_division) };

          Vector3 cube_dims
          { side, side, side };

          display_cube(position, cube_pos, cube_dims,
                       cube_color, edge_color,
                       decay, multiplier);
        }

      }
    }
  }
}

float repos(const int pos, const int extra)
noexcept
{ return float(pos) - float(extra)*0.5f; }
