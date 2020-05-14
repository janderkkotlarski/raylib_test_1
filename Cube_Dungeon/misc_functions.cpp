#include "misc_functions.h"

#include <cmath>
#include <cassert>
#include <iostream>

#include <raymath.h>

std::vector <int> negate_int_vector(const std::vector <int> &vec)
noexcept
{
  std::vector <int> invec;

  unsigned count
  { 0 };

  for (const int number: vec)
  {
    invec.push_back(-number);

    assert(invec[count] == -vec[count]);
  }

  assert(invec.size() == vec.size());

  return invec;
}

std::vector <int> scale_int_vector(const std::vector <int> &vec,
                                   const int scale)
noexcept
{
  std::vector <int> scavec;

  unsigned count
  { 0 };

  for (const int number: vec)
  {
    scavec.push_back(scale*number);

    assert(scavec[count] == scale*vec[count]);
  }

  assert(scavec.size() == vec.size());

  return scavec;
}

std::vector <int> add_int_vector(const std::vector <int> &vec_1,
                                 const std::vector <int> &vec_2)
{
  if (vec_1.size() != vec_2.size())
  {
    std::cerr << "The vectors have different sizes" << std::endl;
    throw -1;
  }

  if (vec_1.size() == 0)
  {
    std::cerr << "The vectors have size 0" << std::endl;
    throw -2;
  }

  std::vector <int> addvec;

  unsigned count
  { 0 };

  for (const int number: vec_1)
  {
    addvec.push_back(number + vec_2[count]);
    assert(addvec[count] == vec_1[count] + vec_2[count]);
    ++count;
  }

  assert(addvec.size() == vec_1.size());

  return addvec;
}

std::vector <int> sub_int_vector(const std::vector <int> &vec_1,
                                 const std::vector <int> &vec_2)
{

  if (vec_1.size() != vec_2.size())
  {
    std::cerr << "The vectors have different sizes" << std::endl;
    throw -1;
  }

  if (vec_1.size() == 0)
  {
    std::cerr << "The vectors have size 0" << std::endl;
    throw -2;
  }

  std::vector <int> subvec;

  unsigned count
  { 0 };

  for (const int number: vec_1)
  {
    subvec.push_back(number - vec_2[count]);
    assert(subvec[count] == vec_1[count] - vec_2[count]);
    ++count;
  }

  assert(subvec.size() == vec_1.size());

  return subvec;
}

void display_string(const std::string str,
                    const std::string &message,
                    const int x,
                    const int y,
                    const int size)
noexcept
{
  if (str.size() > 0)
  {
    std::string info_string
    { message };

    info_string += str;

    const char *info_array
    { info_string.c_str() };
    DrawText(info_array, x, y, size, SKYBLUE);
  }
}

void display_string_vector(const std::vector <std::string> vector_strings,
                           const std::string &message,
                           const int x,
                           const int y,
                           const int size)
noexcept
{
  if (vector_strings.size() > 0)
  {
    std::string info_string
    { message };

    unsigned count
    { 0 };

    for (const std::string &v_string: vector_strings)
    {
      info_string += v_string;

      if (count < vector_strings.size() - 1)
      { info_string += ","; }
    }

    const char *info_array
    { info_string.c_str() };
    DrawText(info_array, x, y, size, SKYBLUE);
  }
}

std::vector <std::string> int_vector_to_strings(const std::vector <int> &vec)
noexcept
{
  std::vector <std::string> strings;

  if (vec.size() > 0)
  {
    for (const int number: vec)
    { strings.push_back(std::to_string(number)); }
  }

  assert(strings.size() == vec.size());

  return strings;
}

std::vector <std::string> vector3_to_strings(const Vector3 &vec)
noexcept
{
  std::vector <std::string> strings;

  strings.push_back(std::to_string(vec.x));
  strings.push_back(std::to_string(vec.y));
  strings.push_back(std::to_string(vec.z));

  assert(strings.size() == 3);

  return strings;
}

void color2profile(const Color &color,
                   std::vector <float> &profile)
noexcept
{
  const float mult
  { 1.0f };

  profile[0] = mult*(float)color.r/255.0f;
  profile[1] = mult*(float)color.g/255.0f;
  profile[2] = mult*(float)color.b/255.0f;
  profile[3] = mult*(float)color.a/255.0f;
}

std::vector <float> color2profile(const Color &color)
noexcept
{
  std::vector <float> profile;

  const float mult
  { 1.0f };

  profile.push_back(mult*(float)color.r/255.0f);
  profile.push_back(mult*(float)color.g/255.0f);
  profile.push_back(mult*(float)color.b/255.0f);
  profile.push_back(mult*(float)color.a/255.0f);

  return profile;
}

void spectral_shift(std::vector <float> &spectral_profile,
                    const float delta_profile)
noexcept
{
  const float delta
  { 1.0f };


  if (spectral_profile[0] == 1.0f && spectral_profile[1] == 0.5f && spectral_profile[2] < 1.0f)
  {
    spectral_profile[2] += delta*delta_profile;

    if (spectral_profile[2] > 1.0f)
    { spectral_profile[2] = 1.0f; }
  }

  if (spectral_profile[2] == 1.0f && spectral_profile[0] == 0.5f && spectral_profile[1] < 1.0f)
  {
    spectral_profile[1] += delta*delta_profile;


    if (spectral_profile[1] > 1.0f)
    { spectral_profile[1] = 1.0f; }
  }

  if (spectral_profile[1] == 1.0f && spectral_profile[2] == 0.5f && spectral_profile[0] < 1.0f)
  {
    spectral_profile[0] += delta*delta_profile;


    if (spectral_profile[0] > 1.0f)
    { spectral_profile[0] = 1.0f; }
  }

  if (spectral_profile[0] == 0.5f && spectral_profile[1] == 1.0f && spectral_profile[2] > 0.5f)
  {
    spectral_profile[2] -= delta*delta_profile;

    if (spectral_profile[2] < 0.5f)
    { spectral_profile[2] = 0.5f; }
  }

  if (spectral_profile[2] == 0.5f && spectral_profile[0] == 1.0f && spectral_profile[1] > 0.5f)
  {
    spectral_profile[1] -= delta*delta_profile;

    if (spectral_profile[1] < 0.5f)
    { spectral_profile[1] = 0.5f; }
  }

  if (spectral_profile[1] == 0.5f && spectral_profile[2] == 1.0f && spectral_profile[0] > 0.5f)
  {
    spectral_profile[0] -= delta*delta_profile;

    if (spectral_profile[0] < 0.5f)
    { spectral_profile[0] = 0.5f; }
  }
}

void vector2array_float(const std::vector <float> &vec,
                        float (&arr)[4])
{
  for (unsigned count{ 0 }; count < vec.size(); ++count)
  { arr[count] = vec[count]; }
}

void chromatic_shift(std::vector <float> &chromatic_profile,
                     const float delta_profile)
noexcept
{
  const float delta
  { 1.0f };


  if (chromatic_profile[0] == 0.5f && chromatic_profile[1] == 1.0f && chromatic_profile[2] < 1.0f)
  {
    chromatic_profile[2] += delta*delta_profile;

    if (chromatic_profile[2] > 1.0f)
    { chromatic_profile[2] = 1.0f; }
  }

  if (chromatic_profile[2] == 0.5f && chromatic_profile[0] == 1.0f && chromatic_profile[1] < 1.0f)
  {
    chromatic_profile[1] += delta*delta_profile;


    if (chromatic_profile[1] > 1.0f)
    { chromatic_profile[1] = 1.0f; }
  }

  if (chromatic_profile[1] == 0.5f && chromatic_profile[2] == 1.0f && chromatic_profile[0] < 1.0f)
  {
    chromatic_profile[0] += delta*delta_profile;


    if (chromatic_profile[0] > 1.0f)
    { chromatic_profile[0] = 1.0f; }
  }

  if (chromatic_profile[0] == 1.0f && chromatic_profile[1] == 0.5f && chromatic_profile[2] > 0.5f)
  {
    chromatic_profile[2] -= delta*delta_profile;

    if (chromatic_profile[2] < 0.5f)
    { chromatic_profile[2] = 0.5f; }
  }

  if (chromatic_profile[2] == 1.0f && chromatic_profile[0] == 0.5f && chromatic_profile[1] > 0.5f)
  {
    chromatic_profile[1] -= delta*delta_profile;

    if (chromatic_profile[1] < 0.5f)
    { chromatic_profile[1] = 0.5f; }
  }

  if (chromatic_profile[1] == 1.0f && chromatic_profile[2] == 0.5f && chromatic_profile[0] > 0.5f)
  {
    chromatic_profile[0] -= delta*delta_profile;

    if (chromatic_profile[0] < 0.5f)
    { chromatic_profile[0] = 0.5f; }
  }
}

void candy_blink(float &candy_factor,
                 const float delta_time,
                 bool &candy_up)
noexcept
{
  const float delta
  { 1.0f };

  if (candy_up)
  { candy_factor += delta*delta_time; }
  else
  { candy_factor -= delta*delta_time; }

  if (candy_factor >= 1.0f)
  {
    candy_factor = 1.0f;
    candy_up = false;
  }

  if (candy_factor <= 0.0f)
  {
    candy_factor = 0.0f;
    candy_up = true;
  }
}

void dark_shift(std::vector <float> &dark_profile,
                const float delta_time,
                float &opacity,
                bool &dark_up)
noexcept
{
  const float delta
  { 0.2f };

  const float max
  { 0.35f };

  if (dark_up)
  { opacity += delta*delta_time; }
  else
  { opacity -= delta*delta_time; }

  if (opacity >= max)
  {
    opacity = max;
    dark_up = false;
  }

  if (opacity <= 0.0f)
  {
    opacity = 0.0f;
    dark_up = true;
  }

  const float cospacity
  { max*(1.0f - cos(1.0f*PI*opacity/max)) };

  dark_profile[0] = 0.1f*cospacity;
  dark_profile[2] = 0.2f*cospacity;
}

void acid_trip(const float cam_angle_average,
               const float cam_angle_deviation,
               float &cam_angle,
               float &opacity)
noexcept
{
  const float max
  { 0.35f };

  cam_angle = cam_angle_average - cos(1.0f*PI*opacity/max)*cam_angle_deviation;
}

void scale_color(Color &color,
                 const float mult)
noexcept
{
  color.r = (unsigned)round((float)color.r*mult);
  color.g = (unsigned)round((float)color.g*mult);
  color.b = (unsigned)round((float)color.b*mult);
}

void scale_color(Color &color,
                 const unsigned char intensity)
noexcept
{ scale_color(color, (float)intensity/255.0f); }

void change_opacity(Color &color,
                    const float opacity)
noexcept
{
  const unsigned opac
  { (unsigned)round(abs(255.0f*opacity)) };

  color.a = opac;
}

Color profile2color(const std::vector <float> &profile)
noexcept
{
  Color color
  { 0, 0, 0, 0 };

  if (profile.size() > 0)
  { color.r = (unsigned char)(int)round(255.0f*profile[0]); }

  if (profile.size() > 1)
  { color.g = (unsigned char)(int)round(255.0f*profile[1]); }

  if (profile.size() > 2)
  { color.b = (unsigned char)(int)round(255.0f*profile[2]); }

  if (profile.size() > 3)
  { color.a = (unsigned char)(int)round(255.0f*profile[3]); }

  return color;
}

void rotate_first_second(Vector3 &first,
                         Vector3 &second,
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

bool display_selector(const Vector3 &position,
                      const Vector3 &cube_position,
                      const Vector3 &forward,
                      const float cam_field,
                      const float multiplier)
noexcept
{
  const Vector3 difference
  { Vector3Subtract(cube_position, position) };

  return (Vector3DotProduct(Vector3Normalize(difference), forward) > cam_field ||
          Vector3DotProduct(difference, difference) <= 4.0f*multiplier*multiplier);
}

bool display_selector(const Vector3 &position,
                      const Vector3 &cube_position,
                      const Vector3 &forward,
                      const float cam_field,
                      const float sight,
                      const float multiplier)
noexcept
{
  const Vector3 difference
  { Vector3Subtract(cube_position, position) };

  return ((Vector3DotProduct(Vector3Normalize(difference), forward) > cam_field &&
           Vector3DotProduct(difference, difference) <= sight*sight) ||
          Vector3DotProduct(difference, difference) <= 4.0f*multiplier*multiplier);
}
