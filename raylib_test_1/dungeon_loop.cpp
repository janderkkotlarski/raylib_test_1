#include "dungeon_loop.h"

#include <cassert>
#include <iostream>
#include <time.h>

#include "misc_functions.h"
#include "keybindings.h"

dungeon_loop::dungeon_loop()
noexcept
  :  m_type_volume(), m_fracta_cube(), m_int_vectors()
{
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
            else if((abs(count_x) > m_free ||
                     abs(count_y) > m_free ||
                     abs(count_z) > m_free) &&
                    (abs(count_x) % 2 == 1 ||
                     abs(count_y) % 2 == 1 ||
                     abs(count_z) % 2 == 1) &&
                     rand() % 100 < m_wall_perc)
            { c_type = cube_type::concrete; }

            if (count_x == 0)
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

  m_type_volume[-1 + m_dungeon_radius]
               [0 + m_dungeon_radius]
               [0 + m_dungeon_radius] = cube_type::special;

  if(m_test)
  {
    m_type_volume[0 + m_dungeon_radius]
                 [2 + m_dungeon_radius]
                 [2 + m_dungeon_radius] = cube_type::none;
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
  { index += m_dungeon_span; }

  while (index > m_dungeon_radius)
  { index -= m_dungeon_span; }

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

void dungeon_loop::play_actions(Camera &camera)
noexcept
{
  m_cube_dungeon_pos = { coordinator(m_position.x),
                         coordinator(m_position.y),
                         coordinator(m_position.z) };

  if (m_act == action::none)
  {
    m_act = key_bind_actions();

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
                   [m_cube_dungeon_pos[2]] == cube_type::special)
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

void dungeon_loop::cube_drawing()
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
            m_fracta_cube.display(m_position, m_decay, m_multiplier);
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

  Camera3D camera;

  camera_init(camera);

  while (m_game)
  {
    m_loop = true;

    dungeon_fill();
    collide();

    while (m_loop)
    {
      play_actions(camera);

      BeginDrawing();
      {
        ClearBackground(Color{ BLACK });

        BeginVrDrawing();
        BeginMode3D(camera);

        { cube_drawing(); }

        EndMode3D();
        EndVrDrawing();

        // if (m_test)
        // { infos(); }

        pos_direct_display();

      }
      EndDrawing();
    }
  }

  UnloadShader(distortion);

  CloseVrSimulator();         // Close VR simulator

  CloseWindow();
}
