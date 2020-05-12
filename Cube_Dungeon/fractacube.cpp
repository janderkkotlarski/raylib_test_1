#include "fractacube.h"

#include <cassert>
#include <iostream>

#include <raymath.h>

#include "misc_functions.h"

fractacube::fractacube(const float multiplier)
noexcept
  : m_multiplier(multiplier),
    m_cube_dims(Vector3Scale((Vector3){ 1.0f, 1.0f, 1.0f }, m_multiplier*m_scale/(float)m_division))
{
  assert(m_scale >= 0.49f &&
         m_scale <= 1.11f);

  assert(m_multiplier > 0.0f);
}

fractacube::fractacube(const int x, const int y, const int z,
                       const cube_type c_type,
                       const float multiplier)
noexcept
  : m_pos_int(x, y, z), m_type(c_type), m_multiplier(multiplier),
    m_cube_dims(Vector3Scale((Vector3){ 1.0f, 1.0f, 1.0f }, m_multiplier*m_scale/(float)m_division))
{
  assert(m_scale >= 0.49f &&
         m_scale <= 1.01f);

  assert(m_multiplier > 0.0f);
}

void fractacube::set_pos_type(const int x, const int y, const int z,
                              const cube_type c_type)
noexcept
{
  m_pos_int = vec_3_int{x, y, z};
  m_type = c_type;
}

void fractacube::display(Model &cube_model, Model &cube_model_dark,
                         const std::vector <float> &spectral_profile,
                         const std::vector <float> &chromatic_profile,
                         const Color &dark_color,
                         const float screen_opacity)
noexcept
{
  const int extra
  { m_division - 1 % 2 };  

  for (int count_x { 0 }; count_x < m_division; ++count_x)
  {
    for (int count_y { 0 }; count_y < m_division; ++count_y)
    {
      for (int count_z { 0 }; count_z < m_division; ++count_z)
      {
        if (m_pattern[count_x][count_y][count_z])
        {
          const float factor
          { m_multiplier/float(m_division) };

          Vector3 sub_pos
          { factor*repos(count_x, extra),
            factor*repos(count_y, extra),
            factor*repos(count_z, extra) };

          Vector3 cube_pos
          { Vector3Add(sub_pos, Vector3Scale(m_pos_int.get_Vector3(), m_multiplier)) };

          Color cube_color
          { type_color(cube_type::special, spectral_profile, chromatic_profile) };


          // scale_color(cube_color, 0.5f);

          if (m_type == cube_type::setback)
          { DrawCube(cube_pos, m_cube_dims.x, m_cube_dims.y, m_cube_dims.z, cube_color); }
          else
          {
            // DrawCube(cube_pos, m_cube_dims.x, m_cube_dims.y, m_cube_dims.z, cube_color);
            DrawModel(cube_model, cube_pos, m_dims_mult, WHITE);
            // DrawModel(cube_model_dark, cube_pos, m_scale, dark_color);
          }
        }
      }
    }
  }
}

float repos(const int pos, const int extra)
noexcept
{ return float(pos) - float(extra)*0.5f; }
