#include "dungeon_loop.h"

#include <cassert>
#include <iostream>
#include <time.h>

#define RLIGHTS_IMPLEMENTATION
#include <rlights.h>

#include "misc_functions.h"
#include "keybindings.h"

dungeon_loop::dungeon_loop()
noexcept
  :  m_type_volume(), m_fracta_cube(m_multiplier), m_int_vectors()
{
  assert(m_multiplier > 0.0f);

  dungeon_init();
}

std::vector <int> dungeon_loop::pos_intifier()
noexcept
{
  return { int(round(m_position.x/m_multiplier)),
           int(round(m_position.y/m_multiplier)),
           int(round(m_position.z/m_multiplier)) } ;
}

void dungeon_loop::stereoscope_init(Shader &distortion)
noexcept
{
  distortion = LoadShader(0, FormatText("distortion.fs", GLSL_VERSION));

  SetConfigFlags(FLAG_MSAA_4X_HINT);// VR device parameters (head-mounted-device)

  InitVrSimulator();

  VrDeviceInfo hmd = { 0 };

  // Oculus Rift CV1 parameters for simulator
  hmd.hResolution = 2000;                 // HMD horizontal resolution in pixels
  hmd.vResolution = 1200;  // 1200               // HMD vertical resolution in pixels
  hmd.hScreenSize = 0.133793f;  // 0.133793f;            // HMD horizontal size in meters
  hmd.vScreenSize = 0.0669f;              // HMD vertical size in meters
  hmd.vScreenCenter = 0.04678f;           // HMD screen center in meters
  hmd.eyeToScreenDistance = 0.041f;       // HMD distance between eye and display in meters
  hmd.lensSeparationDistance = 0.07f;     // HMD lens separation distance in meters
  hmd.interpupillaryDistance = 0.07f;     // HMD IPD (distance between pupils) in meters

  // NOTE: CV1 uses a Fresnel-hybrid-asymmetric lenses with specific distortion compute shaders.
  // Following parameters are an approximation to distortion stereo rendering but results differ from actual device.
  hmd.lensDistortionValues[0] = 1.0f;     // HMD lens distortion constant parameter 0
  hmd.lensDistortionValues[1] = 0.22f;    // HMD lens distortion constant parameter 1
  hmd.lensDistortionValues[2] = 0.24f;    // HMD lens distortion constant parameter 2
  hmd.lensDistortionValues[3] = 0.0f;     // HMD lens distortion constant parameter 3
  hmd.chromaAbCorrection[0] = 0.996f;     // HMD chromatic aberration correction parameter 0
  hmd.chromaAbCorrection[1] = -0.004f;    // HMD chromatic aberration correction parameter 1
  hmd.chromaAbCorrection[2] = 1.014f;     // HMD chromatic aberration correction parameter 2
  hmd.chromaAbCorrection[3] = 0.0f;       // HMD chromatic aberration correction parameter 3

  SetVrConfiguration(hmd, distortion);    // Set Vr device parameters for stereo rendering

  ToggleVrMode();

  SetTargetFPS(fps);  // Set our game to run at fps frames-per-second
}

void dungeon_loop::fog_init(Model &cube_model,
                            Shader &fogger,
                            const int fog_density_loc)
noexcept
{

  const float ambient_loc
  { (float)GetShaderLocation(fogger, "ambient") };

  fogger.locs[LOC_MATRIX_MODEL] = GetShaderLocation(fogger, "matModel");
  fogger.locs[LOC_VECTOR_VIEW] = GetShaderLocation(fogger, "viewPos");


  SetShaderValue(fogger, ambient_loc, m_fog_color, UNIFORM_VEC4);
  SetShaderValue(fogger, fog_density_loc, &m_fog_density, UNIFORM_FLOAT);

  cube_model.materials[0].shader = fogger;
}

void dungeon_loop::camera_init(Camera &camera)
noexcept
{
  camera.position = m_position; // Camera position
  camera.target = Vector3Add(m_position, m_directions[0]); // Vector3Add(camera.position, forward);      // Camera looking at point
  camera.up = m_directions[2];          // Camera up vector (rotation towards target)
  camera.fovy = m_cam_angle;                                // Camera field-of-view Y
  camera.type = CAMERA_PERSPECTIVE; // Camera mode type

  SetCameraMode(camera, CAMERA_FREE);
}

void dungeon_loop::dungeon_init()
noexcept
{
  assert(m_directions.size() == 3);

  srand (time(NULL));

  for(int count_x{ -m_max_dungeon_radius }; count_x <= m_max_dungeon_radius; ++count_x)
  {
    std::vector <std::vector <cube_type>> area;

    for(int count_y{ -m_max_dungeon_radius }; count_y <= m_max_dungeon_radius; ++count_y)
    {
      std::vector <cube_type> line;

      for(int count_z{ -m_max_dungeon_radius }; count_z <= m_max_dungeon_radius; ++count_z)
      { line.push_back(cube_type::none); }

      assert(line.size() == unsigned(2*m_max_dungeon_radius + 1));

      area.push_back(line);
    }

    assert(area.size() == unsigned(2*m_max_dungeon_radius + 1));

    m_type_volume.push_back(area);
  }

  assert(m_type_volume.size() == unsigned(2*m_max_dungeon_radius + 1));
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

  m_dungeon_span = 2*m_dungeon_radius + 1;
  m_wrap = m_multiplier*(m_dungeon_radius + 0.5f);

  m_start_posit = (Vector3){ 1.0f - (float)m_dungeon_radius, 0.0f, 0.0f };

  m_reset = false;

  if (m_level > m_end_level)
  {
    m_loop = false;
    m_game = false;
  }

  m_directions = m_start_directs;

  m_position = Vector3Scale(m_start_posit, m_multiplier);
}

void dungeon_loop::dungeon_fill()
noexcept
{
  for(int count_x{ -m_dungeon_radius }; count_x <= m_dungeon_radius; ++count_x)
  {
    std::vector <std::vector <cube_type>> area;

    for(int count_y{ -m_dungeon_radius }; count_y <= m_dungeon_radius; ++count_y)
    {
     std::vector <cube_type> line;

      for(int count_z{ -m_dungeon_radius }; count_z <= m_dungeon_radius; ++count_z)
      {
        {
          cube_type c_type
          { cube_type::none };

          if (m_simple)
          {
            if (count_x == m_cube_pos[0] &&
                count_y == m_cube_pos[1] &&
                count_z == m_cube_pos[2])
            { c_type = cube_type::alabaster; }

            if (abs(count_x) == m_dungeon_radius ||
                abs(count_y) == m_dungeon_radius ||
                abs(count_z) == m_dungeon_radius)
            { c_type = cube_type::invisible; }
          }
          else
          {
            if ((abs(count_x) % 2 == 1 &&
                 abs(count_y) % 2 == 1) ||
                (abs(count_x) % 2 == 1 &&
                 abs(count_z) % 2 == 1) ||
                (abs(count_z) % 2 == 1 &&
                 abs(count_y) % 2 == 1))
            { c_type = cube_type::concrete; }
            else if((abs(count_x) % 2 == 1 ||
                     abs(count_y) % 2 == 1 ||
                     abs(count_z) % 2 == 1) &&
                     rand() % 100 < m_wall_perc)
            { c_type = cube_type::none; }

            if (abs(count_x) == m_dungeon_radius ||
                abs(count_y) == m_dungeon_radius ||
                abs(count_z) == m_dungeon_radius)
            { c_type = cube_type::concrete; }
          }

          m_type_volume[count_x + m_dungeon_radius]
                       [count_y + m_dungeon_radius]
                       [count_z + m_dungeon_radius] = c_type;
        }
      }      
    }
  }
}


void dungeon_loop::begin_end()
noexcept
{
  for (unsigned sign { 0 }; sign < 2; ++sign)
  {
    m_type_volume[2*m_dungeon_radius - 3 + 2*sign]
                 [0 + m_dungeon_radius]
                 [0 + m_dungeon_radius] = cube_type::none;

    m_type_volume[2*m_dungeon_radius - 2]
                 [-1 + m_dungeon_radius + 2*sign]
                 [0 + m_dungeon_radius] = cube_type::none;

    m_type_volume[2*m_dungeon_radius - 2]
                 [0 + m_dungeon_radius]
                 [-1 + m_dungeon_radius + 2*sign] = cube_type::none;
  }

  m_type_volume[2*m_dungeon_radius - 1]
               [0 + m_dungeon_radius]
               [0 + m_dungeon_radius] = cube_type::next;

  for (unsigned sign { 0 }; sign < 2; ++sign)
  {
    m_type_volume[1 + 2*sign]
                 [0 + m_dungeon_radius]
                 [0 + m_dungeon_radius] = cube_type::none;

    m_type_volume[2]
                 [-1 + m_dungeon_radius + 2*sign]
                 [0 + m_dungeon_radius] = cube_type::none;

    m_type_volume[2]
                 [0 + m_dungeon_radius]
                 [-1 + m_dungeon_radius + 2*sign] = cube_type::none;
  }
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

        if (type_collision(m_collide_type))
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
  if (IsKeyDown(KEY_BACKSPACE) ||
      IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_MIDDLE_RIGHT))
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

  if ((IsKeyPressed(KEY_SPACE) ||
      IsGamepadButtonReleased(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_THUMB)) &&
      false)
  {
    ToggleVrMode();

    m_display_info = !m_display_info;
  }   // Toggle VR mode
}

void dungeon_loop::player_move(Camera &camera,
                               Shader &fogger,
                               const int fog_density_loc)
noexcept
{
  m_velocity = m_delta_time*m_speed;
  m_theta = m_delta_time*m_angle;

  spectral_shift(m_spectral_profile, m_delta_time);
  // dark_shift(m_dark_profile, m_delta_time);

  movetate();
  wrapping(m_position, m_wrap);

  camera.position = m_position;
  camera.target = Vector3Add(m_position, m_directions[0]);
  camera.up = m_directions[2];

  SetShaderValue(fogger, fog_density_loc, &m_fog_density, UNIFORM_FLOAT);
  SetShaderValue(fogger, fogger.locs[LOC_VECTOR_VIEW], &m_position.x, UNIFORM_VEC3);
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

void dungeon_loop::cube_drawing(Model &cube_model, std::vector <Model> &cube_models)
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
        {  m_dungeon_index[ind] = unsigned(m_index_int[ind] + m_dungeon_radius); }

        const cube_type c_type
        { m_type_volume[m_dungeon_index[0]]
                       [m_dungeon_index[1]]
                       [m_dungeon_index[2]] };

        if (c_type != cube_type::none &&
            c_type != cube_type::invisible)
        {
          m_fracta_cube.set_pos_type(m_coord_int[0], m_coord_int[1], m_coord_int[2], c_type);

          if (display_selector(m_position,
                               Vector3Scale(m_fracta_cube.get_position(), m_multiplier),
                               m_directions[0], m_cam_field, m_multiplier))
          {
            if (m_moving_sprite)
            {
              m_fracta_cube.display(cube_models[m_cube_index], m_spectral_profile, m_screen_opacity);


            }
            else
            { m_fracta_cube.display(cube_model, m_spectral_profile, m_screen_opacity); }
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
    { type_color(m_collide_type, m_spectral_profile) };

    scale_color(screen_color, m_light_intensity);
    scale_color(screen_color, 2.5f);

    change_opacity(screen_color, 4.0f*m_screen_opacity);

    for (int count{ 0 }; count < 5; ++count)
    { DrawRectangle(0, 0, m_screen_width, m_screen_height, screen_color); }
  }

  dark_shift(m_dark_color, m_delta_time, m_dark_opacity, m_dark_up);

  DrawRectangle(0, 0, m_screen_width, m_screen_height, m_dark_color);
}

void dungeon_loop::game_loop(Camera &camera, std::vector <Model> &cube_models,
                             Model &cube_model, std::vector <Texture> &textures,
                             Texture &texture,
                             Shader &fogger,
                             Light &light,
                             const int fog_density_loc)
noexcept
{
  while (m_game)
  {
    cube_model.materials[0].maps[MAP_DIFFUSE].texture = texture;

    for (unsigned count{ 0 }; count < cube_models.size(); ++count)
    { cube_models[count].materials[0].maps[MAP_DIFFUSE].texture = textures[count]; }

    level_init();
    dungeon_fill();
    begin_end();
    collide();

    while (m_loop)
    {
      player_move(camera, fogger, fog_density_loc);
      play_actions();
      other_actions();

      light.position = m_position;
      UpdateLightValues(fogger, light);

      BeginDrawing();
      {
        ClearBackground(BLACK);

        // BeginVrDrawing();
        BeginMode3D(camera);
        { cube_drawing(cube_model, cube_models); }

        EndMode3D();
        // EndVrDrawing();

        if (m_test)
        { infos(); }

        pos_direct_display();        
        transition();

        frame_update(cube_models);

        infos();
      }

      EndDrawing();
    }
  }
}

void dungeon_loop::run_window()
{
  InitWindow(m_screen_width, m_screen_height, "Cube Dungeon");

  // Shader distortion;
  // stereoscope_init(distortion);

  const std::string file_name
  { "sprite_" };

  const std::string file_type
  { ".png" };

  std::vector <Model> cube_models;

  std::vector <Texture> textures;

  for (int count{ 0 }; count < 16; ++count)
  {
    cube_models.push_back(LoadModelFromMesh(GenMeshCube(m_fracta_cube.get_cube_dims().x,
                                                        m_fracta_cube.get_cube_dims().y,
                                                        m_fracta_cube.get_cube_dims().z)));

    const std::string file_name_type
    { file_name + std::to_string(count) + file_type };

    textures.push_back(LoadTexture(file_name_type.c_str()));
  }


  Model cube_model
  { LoadModelFromMesh(GenMeshCube(m_fracta_cube.get_cube_dims().x,
                                  m_fracta_cube.get_cube_dims().y,
                                  m_fracta_cube.get_cube_dims().z)) };

  Texture texture = LoadTexture("zAG2xTS.gif");

  Shader fogger
  { LoadShader(FormatText("base_lighting.vs", GLSL_VERSION),
               FormatText("dark_fog.fs", GLSL_VERSION)) };

  const int fog_density_loc
  { GetShaderLocation(fogger, "fogDensity") };
  fog_init(cube_model, fogger, fog_density_loc);

  for (Model &c_model: cube_models)
  { fog_init(c_model, fogger, fog_density_loc); }

  Light light
  { CreateLight(LIGHT_POINT, m_position, Vector3Zero(), m_light_color, fogger) };

  Camera3D camera;
  camera_init(camera);

  game_loop(camera, cube_models, cube_model, textures, texture, fogger, light, fog_density_loc);

  // UnloadShader(distortion);

  CloseVrSimulator();         // Close VR simulator

  CloseWindow();
}
