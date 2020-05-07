#ifndef RAYLIB_FUNCTIONS_H
#define RAYLIB_FUNCTIONS_H

#include <vector>
#include <string>

#include <raylib.h>

#include "fractacube.h"
#include "dungeon_loop.h"

void fog_init(Shader &fog_shader)
noexcept;

void init_cubes_images_fogs(dungeon_loop &d_loop,
                            std::vector <Model> &cube_models,
                            std::vector <Image> &face_images,
                            std::vector <Shader> &fog_shaders,
                            const fractacube &f_cube,
                            const std::string &file_name,
                            const std::string &file_type,
                            const Vector3 &spectral_profile,
                            const Vector3 &chromatic_profile)
noexcept;

#endif // RAYLIB_FUNCTIONS_H
