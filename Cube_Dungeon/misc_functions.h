#ifndef MISC_FUNCTIONS_H
#define MISC_FUNCTIONS_H

#include <vector>
#include <random>

#include <raylib.h>

#include "cube_type.h"

std::vector <float> vector_negate(const std::vector <float> &vec)
noexcept;

std::vector <float> vector_add(const std::vector <float> &vec_1,
                               const std::vector <float> &vec_2);

std::vector <float> vector_subtract(const std::vector <float> &vec_1,
                                     const std::vector <float> &vec_2);

std::vector <float> vector_scale(const std::vector <float> &vec_1,
                                 const float scale);

float vector_dot_product(const std::vector <float> &vec_1,
                         const std::vector <float> &vec_2);

float vector_length(const std::vector <float> &vec)
noexcept;

std::vector <float> vector_normalized(const std::vector <float> &vec)
noexcept;

void vector_normalize(std::vector <float> &vec)
noexcept;

std::vector <float> vector_int2float(const std::vector <int> &vec_int)
noexcept;

std::vector <int> vector_float2int(const std::vector <float> &vec_float)
noexcept;

std::vector <int> negate_int_vector(const std::vector <int> &vec)
noexcept;

std::vector <int> scale_int_vector(const std::vector <int> &vec,
                                   const int scale)
noexcept;

std::vector <unsigned> add_int_vector(const std::vector <int> &vec_1,
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

std::vector <std::string> int_vector2strings(const std::vector <int> &vec)
noexcept;

std::string vector2string(const std::vector <float> &vec)
noexcept;

std::vector <std::string> vector2strings(const std::vector <float> &vec)
noexcept;



void vector2array_float(const std::vector <float> &vec,
                        float (&arr)[4]);

void rotate_first_second(std::vector <float> &first,
                         std::vector <float> &second,
                         const float theta);

void key_bindings(Camera &camera,
                  std::vector <float> &position,
                  std::vector <float> &forward,
                  std::vector <float> &backward,
                  std::vector <float> &rightward,
                  std::vector <float> &leftward,
                  std::vector <float> &upward,
                  std::vector <float> &downward,
                  const float velocity,
                  const float theta)
noexcept;

void wrapper(float &dim,
             const float wrap)
noexcept;

void wrapping(std::vector <float> &position,
              const float wrap)
noexcept;

float randist(std::random_device &rand,
              const float dist_min,
              const float dist_max)
noexcept;

std::vector <float> ranpos(std::random_device &rand,
                       const float dist_min,
                       const float dist_max)
noexcept;

unsigned char dimming(const float mult,
                      unsigned char channel)
noexcept;

Color dimmer(const std::vector <float> &difference,
                     Color &cube_color,
                     const float decay,
                     const float multiplier)
noexcept;

bool display_selector(const std::vector <float> &position,
                      const std::vector <float> &cube_position,
                      const std::vector <float> &forward,
                      const float cam_field)
noexcept;

bool display_selector(const std::vector <float> &position,
                      const std::vector <float> &cube_position,
                      const std::vector <float> &forward,
                      const float cam_angle,
                      const float sight)
noexcept;

#endif // MISC_FUNCTIONS_H
