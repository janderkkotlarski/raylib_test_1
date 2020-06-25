#include "misc_functions.h"

#include <cmath>
#include <cassert>
#include <iostream>

#include <raymath.h>

std::vector <float> vector_negate(const std::vector <float> &vec)
noexcept
{
  std::vector <float> invec;

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

std::vector <float> vector_add(const std::vector <float> &vec_1,
                               const std::vector <float> &vec_2)
{
  if (vec_1.size() == 0)
  {
    std::cerr << "Vector has no size!" << std::endl;

    throw 6;
  }

  if (vec_1.size() != vec_2.size())
  {
    std::cerr << "Vectors have different sizes!" << std::endl;

    throw 7;
  }

  std::vector <float> vec_3;

  unsigned count
  { 0 };

  for (const float num: vec_1)
  {
    vec_3.push_back(num + vec_2[count]);
    ++count;
  }

  return vec_3;
}

std::vector <float> vector_subtract(const std::vector <float> &vec_1,
                                     const std::vector <float> &vec_2)
{
  if (vec_1.size() == 0)
  {
    std::cerr << "Vector has no size!" << std::endl;

    throw 6;
  }

  if (vec_1.size() != vec_2.size())
  {
    std::cerr << "Vectors have different sizes!" << std::endl;

    throw 7;
  }

  std::vector <float> vec_3;

  unsigned count
  { 0 };

  for (const float num: vec_1)
  {
    vec_3.push_back(num - vec_2[count]);
    ++count;
  }

  return vec_3;
}

std::vector <float> vector_scale(const std::vector <float> &vec_1,
                                 const float scale)
{
  if (vec_1.size() == 0)
  {
    std::cerr << "Vector has size 0!";

    throw 1;
  }

  std::vector <float> vec_2;

  for (const float num: vec_1)
  { vec_2.push_back(num*scale); }

  return vec_2;
}

float vector_dot_product(const std::vector <float> &vec_1,
                         const std::vector <float> &vec_2)
{
  if (vec_1.size() == 0 ||
      vec_2.size() == 0)
  {
    std::cerr << "One vector has size 0!" << std::endl;

    throw 4;
  }

  if (vec_1.size() != vec_2.size())
  {
    std::cerr << "Vectors have different sizes!" << std::endl;

    throw 5;
  }

  unsigned count
  { 0 };

  float product
  { 0.0f };

  for (const float num: vec_1)
  {
    product += num*vec_2[count];
    ++count;
  }

  return product;
}

float vector_length(const std::vector <float> &vec)
noexcept
{
  float length
  { sqrt(vector_dot_product(vec, vec)) };

  return length;
}

std::vector <float> vector_normalized(const std::vector <float> &vec)
noexcept
{
  const float length
  { vector_length(vec) };

  std::vector <float> vec_2
  { vec };

  if (length > 0.0f)
  {
    for (float &num: vec_2)
    { num /= length; }
  }

  return vec_2;
}

void vector_normalize(std::vector <float> &vec)
noexcept
{ vec = vector_normalized(vec); }

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

std::vector <float> vector_int2float(const std::vector <int> &vec_int)
noexcept
{
  std::vector <float> vec_float;

  for (const int num: vec_int)
  { vec_float.push_back(num); }

  return vec_float;
}

std::vector <int> vector_float2int(const std::vector <float> &vec_float)
noexcept
{
  std::vector <int> vec_int;

  for (const float num: vec_float)
  { vec_int.push_back(int(round(num))); }

  return vec_int;
}

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

std::vector <unsigned> add_int_vector(const std::vector <int> &vec_1,
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

  std::vector <unsigned> addvec;

  unsigned count
  { 0 };

  for (const int number: vec_1)
  {
    addvec.push_back(number + vec_2[count]);
    assert(addvec[count] == (unsigned)(vec_1[count] + vec_2[count]));
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
    { str };

    info_string += message;

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

std::string vector2string(const std::vector <float> &vec)
noexcept
{
  std::string coords;

  for (const float num: vec)
  { coords += "[" + std::to_string(num) + "]"; }

  return coords;
}

std::vector <std::string> vector2strings(const std::vector <float> &vec)
noexcept
{
  std::vector <std::string> strings;

  for (const float num: vec)
  { strings.push_back(std::to_string(num)); }

  return strings;
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

void rotate_first_second(std::vector <float> &first,
                         std::vector <float> &second,
                         const float theta)
{
  std::vector <float> new_first
  { vector_add(vector_scale(first, cos(theta)), vector_scale(second, sin(theta))) };

  std::vector <float> new_second
  { vector_add(vector_scale(first, -sin(theta)), vector_scale(second, cos(theta))) };

  vector_normalize(new_first);
  vector_normalize(new_second);

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

void wrapping(std::vector <float> &position,
              const float wrap)
noexcept
{
  for (float &num: position)
  { wrapper(num, wrap); }
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

std::vector <float> ranpos(std::random_device &rand,
               const float dist_min,
               const float dist_max)
noexcept
{
  std::vector <float> position;

  bool loop
  { true };

  while (loop)
  {

    for (float &num: position)
    { num = randist(rand, dist_min, dist_max); }

    for (const float num: position)
    {
      if (num > dist_min)
      { loop = false; }
    }
  }

  return position;
}

unsigned char dimming(const float mult,
                      unsigned char channel)
noexcept
{ return static_cast<char>(mult*static_cast<float>(channel)); }

Color dimmer(const std::vector <float> &difference,
             Color &cube_color,
             const float decay,
             const float multiplier)
noexcept
{
  const float distance
  { vector_length(difference) };

  const float mult
  { std::pow(decay, distance/multiplier) };

  const Color color
  { dimming(mult, cube_color.r), dimming(mult, cube_color.g), dimming(mult, cube_color.b), 255 };

  return color;
}

bool display_selector(const std::vector <float> &position,
                      const std::vector <float> &cube_position,
                      const std::vector <float> &forward,
                      const float cam_field)
noexcept
{
  const std::vector <float> difference
  { vector_subtract(cube_position, position) };

  return (vector_dot_product(vector_normalized(difference), forward) > cam_field ||
          vector_dot_product(difference, difference) <= 4.0f);
}

bool display_selector(const std::vector <float> &position,
                      const std::vector <float> &cube_position,
                      const std::vector <float> &forward,
                      const float cam_field,
                      const float sight)
noexcept
{
  const std::vector <float> difference
  { vector_subtract(cube_position, position) };

  return ((vector_dot_product(vector_normalized(difference), forward) > cam_field &&
           vector_dot_product(difference, difference) <= sight*sight) ||
           vector_dot_product(difference, difference) <= 4.0f);
}
