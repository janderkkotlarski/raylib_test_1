#include "dungeon_loop.h"

#include <cassert>
#include <iostream>
#include <time.h>

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

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

  for(int count_x{ -m_dungeon_radius }; count_x <= m_dungeon_radius; ++count_x)
  {
    std::vector <std::vector <cube_type>> area;

    for(int count_y{ -m_dungeon_radius }; count_y <= m_dungeon_radius; ++count_y)
    {
      std::vector <cube_type> line;

      for(int count_z{ -m_dungeon_radius }; count_z <= m_dungeon_radius; ++count_z)
      { line.push_back(cube_type::none); }

      assert(line.size() == unsigned(m_dungeon_span));

      area.push_back(line);
    }

    assert(area.size() == unsigned(m_dungeon_span));

    m_type_volume.push_back(area);
  }

  assert(m_type_volume.size() == unsigned(m_dungeon_span));

}

void dungeon_loop::dungeon_fill()
noexcept
{
  m_directions = m_start_directs;

  m_position = Vector3Scale(m_start_posit, m_multiplier);

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
            { c_type = cube_type::concrete; }

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

  std::vector <int> coords
  { 1, 1, 1 };

  while ((abs(coords[0]) <= m_horizon ||
          abs(coords[1]) <= m_horizon ||
          abs(coords[2]) <= m_horizon) &&
         (abs(coords[0]) % 2 != 0 ||
          abs(coords[1]) % 2 != 0 ||
          abs(coords[2]) % 2 != 0))
  {
    for (int &coord: coords)
    { coord = (rand() % (2*m_dungeon_radius)) - m_dungeon_radius; }
  }

  m_type_volume[unsigned(coords[0]) + m_dungeon_radius]
               [unsigned(coords[1]) + m_dungeon_radius]
               [unsigned(coords[2]) + m_dungeon_radius] = cube_type::none;

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

      if (type_collision(m_type_volume[posit[0]][posit[1]][posit[2]]) &&
          m_act == direct2action(directs, dir))
      { m_act = action::none; }
    }
  }
}

action dungeon_loop::gamepad_input()
{
  if (IsGamepadAvailable(GAMEPAD_PLAYER1))
  {
    if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_UP))
    { return action::forward; }
  }

  return m_act;
}

void dungeon_loop::play_actions(Camera &camera)
noexcept
{
  m_cube_dungeon_pos = { coordinator(m_position.x),
                         coordinator(m_position.y),
                         coordinator(m_position.z) };

  if (m_act == action::none)
  {
    m_act = key_bind_actions();

    m_act = gamepad_input();

    if (m_act != action::none)
    { collide(); }

    m_time = 0.0f;
  }

  if (m_act != action::none)
  {
    m_delta_time = GetFrameTime();
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

  m_velocity = m_delta_time*m_speed;
  m_theta = m_delta_time*m_angle;
  spectral_shift(m_spectral_profile, m_delta_time);

  movetate();

  wrapping(m_position, m_wrap);

  camera.position = m_position;

  camera.target = Vector3Add(m_position, m_directions[0]);
  camera.up = m_directions[2];


  if (IsKeyDown(KEY_BACKSPACE))
  { m_loop = false; }

  if (WindowShouldClose())
  {
    m_loop = false;
    m_game = false;
  }

  if (m_act == action::none &&
      m_type_volume[m_cube_dungeon_pos[0]]
                   [m_cube_dungeon_pos[1]]
                   [m_cube_dungeon_pos[2]] == cube_type::next)
  { m_loop = false; }

  if (IsKeyPressed(KEY_SPACE))
  {
    ToggleVrMode();

    m_display_info = !m_display_info;
  }   // Toggle VR mode
}

void dungeon_loop::infos()
noexcept
{
  DrawFPS(20, 20);


  if (m_display_info)
  {
    const int x
    { 20 };
    int y
    { 40 };

    const int step
    { 60 };
    const int size
    { 20 };

    int count
    { 0 };

    for (const Vector3 &direction: m_directions)
    {
      display_string_vector(vector3_to_strings(direction),
                            "Direction" + std::to_string(count), x, y, size);
      y += step;
      ++count;
    }
  }
  else
  { DrawFPS(650, 20); }
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

void dungeon_loop::cube_drawing(Model &cube_model)
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

        if (c_type != cube_type::none)
        {
          m_fracta_cube.set_pos_type(m_coord_int[0], m_coord_int[1], m_coord_int[2], c_type);

          if (display_selector(m_position,
                               Vector3Scale(m_fracta_cube.get_position(), m_multiplier),
                               m_directions[0], m_cam_field, m_multiplier))
          {
            m_fracta_cube.display(cube_model, m_spectral_profile);
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

void dungeon_loop::run()
{
  InitWindow(m_screen_width, m_screen_height, "Cube Dungeon");

  Shader distortion
  { LoadShader(0, FormatText("resources/distortion%i.fs", GLSL_VERSION)) };

  stereoscope_init(distortion);

  Shader shader = LoadShader(FormatText("C:/raylib/raylib/examples/shaders/resources/shaders/glsl330/base_lighting.vs", GLSL_VERSION),
                             FormatText("C:/raylib/raylib/examples/shaders/resources/shaders/glsl330/dark_fog.fs", GLSL_VERSION));
  shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");
  shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

  Camera3D camera;

  camera_init(camera);

  Model cube_model
  { LoadModelFromMesh(GenMeshCube(m_fracta_cube.get_cube_dims().x,
                                  m_fracta_cube.get_cube_dims().y,
                                  m_fracta_cube.get_cube_dims().z)) };

  const float array4[4]
  { 0.0f, 0.0f, 0.0f, 1.0f };

  int ambientLoc = GetShaderLocation(shader, "ambient");
  SetShaderValue(shader, float(ambientLoc), array4, UNIFORM_VEC4);

  float fogDensity = 0.005f;
  int fogDensityLoc = GetShaderLocation(shader, "fogDensity");
  SetShaderValue(shader, fogDensityLoc, &fogDensity, UNIFORM_FLOAT);

  cube_model.materials[0].shader = shader;

  Light light
  { CreateLight(LIGHT_POINT, m_position, Vector3Zero(), WHITE, shader) };

  // CreateLight(LIGHT_POINT, m_position, Vector3Zero(), WHITE, shader);

  while (m_game)
  {
    m_loop = true;

    dungeon_fill();
    collide();

    while (m_loop)
    {
      SetShaderValue(shader, fogDensityLoc, &fogDensity, UNIFORM_FLOAT);

      SetShaderValue(shader, shader.locs[LOC_VECTOR_VIEW], &m_position.x, UNIFORM_VEC3);

      play_actions(camera);

      light.position = m_position;

      UpdateLightValues(shader, light);

      BeginDrawing();
      {
        ClearBackground(BLACK);

        BeginVrDrawing();
        BeginMode3D(camera);

        { cube_drawing(cube_model); }

        EndMode3D();
        EndVrDrawing();

        if (m_test)
        { infos(); }

        pos_direct_display();

      }
      EndDrawing();
    }
  }

  UnloadShader(distortion);

  CloseVrSimulator();         // Close VR simulator

  CloseWindow();
}
