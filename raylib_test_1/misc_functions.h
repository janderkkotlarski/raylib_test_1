#ifndef MISC_FUNCTIONS_H
#define MISC_FUNCTIONS_H

#include <vector>
#include <random>

#include <raylib.h>

#include "cube_type.h"

std::vector <int> negate_int_vector(const std::vector <int> &vec)
noexcept;

std::vector <int> scale_int_vector(const std::vector <int> &vec,
                                   const int scale)
noexcept;

std::vector <int> add_int_vector(const std::vector <int> &vec_1,
                                 const std::vector <int> &vec_2);

std::vector <int> sub_int_vector(const std::vector <int> &vec_1,
                                 const std::vector <int> &vec_2);

void display_string_vector(const std::vector <std::string> vector_strings,
                           const std::string &message,
                           const int x,
                           const int y,
                           const int size)
noexcept;

std::vector <std::string> int_vector_to_strings(const std::vector <int> &vec)
noexcept;

std::vector <std::string> vector3_to_strings(const Vector3 &vec)
noexcept;

Vector3 add_vector3(const Vector3 &vec_1,
                    const Vector3 &vec_2)
noexcept;

Vector3 sub_vector3(const Vector3 &vec_1,
                    const Vector3 &vec_2)
noexcept;

Vector3 multiply_vector3(const Vector3 &vec_1,
                         const float mult)
noexcept;

std::vector <std::string> vector3_to_strings(const Vector3 &vec)
noexcept;

void rotate_first_second(Vector3 &first,
                         Vector3 &second,
                         const float theta)
noexcept;

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
noexcept;

void wrapper(float &dim,
             const float wrap)
noexcept;

void wrapping(Vector3 &position,
              const float wrap)
noexcept;

float randist(std::random_device &rand,
              const float dist_min,
              const float dist_max)
noexcept;

Vector3 ranpos(std::random_device &rand,
                       const float dist_min,
                       const float dist_max)
noexcept;

unsigned char dimming(const float mult,
                      unsigned char channel)
noexcept;

Color dimmer(const Vector3 &difference,
                     Color &cube_color,
                     const float decay,
                     const float multiplier)
noexcept;

bool display_selector(const Vector3 &position,
                      const Vector3 &cube_position,
                      const Vector3 &forward,
                      const float cam_field,
                      const float multiplier)
noexcept;

bool display_selector(const Vector3 &position,
                      const Vector3 &cube_position,
                      const Vector3 &forward,
                      const float cam_angle,
                      const float sight,
                      const float multiplier)
noexcept;

void display_cube(const Vector3 &position,
                  Vector3 &cube_position,
                  const Vector3 &cube_dims,
                  const cube_type c_type,
                  const float decay,
                  const float multiplier)
noexcept;

#endif // MISC_FUNCTIONS_H
