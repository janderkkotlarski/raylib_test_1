#ifndef RAYLIB_FUNCTIONS_H
#define RAYLIB_FUNCTIONS_H

#include <vector>
#include <string>

#include <raylib.h>

#include "fractacube.h"
#include "dungeon_loop.h"

#if defined(PLATFORM_DESKTOP)
  #define GLSL_VERSION            100
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
  #define GLSL_VERSION            330
#endif

void fog_ambient(Shader &fog_shader,
                 const std::vector <float> &ambient_profile);

void fog_init(Shader &fog_shader,
              const std::vector <float> &ambient_profile,
              int &fog_density_loc,
              const float fog_density)
noexcept;

void fog_refresh(Shader &fog_shader,
                 const Vector3 &position,
                 const std::vector <float> &ambient_profile,
                 const int fog_density_loc,
                 const float fog_density)
noexcept;

void refresh_fogs(std::vector <Model> &cube_models,
                  std::vector <Shader> &fog_shaders,
                  const Vector3 &position,
                  const std::vector<float> &spectral_profile,
                  const std::vector<float> &chromatic_profile,
                  const float candy_factor,
                  const int fog_density_loc,
                  const float fog_density)
 noexcept;

void init_cubes_images_fogs(std::vector <Model> &cube_models,
                            std::vector <Image> &face_images,
                            std::vector <Shader> &fog_shaders,
                            const Vector3 &position,
                            const std::vector<float> &ambient_profile,
                            const fractacube &f_cube,
                            const std::string &file_name,
                            const std::string &file_type,
                            int &fog_density_loc,
                            const float fog_density)
noexcept;

#endif // RAYLIB_FUNCTIONS_H
