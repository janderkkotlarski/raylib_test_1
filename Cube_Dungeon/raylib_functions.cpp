#include "raylib_functions.h"

#include "cube_type.h"



void fog_init(Shader &fog_shader,
              const std::vector <float> &fog_profile)
noexcept
{
  fog_shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(fog_shader, "matModel");
  fog_shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(fog_shader, "viewPos");

  const float ambient_loc
  { (float)GetShaderLocation(fog_shader, "ambient") };

  SetShaderValue(fog_shader, ambient_loc, &fog_profile, UNIFORM_VEC4);
}

void fog_refresh(Shader &fog_shader,
                 const Vector3 &position,
                 const int fog_density_loc,
                 const float fog_density)
noexcept
{
  SetShaderValue(fog_shader, fog_density_loc, &fog_density, UNIFORM_FLOAT);
  SetShaderValue(fog_shader, fog_shader.locs[LOC_VECTOR_VIEW], &position.x, UNIFORM_VEC3);  
}

void refresh_fogs(std::vector <Model> &cube_models,
                  std::vector <Shader> &fog_shaders,
                  const Vector3 &position,
                  const int fog_density_loc,
                  const float fog_density)
 noexcept
{
  for (unsigned count{ 0 }; count < cube_models.size(); ++count)
  {
    fog_refresh(fog_shaders[count], position,
                fog_density_loc, fog_density);
  }
}

void init_cubes_images_fogs(std::vector <Model> &cube_models,
                            std::vector <Image> &face_images,
                            std::vector <Shader> &fog_shaders,
                            const Vector3 &position,
                            const std::vector <float> &fog_profile,
                            const fractacube &f_cube,
                            const std::string &file_name,
                            const std::string &file_type,
                            const int fog_density_loc,
                            const float fog_density)
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

      cube_models.push_back(LoadModelFromMesh(GenMeshCube(f_cube.get_cube_dims().x,
                                                          f_cube.get_cube_dims().y,
                                                          f_cube.get_cube_dims().z)));

      cube_models[count].materials[0].maps[MAP_DIFFUSE].texture = LoadTextureFromImage(face_images[count]);

      fog_shaders.push_back(LoadShader(FormatText("base_lighting.vs", GLSL_VERSION),
                                       FormatText("dark_fog.fs", GLSL_VERSION)));

      fog_init(fog_shaders[count], fog_profile);

      fog_refresh(fog_shaders[count], position, fog_density_loc, fog_density);
      cube_models[count].materials[0].shader = fog_shaders[count];

    }
    else
    { loading = false; }

    ++count;
  }
}
