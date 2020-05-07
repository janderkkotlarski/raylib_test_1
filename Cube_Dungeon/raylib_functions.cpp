#include "raylib_functions.h"

#include "cube_type.h"

void fog_init(Shader &fog_shader)
noexcept
{
  fog_shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(fog_shader, "matModel");
  fog_shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(fog_shader, "viewPos");
}

void init_cubes_images_fogs(dungeon_loop &d_loop,
                            std::vector <Model> &cube_models,
                            std::vector <Image> &face_images,
                            std::vector <Shader> &fog_shaders,
                            const fractacube &f_cube,
                            const std::string &file_name,
                            const std::string &file_type,
                            const Vector3 &spectral_profile,
                            const Vector3 &chromatic_profile)
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
      d_loop.fog_refresh(cube_models[count], fog_shaders[count], color2profile(type_color(index2type(count), spectral_profile, chromatic_profile)));

    }
    else
    { loading = false; }

    ++count;
  }
}
