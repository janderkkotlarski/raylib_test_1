#include "raylib_functions.h"

#include "cube_type.h"

void fog_init(Shader &fog_shader)
noexcept
{
  fog_shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(fog_shader, "matModel");
  fog_shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(fog_shader, "viewPos");
}

void fog_refresh(Model &cube_model,
                 Shader &fogg_shader,
                 const std::vector <float> &fog_profile,
                 const int fog_density_loc,
                 const float fog_density)
noexcept
{
  const float ambient_loc
  { (float)GetShaderLocation(fogg_shader, "ambient") };

  float fog_color[fog_profile.size()];

  for (unsigned count { 0 }; count < fog_profile.size(); ++count)
  { fog_color[count] = fog_profile[count]; }

  SetShaderValue(fogg_shader, ambient_loc, fog_color, UNIFORM_VEC4);
  SetShaderValue(fogg_shader, fog_density_loc, &fog_density, UNIFORM_FLOAT);

  cube_model.materials[0].shader = fogg_shader;
}

void refresh_fogs(std::vector <Model> &cube_models,
                  std::vector <Shader> &fog_shaders,
                  const std::vector <float> &fog_profile,
                  const int fog_density_loc,
                  const float fog_density,
                  const Vector3 &spectral_profile,
                  const Vector3 &chromatic_profile)
 noexcept
{
  for (unsigned count{ 0 }; count < cube_models.size(); ++count)
  {
    fog_refresh(cube_models[count], fog_shaders[count], color2profile(type_color(index2type(count), spectral_profile, chromatic_profile)),
                fog_density_loc, fog_density);
  }
}

void init_cubes_images_fogs(std::vector <Model> &cube_models,
                            std::vector <Image> &face_images,
                            std::vector <Shader> &fog_shaders,
                            const fractacube &f_cube,
                            const std::string &file_name,
                            const std::string &file_type,
                            const Vector3 &spectral_profile,
                            const Vector3 &chromatic_profile,
                            const int fog_density_loc,
                            const float fog_density)
noexcept
{
  #if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
  #else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
  #endif

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

      cube_models.push_back(LoadModelFromMesh(GenMeshCube(f_cube.get_cube_dims().x,
                                                          f_cube.get_cube_dims().y,
                                                          f_cube.get_cube_dims().z)));

      cube_models[count].materials[0].maps[MAP_DIFFUSE].texture = LoadTextureFromImage(face_images[count]);

      fog_shaders.push_back(LoadShader(FormatText("base_lighting.vs", GLSL_VERSION),
                                       FormatText("dark_fog.fs", GLSL_VERSION)));

      fog_init(fog_shaders[count]);
      fog_refresh(cube_models[count], fog_shaders[count], color2profile(type_color(index2type(count), spectral_profile, chromatic_profile)),
                  fog_density_loc, fog_density);

    }
    else
    { loading = false; }

    ++count;
  }
}
