#include "raylib_functions.h"

#include <iostream>

#include "cube_type.h"

Vector3 vector2vector3 (const std::vector <float> &vec)
{
  if (vec.size() != 3)
  {
    std::cerr << "Vector size is not 3!";
    throw 7;
  }

  return Vector3{ vec[0], vec[1], vec[2] };
}

std::vector <float> vector3_2vector (const Vector3 &vec3)
noexcept
{ return { vec3.x, vec3.y, vec3.z }; }

void fog_ambient(Shader &fog_shader,
                 const std::vector <float> &ambient_profile)
{
  const float ambient_loc
  { (float)GetShaderLocation(fog_shader, "ambient") };

  float ambient_floats[]
  { 0.0f, 10.0f, 10.0f, 1.0f };

  vector2array_float(ambient_profile, ambient_floats);

  SetShaderValue(fog_shader, ambient_loc, ambient_floats, UNIFORM_VEC4);
}

void fog_init(Shader &fog_shader,
              std::vector <float> &ambient_profile,
              int &fog_density_loc,
              const float fog_density)
noexcept
{
  fog_shader = LoadShader(FormatText("base_lighting.vs", GLSL_VERSION),
                          FormatText("dark_fog.fs", GLSL_VERSION));

  fog_shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(fog_shader, "matModel");
  fog_shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(fog_shader, "viewPos");

  fog_ambient(fog_shader, ambient_profile);

  fog_density_loc = GetShaderLocation(fog_shader, "fogDensity");
  SetShaderValue(fog_shader, fog_density_loc, &fog_density, UNIFORM_FLOAT);
}

void fog_refresh(Shader &fog_shader,
                 const std::vector <float> &position,
                 const std::vector <float> &ambient_profile,
                 const int fog_density_loc,
                 const float fog_density)
noexcept
{
  fog_ambient(fog_shader, ambient_profile);

  SetShaderValue(fog_shader, fog_density_loc, &fog_density, UNIFORM_FLOAT);
  SetShaderValue(fog_shader, fog_shader.locs[LOC_VECTOR_VIEW], &position[0], UNIFORM_VEC3);
}

void refresh_fogs(std::vector <Model> &cube_models,
                  std::vector <Shader> &fog_shaders,
                  const std::vector <float> &position,
                  const std::vector <float> &spectral_profile,
                  const std::vector <float> &chromatic_profile,
                  const float candy_factor,
                  const int fog_density_loc,
                  const float fog_density)
noexcept
{
  for (unsigned count{ 0 }; count < cube_models.size(); ++count)
  {
    const cube_type c_type
    { index2type(count) };

    std::vector <float> ambient_profile
    { 0.0f, 0.0f, 10.0f, 1.0f };

    type2profile(c_type, ambient_profile);

    type2proflex(c_type, ambient_profile, spectral_profile, chromatic_profile, candy_factor);

    scale_profile(ambient_profile, 10.0f);

    fog_refresh(fog_shaders[count], position, ambient_profile,
                fog_density_loc, fog_density);
  }
}

void refresh_darks(std::vector <Model> &cube_models,
                  std::vector <Shader> &fog_shaders,
                  const std::vector <float> &position,
                  const std::vector <float> &dark_profile,
                  const int fog_density_loc,
                  const float fog_density)
noexcept
{
  for (unsigned count{ 0 }; count < cube_models.size(); ++count)
  {
    std::vector <float> ambient_profile
    { dark_profile };

    scale_profile(ambient_profile, 5.0f);

    fog_refresh(fog_shaders[count], position, ambient_profile,
                fog_density_loc, fog_density);
  }
}

void init_cubes_images_fogs(std::vector <Model> &cube_models,
                            std::vector <Image> &face_images,
                            std::vector <Shader> &fog_shaders,
                            const std::vector <float> &position,
                            std::vector <float> &ambient_profile,
                            const fractacube &f_cube,
                            const std::string &file_name,
                            const std::string &file_type,
                            int &fog_density_loc,
                            const float fog_density,
                            const bool dark_bloom)
noexcept
{
  bool loading
  { true };

  unsigned count
  { 0 };

  while(loading)
  {
    const std::string file_name_type
    { file_name + std::to_string(count) + file_type };

    if (FileExists(file_name_type.c_str()))
    {
      face_images.push_back(LoadImage(file_name_type.c_str()));

      ImageRotateCW(&face_images[count]);

      cube_models.push_back(LoadModelFromMesh(GenMeshCube(f_cube.get_cube_dims()[0],
                                                          f_cube.get_cube_dims()[1],
                                                          f_cube.get_cube_dims()[2])));

      cube_models[count].materials[0].maps[MAP_DIFFUSE].texture = LoadTextureFromImage(face_images[count]);

      fog_shaders.push_back(Shader{});

      fog_shaders[count] = LoadShader(FormatText("base_lighting.vs", GLSL_VERSION),
                                      FormatText("dark_fog.fs", GLSL_VERSION));

      if (dark_bloom)
      { fog_shaders[count] = LoadShader(0, FormatText("bloom.fs", GLSL_VERSION)); }

      fog_init(fog_shaders[count], ambient_profile, fog_density_loc, fog_density);

      fog_refresh(fog_shaders[count], position, ambient_profile, fog_density_loc, fog_density);
      cube_models[count].materials[0].shader = fog_shaders[count];

    }
    else
    { loading = false; }

    ++count;
  }
}
