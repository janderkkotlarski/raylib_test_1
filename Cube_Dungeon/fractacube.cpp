#include "fractacube.h"

#include <cassert>
#include <iostream>

#include <raymath.h>

#include "misc_functions.h"
#include "raylib_functions.h"

fractacube::fractacube()
noexcept
  : m_cube_dims(vector_scale(std::vector <float>{ 1.0f, 1.0f, 1.0f }, m_scale/(float)m_division))
{
  assert(m_scale >= 0.49f &&
         m_scale <= 1.11f);
}

fractacube::fractacube(const int x, const int y, const int z,
                       const cube_type c_type)
noexcept
  : m_pos_int(std::vector <int>{x, y, z}), m_type(c_type),
    m_cube_dims(vector_scale(std::vector <float>{ 1.0f, 1.0f, 1.0f }, m_scale/(float)m_division))
{
  assert(m_scale >= 0.49f &&
         m_scale <= 1.01f);
}

void fractacube::set_pos_type(const int x, const int y, const int z,
                              const cube_type c_type)
noexcept
{
  m_pos_int = std::vector <int>{x, y, z};
  m_type = c_type;
}

void fractacube::display(Model &cube_model, Model &cube_model_dark,
                         const float &hale_scale)
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
          { float(m_division) };

          std::vector <float> sub_pos
          { factor*repos(count_x, extra),
            factor*repos(count_y, extra),
            factor*repos(count_z, extra) };

          const std::vector <float> pos_float;

          std::vector <float> cube_pos
          { vector_add(sub_pos, vector_int2float(m_pos_int)) };

          const Color setback_color
          { 0, 0, 0, 24 };

          if (m_type == cube_type::setback)
          { DrawCube(vector2vector3(cube_pos), m_cube_dims[0], m_cube_dims[1], m_cube_dims[2], setback_color); }
          else
          {
            // DrawCube(cube_pos, m_cube_dims.x, m_cube_dims.y, m_cube_dims.z, cube_color);
            DrawModel(cube_model, vector2vector3(cube_pos), hale_scale, Color{ 255, 255, 255, 63 });
            DrawModel(cube_model_dark, vector2vector3(cube_pos), hale_scale, WHITE);
          }
        }
      }
    }
  }
}

float repos(const int pos, const int extra)
noexcept
{ return float(pos) - float(extra)*0.5f; }
