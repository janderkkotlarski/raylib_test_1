#include "dungeon_loop.h"

#include <raymath.h>

#include "misc_functions.h"
#include "keybindings.h"

dungeon_loop::dungeon_loop()
noexcept
  : m_cube_positions(), m_fracta_cubes(), m_camera()
{
  ToggleVrMode();

  std::random_device rand;

  // for(int count{ 0 }; count < m_cube_amount; ++count)
  // { m_cube_positions.push_back(ranpos(rand, m_dist_min, m_dist_max)); }

  for(int count_x{ -m_dungeon_radius }; count_x <= m_dungeon_radius; ++count_x)
  {
    std::vector <std::vector <cube_type>> area;

    for(int count_y{ -m_dungeon_radius }; count_y <= m_dungeon_radius; ++count_y)
    {
     std::vector <cube_type> line;

      for(int count_z{ -m_dungeon_radius }; count_z <= m_dungeon_radius; ++count_z)
      {
        if (rand() < rand.max()/3)
        { line.push_back(cube_type::concrete); }
        else
        { line.push_back(cube_type::none); }
      }

      area.push_back(line);
    }

    m_type_volume.push_back(area);
  }

  m_camera.position = m_position; // Camera position
  m_camera.target = Vector3Add(m_position, m_directions[0]); // Vector3Add(camera.position, forward);      // Camera looking at point
  m_camera.up = m_directions[2];          // Camera up vector (rotation towards target)
  m_camera.fovy = m_cam_angle;                                // Camera field-of-view Y
  m_camera.type = CAMERA_PERSPECTIVE; // Camera mode type

  SetCameraMode(m_camera, CAMERA_FREE);
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

  if (coord < -m_dungeon_radius)
  { index += m_dungeon_span; }
  else if (coord > m_dungeon_radius)
  { index -= m_dungeon_span; }

  return index;
}

int dungeon_loop::dungeon_warp(const int coord)
noexcept
{
  int index = coord;

  if (coord < 0)
  { index += m_dungeon_span; }
  else if (coord >= m_dungeon_span)
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

  return directs;
}


void dungeon_loop::collide()
noexcept
{
  std::vector <int> coords
  { coordinator(m_position.x),
    coordinator(m_position.y),
    coordinator(m_position.z) };

  std::vector <std::vector <int>> directs
  { director() };

  for (const std::vector <int> &direct: directs)
  {
    for (int sign{ -1 }; sign <= 1; sign +=2)
    {
      std::vector <int> posit
      { sign == -1 ? sub_int_vector(coords, direct) : add_int_vector(coords, direct) };

      for (int &part: posit)
      { part = dungeon_warp(part); }

      if (m_type_volume[posit[0]][posit[1]][posit[2]] == cube_type::concrete &&
          m_act == direct2action(directs, direct))
      { m_act = action::none; }
    }
  }
}

void dungeon_loop::play_actions()
noexcept
{
  if (m_act == action::none)
  {
    m_act = key_bind_actions();

    if (m_act != action::none)
    { this->collide(); }

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

  this->movetate();

  wrapping(m_position, m_wrap);

  m_camera.position = m_position;

  m_camera.target = Vector3Add(m_position, m_directions[0]);
  m_camera.up = m_directions[2];


  if (IsKeyDown(KEY_BACKSPACE))
  { m_loop = false; }

  if (WindowShouldClose())
  { m_loop = false; }

  if (IsKeyPressed(KEY_SPACE))
  {
    ToggleVrMode();

    m_display_info = !m_display_info;
  }   // Toggle VR mode
}

void dungeon_loop::info_display()
noexcept
{
  DrawFPS(10, 10);

  const std::vector <std::string> pos_strings
  { vector3_to_strings(m_camera.position) };

  const std::string distance_string
  { std::to_string(m_min_distance) };

  const std::vector <std::string> difference_strings
  { vector3_to_strings(m_min_difference) };

  const std::string camera_pos
  { "m_camera position:\n{" + pos_strings[0] + ","  + pos_strings[1] + "," + pos_strings[2] };

  const std::string min_dist
  { "Minimum distance:\n{" + distance_string };

  const std::string diff
  { "m_min_difference:\n{" + difference_strings[0] + ","  + difference_strings[1] + "," + difference_strings[2] };

  const char *array_pos
  { camera_pos.c_str() };

  const char *array_dist
  { min_dist.c_str() };

  const char *array_diff
  { diff.c_str() };

  DrawText(array_pos, 10, 40, 20, GREEN);
  DrawText(array_dist, 10, 280, 20, RED);
  DrawText(array_diff, 10, 340, 20, RED);

  // DrawRectangle( 10, 10, 320, 133, Fade(SKYBLUE, 0.5f));
  // DrawRectangleLines( 10, 10, 320, 133, BLUE);


  // DrawText("Free m_camera default controls:", 20, 20, 10, BLACK);
  // DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
  // DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
  // DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, DARKGRAY);
  // DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 100, 10, DARKGRAY);
  // DrawText("- Z to zoom to (0, 0, 0)", 40, 120, 10, DARKGRAY);

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

    for (const Vector3 &direction: m_directions)
    {
      display_vector3(direction, x, y, size);
      y += step;
    }
  }
  else
  { DrawFPS(650, 20); }
}

void dungeon_loop::display_pos(const int pos_x,
                               const int pos_y,
                               const int pos_z)
noexcept
{
  int x_min
  { pos_x - m_horizon };

  if (x_min < -m_dungeon_radius)
  { x_min += m_dungeon_span; }

  int x_max
  { pos_x + m_horizon };

  if (x_max > m_dungeon_radius)
  { x_max -= m_dungeon_span; }

  int y_min
  { pos_y - m_horizon };

  if (y_min < -m_dungeon_radius)
  { y_min += m_dungeon_span; }

  int y_max
  { pos_y + m_horizon };

  if (y_max > m_dungeon_radius)
  { y_max -= m_dungeon_span; }

  int z_min
  { pos_z - m_horizon };

  if (z_min < -m_dungeon_radius)
  { z_min += m_dungeon_span; }

  int z_max
  { pos_z + m_horizon };

  if (z_max > m_dungeon_radius)
  { z_max -= m_dungeon_span; }

  const std::string x_min_string
  { std::to_string(x_min) };

  const std::string y_min_string
  { std::to_string(y_min) };

  const std::string z_min_string
  { std::to_string(z_min) };

  const std::string x_max_string
  { std::to_string(x_max) };

  const std::string y_max_string
  { std::to_string(y_max) };

  const std::string z_max_string
  { std::to_string(z_max) };

  const std::string pos_min_string
  { "minimum position:\n{" + x_min_string + "," + y_min_string + "," + z_min_string };

  const std::string pos_max_string
  { "maximum position:\n{" + x_max_string + "," + y_max_string + "," + z_max_string };

  const char *array_pos_min
  { pos_min_string.c_str() };

  const char *array_pos_max
  { pos_max_string.c_str() };

  DrawText(array_pos_min, 10, 400, 20, YELLOW);
  DrawText(array_pos_max, 10, 460, 20, YELLOW);
}



void dungeon_loop::run()
{
  while (m_loop)
  {
    this->play_actions();

    BeginDrawing();
    {
      ClearBackground(Color{ BLACK });
      m_min_distance = 1000000.0f;

      const int pos_x
      { static_cast<int>(round(m_position.x/m_multiplier)) };
      const int pos_y
      { static_cast<int>(round(m_position.y/m_multiplier)) };
      const int pos_z
      { static_cast<int>(round(m_position.z/m_multiplier)) };

      BeginVrDrawing();
      BeginMode3D(m_camera);
      {
        for (int count_x { -m_horizon }; count_x <= m_horizon; ++count_x)
        {
          const int coord_x
          { pos_x + count_x };
          int index
          { dungeon_wrap(coord_x) };

          for (int count_y { -m_horizon }; count_y <= m_horizon; ++count_y)
          {
            int coord_y
            { pos_y + count_y };
            int indey
            { dungeon_wrap(coord_y) };

            for (int count_z { -m_horizon }; count_z <= m_horizon; ++count_z)
            {
              int coord_z
              { pos_z + count_z };
              int indez
              { dungeon_wrap(coord_z) };

              const int dungeon_x
              { index + m_dungeon_radius };
              const int dungeon_y
              { indey + m_dungeon_radius };
              const int dungeon_z
              { indez + m_dungeon_radius };

              const cube_type c_type
              { m_type_volume[unsigned(dungeon_x)]
                             [unsigned(dungeon_y)]
                             [unsigned(dungeon_z)] };

              if (c_type != cube_type::none)
              {
                m_fracta_cube.set_pos_type(coord_x, coord_y, coord_z, c_type);

                if (display_selector(m_position,
                                     Vector3Scale(m_fracta_cube.get_position(), m_multiplier),
                                     m_directions[0], m_cam_field, m_multiplier))
                {
                  m_fracta_cube.display(m_position, m_directions[0], m_cube_color, m_edge_color,
                                        m_cam_field, m_sight, m_decay, m_multiplier);
                }
              }

            }
          }
        }
      }
      EndMode3D();
      EndVrDrawing();

      if (m_test)
      { this->infos(); }
    }

    EndDrawing();
  }
}
