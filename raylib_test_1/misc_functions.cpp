#include "misc_functions.h"

#include <cmath>

Vector3 add_vector3(const Vector3 &vec_1,
                            const Vector3 &vec_2)
noexcept
{
  Vector3 out_vec;

  out_vec.x = vec_1.x + vec_2.x;
  out_vec.y = vec_1.y + vec_2.y;
  out_vec.z = vec_1.z + vec_2.z;

  return out_vec;
}

Vector3 sub_vector3(const Vector3 &vec_1,
                            const Vector3 &vec_2)
noexcept
{
  Vector3 out_vec;

  out_vec.x = vec_1.x - vec_2.x;
  out_vec.y = vec_1.y - vec_2.y;
  out_vec.z = vec_1.z - vec_2.z;

  return out_vec;
}

Vector3 multiply_vector3(const Vector3 &vec_1,
                                 const float mult)
noexcept
{
  Vector3 out_vec;

  out_vec.x = vec_1.x*mult;
  out_vec.y = vec_1.y*mult;
  out_vec.z = vec_1.z*mult;

  return out_vec;
}

std::vector <std::string> vector3_to_strings(const Vector3 &vec)
noexcept
{
  std::vector <std::string> strings;

  strings.push_back(std::to_string(vec.x));
  strings.push_back(std::to_string(vec.y));
  strings.push_back(std::to_string(vec.z));

  return strings;
}

Vector3 unit_vectorize(const Vector3 &vec)
noexcept
{
  const float abs_length
  { static_cast<float>(sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z)) };

  if (abs_length > 0.0f)
  {
    const Vector3 out
    { vec.x/abs_length, vec.y/abs_length, vec.z/abs_length };

    return out;
  }

  return vec;
}

float inproduct(const Vector3 &vec_1,
                const Vector3 &vec_2)
noexcept
{ return vec_1.x*vec_2.x + vec_1.y*vec_2.y + vec_1.z*vec_2.z; }

void rotate_first_second(Vector3 &first,
                         Vector3 &second,
                         Vector3 &inv_first,
                         Vector3 &inv_second,
                         const float theta)
noexcept
{
  Vector3 new_first
  { add_vector3(multiply_vector3(first, cos(theta)), multiply_vector3(second, sin(theta))) };

  Vector3 new_second
  { add_vector3(multiply_vector3(first, -sin(theta)), multiply_vector3(second, cos(theta))) };

  unit_vectorize(new_first);
  unit_vectorize(new_second);

  first = new_first;
  second = new_second;

  inv_first = multiply_vector3(first, -1);
  inv_second = multiply_vector3(second, -1);
}

void key_bindings(Camera &camera,
                  Vector3 &position,
                  Vector3 &forward,
                  Vector3 &backward,
                  Vector3 &rightward,
                  Vector3 &leftward,
                  Vector3 &upward,
                  Vector3 &downward,
                  const float velocity,
                  const float theta)
noexcept
{
  if (IsKeyDown('W'))
  { position = add_vector3(position, multiply_vector3(forward, velocity)); }

  if (IsKeyDown('S'))
  { position = add_vector3(position, multiply_vector3(backward, velocity)); }

  if (IsKeyDown('D'))
  { position = add_vector3(position, multiply_vector3(rightward, velocity)); }

  if (IsKeyDown('A'))
  { position = add_vector3(position, multiply_vector3(leftward, velocity)); }

  if (IsKeyDown('E'))
  { position = add_vector3(position, multiply_vector3(upward, velocity)); }

  if (IsKeyDown('Q'))
  { position = add_vector3(position, multiply_vector3(downward, velocity)); }

  if (IsKeyDown('L'))
  { rotate_first_second(forward, rightward, backward, leftward, theta); }

  if (IsKeyDown('J'))
  { rotate_first_second(forward, leftward, backward, rightward, theta); }

  if (IsKeyDown('I'))
  {
    rotate_first_second(forward, upward, backward, downward, theta);
    camera.up = upward;
  }

  if (IsKeyDown('K'))
  {
    rotate_first_second(forward, downward, backward, upward, theta);
    camera.up = upward;
  }

  if (IsKeyDown('O'))
  {
    rotate_first_second(upward, rightward, downward, leftward, theta);
    camera.up = upward;
  }

  if (IsKeyDown('U'))
  {
    rotate_first_second(upward, leftward, downward, rightward, theta);
    camera.up = upward;
  }
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
  { std::sqrt(inproduct(difference, difference)) };

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
  const Vector3 difference
  { sub_vector3(cube_position, position) };

  if (inproduct(unit_vectorize(difference), forward) > cam_angle &&
      inproduct(difference, difference) <= sight*sight)
  {
    const Color dim_color
    { dimmer(difference, cube_color, decay, multiplier) };

    const Color dedge_color
    { dimmer(difference, edge_color, decay, multiplier) };

    DrawCube(cube_position, cube_dims.x, cube_dims.y, cube_dims.z, dim_color);
    DrawCubeWires(cube_position, cube_dims.x, cube_dims.y, cube_dims.z, dedge_color);
  }
}
