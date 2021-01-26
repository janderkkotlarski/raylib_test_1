#ifndef FRACTACUBE_H
#define FRACTACUBE_H

#include <vector>

#include "raylib.h"

#include "cube_type.h"
#include "misc_functions.h"

class fractacube
{
private:
  std::vector <int> m_pos_int
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

  const float m_dims_mult
  { 1.0f };

  const std::vector <float> m_cube_dims;

public:
  fractacube()
  noexcept;

  fractacube(const int x, const int y, const int z,
             const cube_type c_type)
  noexcept;

  std::vector <float> get_position()
  const noexcept
  { return vector_int2float(m_pos_int); }

  std::vector <float> get_cube_dims()
  const noexcept
  { return m_cube_dims; }

  void set_pos_type(const int x, const int y, const int z,
                    const cube_type c_type)
  noexcept;

  void display(Model &cube_model, Model &cube_model_dark,
               const float &hale_scale)
  noexcept;
};

float repos(const int pos, const int extra)
noexcept;

#endif // FRACTACUBE_H
