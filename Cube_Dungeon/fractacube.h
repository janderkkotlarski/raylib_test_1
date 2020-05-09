#ifndef FRACTACUBE_H
#define FRACTACUBE_H

#include <vector>

#include <raylib.h>

#include "cube_type.h"
#include "vec_3_int.h"

class fractacube
{
private:
  vec_3_int m_pos_int
  { 0, 0, 0};

  const std::vector <std::vector <std::vector <bool>>> m_pattern
  { { {1} } }; // 2

  /*
  { { {1, 0, 1}, // 2
      {0, 1, 0}, // 1
      {1, 0, 1} }, // 1
  // -1: 5
    { {0, 1, 0}, // 1
      {1, 0, 1}, // 2
      {0, 1, 0} }, // 1
  // 0: 20
    { {1, 0, 1}, // 2
      {0, 1, 0}, // 1
      {1, 0, 1} } }; // 2
  */

  /*
  // -2: 13
  { { {1, 0, 1, 0, 1}, // 3
      {0, 0, 1, 0, 0}, // 1
      {1, 1, 1, 1, 1}, // 5
      {0, 0, 1, 0, 0}, // 1
      {1, 0, 1, 0, 1} }, // 3
  // -1: 5
    { {0, 0, 1, 0, 0}, // 1
      {0, 0, 0, 0, 0}, // 0
      {1, 0, 1, 0, 1}, // 3
      {0, 0, 0, 0, 0}, // 0
      {0, 0, 1, 0, 0} }, // 1
  // 0: 20
    { {1, 1, 1, 1, 1}, // 5
      {1, 0, 1, 0, 1}, // 3
      {1, 1, 0, 1, 1}, // 4
      {1, 0, 1, 0, 1}, // 3
      {1, 1, 1, 1, 1} }, // 5
  // 1: 5
    { {0, 0, 1, 0, 0}, // 1
      {0, 0, 0, 0, 0}, // 0
      {1, 0, 1, 0, 1}, // 5
      {0, 0, 0, 0, 0}, // 0
      {0, 0, 1, 0, 0} }, // 1
  // 2: 13
    { {1, 0, 1, 0, 1}, // 3
      {0, 0, 1, 0, 0}, // 1
      {1, 1, 1, 1, 1}, // 5
      {0, 0, 1, 0, 0}, // 1
      {1, 0, 1, 0, 1} } }; // 3
  */

  /*
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

   */

  const int m_division
  { (int)(m_pattern.size()) };

  const int m_jumps
  { m_division - 1 };

  const float m_scale
  { 1.0f };

  cube_type m_type
  { cube_type::none };

  const float m_multiplier;

  const float m_dims_mult
  { 1.0f };

  const Vector3 m_cube_dims;

public:
  fractacube(const float multiplier)
  noexcept;

  fractacube(const int x, const int y, const int z,
             const cube_type c_type,
             const float multiplier)
  noexcept;

  Vector3 get_position()
  const noexcept
  { return m_pos_int.get_Vector3(); }

  Vector3 get_cube_dims()
  const noexcept
  { return m_cube_dims; }

  void set_pos_type(const int x, const int y, const int z,
                      const cube_type c_type)
  noexcept;

  void display(Model &cube_model, Model &cube_model_dark,
               const std::vector<float> &spectral_profile,
               const std::vector<float> &chromatic_profile,
               const Color &dark_color,
               const float screen_opacity)
  noexcept;
};

float repos(const int pos, const int extra)
noexcept;

#endif // FRACTACUBE_H
