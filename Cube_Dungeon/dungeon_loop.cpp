#include "dungeon_loop.h"

#include <cassert>
#include <iostream>
#include <time.h>

#define RLIGHTS_IMPLEMENTATION
#include <rlights.h>

#include "keybindings.h"
#include "dungeon_maze.h"
#include "raylib_functions.h"

dungeon_loop::dungeon_loop()
noexcept
  :  m_type_volume(), m_fracta_cube(m_multiplier), m_int_vectors()
{
  assert(m_multiplier > 0.0f);
  assert(m_directions.size() == 3);

  // acid_trip(m_cam_angle_average, m_cam_angle_deviation, m_cam_angle, m_dark_opacity);

  dungeon_init(m_type_volume, m_max_dungeon_radius);
}

std::vector <int> dungeon_loop::pos_intifier()
noexcept
{
  return { int(round(m_position.x/m_multiplier)),
           int(round(m_position.y/m_multiplier)),
           int(round(m_position.z/m_multiplier)) } ;
}

void dungeon_loop::camera_init(Camera &camera)
noexcept
{
  camera_position(camera); // Camera position
  camera.target = Vector3Add(m_position, m_directions[0]); // Vector3Add(camera.position, forward);      // Camera looking at point
  camera.up = m_directions[2];          // Camera up vector (rotation towards target)
  camera.fovy = m_cam_angle;                                // Camera field-of-view Y
  camera.type = CAMERA_PERSPECTIVE; // Camera mode type

  SetCameraMode(camera, CAMERA_FIRST_PERSON);

  SetTargetFPS(fps);
}

void dungeon_loop::player_init()
noexcept
{
  m_start_posit = (Vector3){ 1.0f - (float)m_dungeon_radius, 0.0f, 0.0f };

  m_directions = m_start_directs;

  m_position = Vector3Scale(m_start_posit, m_multiplier);
}

void dungeon_loop::level_init()
noexcept
{  
  m_loop = true;

  if (!m_reset)
  {
    if (m_level > 0)
    {
      m_dungeon_radius += 2;
      ++m_wall_perc;
    }

    ++m_level;
  }

  m_reset = false;

  if (m_level > m_end_level)
  {
    m_loop = false;
    m_game = false;
  }

  m_dungeon_span = 2*m_dungeon_radius + 1;
  m_wrap = m_multiplier*(m_dungeon_radius + 0.5f);

  player_init();
}

void dungeon_loop::movetate()
noexcept
{
  switch (m_act)
  {
    case action::forward:
      m_position = Vector3Add(m_position, Vector3Scale(m_directions[0], m_velocity));
      break;
    case action::backward:
      m_position = Vector3Subtract(m_position, Vector3Scale(m_directions[0], m_velocity));
      break;
    case action::right:
      m_position = Vector3Add(m_position, Vector3Scale(m_directions[1], m_velocity));
      break;
    case action::left:
      m_position = Vector3Subtract(m_position, Vector3Scale(m_directions[1], m_velocity));
      break;
    case action::up:
      m_position = Vector3Add(m_position, Vector3Scale(m_directions[2], m_velocity));
      break;
    case action::down:
      m_position = Vector3Subtract(m_position, Vector3Scale(m_directions[2], m_velocity));
      break;

    case action::rotate_right:
      rotate_first_second(m_directions[0], m_directions[1], m_theta);
      break;
    case action::rotate_left:
      rotate_first_second(m_directions[1], m_directions[0], m_theta);
      break;
    case action::rotate_up:
      rotate_first_second(m_directions[0], m_directions[2], m_theta);
      break;
    case action::rotate_down:
      rotate_first_second(m_directions[2], m_directions[0], m_theta);
      break;
    case action::roll_right:
      rotate_first_second(m_directions[2], m_directions[1], m_theta);
      break;
    case action::roll_left:
      rotate_first_second(m_directions[1], m_directions[2], m_theta);
      break;
  }
}

int dungeon_loop::dungeon_wrap(const int coord)
noexcept
{
  int index = coord;

  while (index < -m_dungeon_radius)
  {
    // index += m_dungeon_span;
    index = 0;
  }

  while (index > m_dungeon_radius)
  {
    // index -= m_dungeon_span;
    index = 0;
  }

  return index;
}

int dungeon_loop::dungeon_warp(const int coord)
noexcept
{
  int index = coord;

  while (index < 0)
  { index += m_dungeon_span; }

  while (index >= m_dungeon_span)
  { index -= m_dungeon_span; }

  return index;
}

int dungeon_loop::coordinator(const float pos)
noexcept
{ return int(round(pos/m_multiplier)) + m_dungeon_radius; }

std::vector <std::vector <int>> dungeon_loop::director()
noexcept
{
  std::vector <std::vector <int>> directs;

  for (const Vector3 &direction: m_directions)
  {
    std::vector <int> direct;

    direct.push_back(int(round(direction.x)));
    direct.push_back(int(round(direction.y)));
    direct.push_back(int(round(direction.z)));

    directs.push_back(direct);
  }

  assert(directs.size() == m_directions.size());

  return directs;
}

void dungeon_loop::collide()
noexcept
{
  std::vector <std::vector <int>> directs
  { director() };

  for (const std::vector <int> &direct: directs)
  {   
    for (int sign{ 1 }; sign >= -1; sign -=2)
    {
      const std::vector dir
      { scale_int_vector(direct, sign) };

      std::vector <int> posit
      { add_int_vector(m_cube_dungeon_pos, dir) };

      for (int &part: posit)
      { part = dungeon_warp(part); }

      if (m_act == direct2action(directs, dir))
      {
        m_collide_type = m_type_volume[posit[0]][posit[1]][posit[2]];

        if(type_collision(m_collide_type))
        { m_act = action::none; }
      }
    }
  }
}

void dungeon_loop::play_actions()
noexcept
{
  m_cube_dungeon_pos = { coordinator(m_position.x),
                         coordinator(m_position.y),
                         coordinator(m_position.z) };

  if (m_cube_dungeon_pos ==
      (std::vector <int>){ coordinator(m_multiplier*m_start_posit.x),
                           coordinator(m_multiplier*m_start_posit.y),
                           coordinator(m_multiplier*m_start_posit.z) })

  { m_collide_type = cube_type::none; }

  if (m_act == action::none)
  {
    m_act = key_bind_actions();
    gamepad_actions(m_act);

    if (m_act != action::none)
    { collide(); }

    m_time = 0.0f;
  }

  m_delta_time = GetFrameTime();

  if (m_act != action::none)
  {
    m_time += m_delta_time;

    if (m_time >= m_period)
    {
      m_act = action::none;

      m_position.x = m_multiplier*round(m_position.x/m_multiplier);
      m_position.y = m_multiplier*round(m_position.y/m_multiplier);
      m_position.z = m_multiplier*round(m_position.z/m_multiplier);

      for (Vector3 &direction: m_directions)
      {
        direction.x = round(direction.x);
        direction.y = round(direction.y);
        direction.z = round(direction.z);
      }
    }
  }
}

void dungeon_loop::other_actions()
noexcept
{
  if (IsKeyReleased(KEY_BACKSPACE) ||
      IsGamepadButtonReleased(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_MIDDLE_RIGHT))
  {
    m_loop = false;
    m_reset = true;
    m_act = action::none;
  }

  if (WindowShouldClose() ||
      IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_MIDDLE_LEFT))
  {
    m_loop = false;
    m_game = false;
    m_act = action::none;
  }

  if (m_act == action::none &&
      m_type_volume[m_cube_dungeon_pos[0]]
                   [m_cube_dungeon_pos[1]]
                   [m_cube_dungeon_pos[2]] == cube_type::next)
  { m_loop = false; }

  if (m_act == action::none &&
      m_type_volume[m_cube_dungeon_pos[0]]
                   [m_cube_dungeon_pos[1]]
                   [m_cube_dungeon_pos[2]] == cube_type::setback)
  {
    m_type_volume[m_cube_dungeon_pos[0]]
                 [m_cube_dungeon_pos[1]]
                 [m_cube_dungeon_pos[2]] = cube_type::none;

    player_init();
  }  
}

void dungeon_loop::test_cheats()
noexcept
{
  if (IsKeyReleased(KEY_RIGHT_BRACKET))
  { m_loop = false; }

  if (IsKeyReleased(KEY_LEFT_BRACKET))
  {
    m_loop = false;

    m_level -= 2;

    if (m_level < 0)
    { m_level = 0; }
  }
}

void dungeon_loop::player_move(Camera &camera)
noexcept
{
  m_velocity = m_delta_time*m_speed;
  m_theta = m_delta_time*m_angle;

  spectral_shift(m_spectral_profile, m_delta_time);
  // dark_shift(m_dark_profile, m_delta_time);

  chromatic_shift(m_chromatic_profile, m_delta_time);

  movetate();
  wrapping(m_position, m_wrap);

  camera_position(camera);
  camera.target = Vector3Add(m_position, m_directions[0]);
  camera.up = m_directions[2];
  camera.fovy = m_cam_angle;
}

void dungeon_loop::infos()
noexcept
{
  const int x
  { 20 };
  int y
  { 20 };
  const int size
  { 20 };

  display_string(std::to_string(m_level), "Level ", x, y, size);

  y += 30;

  display_string("FPS: ", std::to_string(GetFPS()), x, y, size);

}

void dungeon_loop::pos_direct_display()
noexcept
{
  if (m_int_vectors.size() > 0)
  {

  }
}

void dungeon_loop::coord_transform(const std::vector <int> &counters,
                                   const int index)
noexcept
{
  m_coord_int[index] = m_pos_int[index] + counters[index];
  m_index_int[index] = dungeon_wrap(m_coord_int[index]);
}

void dungeon_loop::frame_update(std::vector <Model> &cube_models)
noexcept
{
  ++m_frame;

  if (m_frame >= m_frames)
  {
    m_frame = 0;

    ++m_cube_index;

    if (m_cube_index >= cube_models.size())
    { m_cube_index = 0; }
  }
}

void dungeon_loop::cube_drawing(std::vector <Model> &cube_models,
                                std::vector <Model> &dark_models,
                                Model &model)
noexcept
{
  m_pos_int = pos_intifier();

  unsigned index
  { 0 };

  std::vector <int> counters
  { -m_horizon,  -m_horizon,  -m_horizon};

  for (; counters[index] <= m_horizon; ++counters[index])
  {
    coord_transform(counters, index);

    ++index;

    for (; counters[index] <= m_horizon; ++counters[index])
    {
      coord_transform(counters, index);

      ++index;

      for (; counters[index] <= m_horizon; ++counters[index])
      {
        coord_transform(counters, index);

        const std::vector <int> dungeon_pos;

        for (unsigned ind{ 0 }; ind < 3; ++ind)
        { m_dungeon_index[ind] = unsigned(m_index_int[ind] + m_dungeon_radius); }

        const cube_type c_type
        { m_type_volume[m_dungeon_index[0]]
                       [m_dungeon_index[1]]
                       [m_dungeon_index[2]] };

        if (c_type != cube_type::none &&
            c_type != cube_type::invisible &&
            c_type != cube_type::transparent)
        {
          m_fracta_cube.set_pos_type(m_coord_int[0], m_coord_int[1], m_coord_int[2], c_type);

          const unsigned c_index
          { type2index(c_type) };

          if (display_selector(m_position,
                               Vector3Scale(m_fracta_cube.get_position(), m_multiplier),
                               m_directions[0], m_cam_field, m_multiplier))
          {
            if (index != 42)
            {
              const Color cubes_color
              { type_color(c_type, m_spectral_profile, m_chromatic_profile) };



              // m_fracta_cube.display(cube_models[c_index], dark_models[c_index], m_spectral_profile, m_chromatic_profile, m_dark_color, m_screen_opacity);

              m_fracta_cube.display(model, model, m_spectral_profile, m_chromatic_profile, m_dark_color, m_screen_opacity);
            }
          }
        }
      }

      counters[index] = -m_horizon;
      --index;
    }

    counters[index] = -m_horizon;
    --index;
  }
}

void dungeon_loop::transition()
noexcept
{
  m_screen_opacity = 0.0f;

  if (transit(m_collide_type))
  {
    m_screen_opacity = m_time/m_period;

    Color screen_color
    { type_color(m_collide_type, m_spectral_profile, m_chromatic_profile) };

    scale_color(screen_color, m_light_intensity);
    scale_color(screen_color, 1.5f);

    change_opacity(screen_color, 4.0f*m_screen_opacity);

    for (int count{ 0 }; count < 3; ++count)
    { DrawRectangle(0, 0, m_screen_width, m_screen_height, screen_color); }
  }

  dark_shift(m_cube_vein_profile, m_delta_time, m_dark_opacity, m_dark_up);

  // acid_trip(m_cam_angle_average, m_cam_angle_deviation, m_cam_angle, m_dark_opacity);

  // DrawRectangle(0, 0, m_screen_width, m_screen_height, m_dark_color);
}

void dungeon_loop::game_loop(Camera &camera, std::vector <Model> &cube_models, std::vector <Model> &dark_models,
                             Model &model,
                             std::vector <Shader> &fog_shaders, std::vector <Shader> &dark_shaders,
                             Shader &shader,
                             const int fog_density_loc)
noexcept
{
  while (m_game)
  {
    // cube_model.materials[0].maps[MAP_DIFFUSE].texture = texture;

    // for (unsigned count{ 0 }; count < cube_models.size(); ++count)
    // { cube_models[count].materials[0].maps[MAP_DIFFUSE].texture = LoadTextureFromImage(images[count]); }

    level_init();
    dungeon_filler(m_type_volume, m_level, m_dungeon_radius);
    single_placements(m_type_volume, m_dungeon_radius);
    collide();

    while (m_loop)
    {
      player_move(camera);
      play_actions();

      refresh_fogs(cube_models, fog_shaders, m_position, m_fog_density_loc, m_fog_density);

      refresh_fogs(dark_models, dark_shaders, m_position, m_fog_density_loc, m_fog_density);

      const int ambientLoc = GetShaderLocation(shader, "ambient");

      float ambient_profile[4]
      { 1.0f, 1.0f, 1.0f, 1.0f };

      vector2array_float(m_chromatic_profile, ambient_profile);

      SetShaderValue(shader, ambientLoc, ambient_profile, UNIFORM_VEC4);

      SetShaderValue(shader, fog_density_loc, &m_fog_density, UNIFORM_FLOAT);
      SetShaderValue(shader, shader.locs[LOC_VECTOR_VIEW], &m_position.x, UNIFORM_VEC3);

      // fog_refresh(cube_model_dark, darker, m_cube_vein_profile, m_fog_density_loc, m_fog_density);

      BeginDrawing();
      {
        ClearBackground(BLACK);

        // BeginVrDrawing();
        BeginMode3D(camera);        
        { cube_drawing(cube_models, dark_models, model); }

        EndMode3D();
        // EndVrDrawing();

        if (m_test)
        { infos(); }

        pos_direct_display();        
        transition();

        // frame_update(cube_models);

        infos();
      }

      EndDrawing();

      other_actions();
      test_cheats();
    }
  }
}

void dungeon_loop::run_window()
{
  InitWindow(m_screen_width, m_screen_height, "Cube Dungeon");

  const std::string file_name
  { "cube_face_" };

  std::string file_type
  { ".png" };

  std::vector <Model> cube_models;

  std::vector <Image> face_images;

  std::vector <Shader> fog_shaders;

  init_cubes_images_fogs(cube_models, face_images, fog_shaders, m_position, m_ambient_profile,
                         m_fracta_cube, file_name, file_type, m_fog_density_loc, m_fog_density);

  file_type = "_.png";

  std::vector <Model> dark_models;

  std::vector <Image> dark_images;

  std::vector <Shader> dark_shaders;

  init_cubes_images_fogs(dark_models, dark_images, dark_shaders, m_position, m_ambient_profile,
                         m_fracta_cube, file_name, file_type, m_dark_density_loc, m_fog_density);

  Model c_model
  { LoadModelFromMesh(GenMeshCube(m_fracta_cube.get_cube_dims().x,
                                  m_fracta_cube.get_cube_dims().y,
                                  m_fracta_cube.get_cube_dims().z)) };



  c_model.materials[0].maps[MAP_DIFFUSE].texture = LoadTexture("cube_face_0.png");

  Shader f_shader
  { LoadShader(FormatText("base_lighting.vs", GLSL_VERSION),
               FormatText("dark_fog.fs", GLSL_VERSION)) };

  f_shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(f_shader, "matModel");
  f_shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(f_shader, "viewPos");


  const std::vector <float> ambi_profile
  { 1.0f, 1.0f, 1.0f, 1.0f };

  float ambient_profile[4]
  { 0.0f, 1.0f, 1.0f, 1.0f };

  vector2array_float(ambi_profile, ambient_profile);

  const int ambientLoc = GetShaderLocation(f_shader, "ambient");
  SetShaderValue(f_shader, ambientLoc, ambient_profile, UNIFORM_VEC4);

  const int fog_density_loc
  { GetShaderLocation(f_shader, "fogDensity") };
  SetShaderValue(f_shader, fog_density_loc, &m_fog_density, UNIFORM_FLOAT);

  c_model.materials[0].shader = f_shader;


  Camera3D camera;
  camera_init(camera);

  game_loop(camera, cube_models, dark_models, c_model,
            fog_shaders, dark_shaders, f_shader, fog_density_loc);

  // UnloadShader(distortion);

  CloseVrSimulator();         // Close VR simulator

  CloseWindow();
}
