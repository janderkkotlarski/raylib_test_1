#ifndef MISC_FUNCTIONS_H
#define MISC_FUNCTIONS_H

#include <vector>
#include <random>

#include <raylib.hpp>

raylib::Vector3 add_vector3(const raylib::Vector3 &vec_1,
                            const raylib::Vector3 &vec_2)
noexcept;

raylib::Vector3 sub_vector3(const raylib::Vector3 &vec_1,
                            const raylib::Vector3 &vec_2)
noexcept;

raylib::Vector3 multiply_vector3(const raylib::Vector3 &vec_1,
                                 const float mult)
noexcept;

std::vector <std::string> vector3_to_strings(const raylib::Vector3 &vec)
noexcept;

raylib::Vector3 unit_vectorize(const raylib::Vector3 &vec)
noexcept;

float inproduct(const raylib::Vector3 &vec_1,
                const raylib::Vector3 &vec_2)
noexcept;

void rotate_first_second(raylib::Vector3 &first,
                         raylib::Vector3 &second,
                         raylib::Vector3 &inv_first,
                         raylib::Vector3 &inv_second,
                         const float theta)
noexcept;

void key_bindings(raylib::Camera &camera,
                  raylib::Vector3 &position,
                  raylib::Vector3 &forward,
                  raylib::Vector3 &backward,
                  raylib::Vector3 &rightward,
                  raylib::Vector3 &leftward,
                  raylib::Vector3 &upward,
                  raylib::Vector3 &downward,
                  const float velocity,
                  const float theta)
noexcept;

void wrapper(float &dim,
             const float wrap)
noexcept;

void wrapping(raylib::Vector3 &position,
              const float wrap)
noexcept;

float randist(std::random_device &rand,
              const float dist_min,
              const float dist_max)
noexcept;

raylib::Vector3 ranpos(std::random_device &rand,
                       const float dist_min,
                       const float dist_max)
noexcept;

unsigned char dimming(const float mult,
                      unsigned char channel)
noexcept;

raylib::Color dimmer(const raylib::Vector3 &difference,
                     raylib::Color &cube_color,
                     const float decay,
                     const float multiplier)
noexcept;

void display_cube(const raylib::Vector3 &position,
                  raylib::Vector3 &cube_position,
                  const raylib::Vector3 &cube_dims,
                  const raylib::Vector3 &forward,
                  raylib::Color &cube_color,
                  raylib::Color &edge_color,
                  const float cam_angle,
                  const float sight,
                  const float decay,
                  const float multiplier)
noexcept;

#endif // MISC_FUNCTIONS_H
