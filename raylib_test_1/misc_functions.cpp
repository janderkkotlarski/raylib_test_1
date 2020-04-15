#include "misc_functions.h"

#include <cmath>

#include <raymath.h>

std::vector <std::string> vector3_to_strings(const Vector3 &vec)
noexcept
{
  std::vector <std::string> strings;

  strings.push_back(std::to_string(vec.x));
  strings.push_back(std::to_string(vec.y));
  strings.push_back(std::to_string(vec.z));

  return strings;
}

void rotate_first_second(Vector3 &first,
                         Vector3 &second,
                         Vector3 &inv_first,
                         Vector3 &inv_second,
                         const float theta)
noexcept
{
  Vector3 new_first
  { Vector3Add(Vector3Scale(first, cos(theta)), Vector3Scale(second, sin(theta))) };

  Vector3 new_second
  { Vector3Add(Vector3Scale(first, -sin(theta)), Vector3Scale(second, cos(theta))) };

  Vector3Normalize(new_first);
  Vector3Normalize(new_second);

  first = new_first;
  second = new_second;

  inv_first = Vector3Negate(first);
  inv_second = Vector3Negate(second);
}

void wrapper(float &dim,
             const float wrap)
noexcept
{
  if (wrap > 0.0f &&
      std::abs(dim) > wrap)
  { dim -= 2.0f*wrap*dim/std::abs(dim); }
}

void wrapping(Vector3 &position,
              const float wrap)
noexcept
{
  wrapper(position.x, wrap);
  wrapper(position.y, wrap);
  wrapper(position.z, wrap);
}

float randist(std::random_device &rand,
              const float dist_min,
              const float dist_max)
noexcept
{
  float fraction
  { static_cast<float>(rand())/static_cast<float>(rand.max()) };

  if (rand() > rand.max()/2)
  { fraction *= -1.0f; }

  return dist_min + fraction*(dist_max - dist_min);
}

Vector3 ranpos(std::random_device &rand,
               const float dist_min,
               const float dist_max)
noexcept
{
  Vector3 position;

  bool loop
  { true };

  while (loop)
  {
    position.x = randist(rand, dist_min, dist_max);
    position.y = randist(rand, dist_min, dist_max);
    position.z = randist(rand, dist_min, dist_max);

    if (std::abs(position.x) > dist_min ||
        std::abs(position.y) > dist_min ||
        std::abs(position.z) > dist_min)
    { loop = false; }
  }

  return position;
}

unsigned char dimming(const float mult,
                      unsigned char channel)
noexcept
{ return static_cast<char>(mult*static_cast<float>(channel)); }

Color dimmer(const Vector3 &difference,
             Color &cube_color,
             const float decay,
             const float multiplier)
noexcept
{
  const float distance
  { Vector3Length(difference) };

  const float mult
  { std::pow(decay, distance/multiplier) };

  const Color color
  { dimming(mult, cube_color.r), dimming(mult, cube_color.g), dimming(mult, cube_color.b), 255 };

  return color;
}

void display_cube(const Vector3 &position,
                  Vector3 &cube_position,
                  const Vector3 &cube_dims,
                  const Vector3 &forward,
                  Color &cube_color,
                  Color &edge_color,
                  const float cam_angle,
                  const float sight,
                  const float decay,
                  const float multiplier)
noexcept
{
  Vector3 difference
  { Vector3Subtract(cube_position, position) };

  if ((Vector3DotProduct(Vector3Normalize(difference), forward) > cam_angle &&
      Vector3DotProduct(difference, difference) <= sight*sight) ||
      Vector3DotProduct(difference, difference) <= multiplier*multiplier)
  {
    const Color dim_color
    { dimmer(difference, cube_color, decay, multiplier) };

    const Color dedge_color
    { dimmer(difference, edge_color, decay, multiplier) };

    DrawCube(cube_position, cube_dims.x, cube_dims.y, cube_dims.z, dim_color);
    DrawCubeWires(cube_position, cube_dims.x, cube_dims.y, cube_dims.z, dedge_color);
  }
}
