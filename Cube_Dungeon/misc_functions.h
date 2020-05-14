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

void display_string(const std::string str,
                    const std::string &message,
                    const int x,
                    const int y,
                    const int size)
noexcept;

void display_string_vector(const std::vector <std::string> vector_strings,
                           const std::string &message,
                           const int x,
                           const int y,
                           const int size)
noexcept;

void color2profile(const Color &color,
                   std::vector <float> &profile)
noexcept;

void spectral_shift(std::vector<float> &spectral_profile,
                    const float delta_profile)
noexcept;

void chromatic_shift(std::vector<float> &chromatic_profile,
                     const float delta_profile)
noexcept;

void candy_blink(float &candy_factor,
                 const float delta_time,
                 bool &candy_up)
noexcept;

void dark_shift(std::vector<float> &dark_profile,
                const float delta_time,
                float &opacity,
                bool &dark_up)
noexcept;

void acid_trip(const float cam_angle_average,
               const float cam_angle_deviation,
               float &cam_angle,
               float &opacity)
noexcept;

void scale_color(Color &color,
                 const float mult)
noexcept;

void scale_color(Color &color,
                 const unsigned char intensity)
noexcept;

void change_opacity(Color &color,
                    const float opacity)
noexcept;

Color profile2color(const std::vector <float> &profile)
noexcept;

void color2profile(const Color &color,
                   std::vector <float> &profile)
noexcept;

std::vector <float> color2profile(const Color &color)
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

void vector2array_float(const std::vector <float> &vec,
                        float (&arr)[4]);

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

#endif // MISC_FUNCTIONS_H
