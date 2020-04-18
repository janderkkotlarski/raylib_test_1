#include "dungeon_loop.h"

#include <raymath.h>

#include "misc_functions.h"

dungeon_loop::dungeon_loop()
noexcept
  : m_cube_positions(), m_fracta_cubes(), m_camera()
{
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
        { m_cube_positions.push_back(Vector3{ m_multiplier*count_x, m_multiplier*count_y, m_multiplier*count_z }); }

        if (rand() < rand.max()/3)
        { m_fracta_cubes.push_back(fractacube(count_x, count_y, count_z, cube_type::concrete)); }

        if (rand() < rand.max()/3)
        { line.push_back(cube_type::next); }
        else
        { line.push_back(cube_type::none); }
      }

      area.push_back(line);
    }

    m_type_volume.push_back(area);
  }

  m_camera.position = m_position; // Camera position
  m_camera.target = Vector3Add(m_position, m_forward); // Vector3Add(camera.position, forward);      // Camera looking at point
  m_camera.up = m_upward;          // Camera up vector (rotation towards target)
  m_camera.fovy = m_cam_angle;                                // Camera field-of-view Y
  m_camera.type = CAMERA_PERSPECTIVE; // Camera mode type

  SetCameraMode(m_camera, CAMERA_FREE);
}

void dungeon_loop::play_key_bindings()
noexcept
{
 if (IsKeyDown('W'))
 { m_position = Vector3Add(m_position, Vector3Scale(m_forward, m_velocity)); }

 if (IsKeyDown('S'))
 { m_position = Vector3Add(m_position, Vector3Scale(m_backward, m_velocity)); }

 if (IsKeyDown('D'))
 { m_position = Vector3Add(m_position, Vector3Scale(m_rightward, m_velocity)); }

 if (IsKeyDown('A'))
 { m_position = Vector3Add(m_position, Vector3Scale(m_leftward, m_velocity)); }

 if (IsKeyDown('E'))
 { m_position = Vector3Add(m_position, Vector3Scale(m_upward, m_velocity)); }

 if (IsKeyDown('Q'))
 { m_position = Vector3Add(m_position, Vector3Scale(m_downward, m_velocity)); }

 if (IsKeyDown('L'))
 { rotate_first_second(m_forward, m_rightward, m_backward, m_leftward, m_theta); }

 if (IsKeyDown('J'))
 { rotate_first_second(m_forward, m_leftward, m_backward, m_rightward, m_theta); }

 if (IsKeyDown('I'))
 {
   rotate_first_second(m_forward, m_upward, m_backward, m_downward, m_theta);
   m_camera.up = m_upward;
 }

 if (IsKeyDown('K'))
 {
   rotate_first_second(m_forward, m_downward, m_backward, m_upward, m_theta);
   m_camera.up = m_upward;
 }

 if (IsKeyDown('O'))
 {
   rotate_first_second(m_upward, m_rightward, m_downward, m_leftward, m_theta);
   m_camera.up = m_upward;
 }

 if (IsKeyDown('U'))
 {
   rotate_first_second(m_upward, m_leftward, m_downward, m_rightward, m_theta);
   m_camera.up = m_upward;
 }

 if (IsKeyDown(KEY_BACKSPACE))
 { m_loop = false; }

 if (WindowShouldClose())
 { m_loop = false; }
}

void dungeon_loop::info_display()
noexcept
{
  DrawFPS(10, 10);

  const std::vector <std::string> pos_strings
  { vector3_to_strings(m_camera.position) };

  const std::vector <std::string> front_strings
  { vector3_to_strings(m_forward) };

  const std::vector <std::string> right_strings
  { vector3_to_strings(m_rightward) };

  const std::vector <std::string> up_strings
  { vector3_to_strings(m_upward) };

  const std::string distance_string
  { std::to_string(m_min_distance) };

  const std::vector <std::string> difference_strings
  { vector3_to_strings(m_min_difference) };

  const std::string camera_pos
  { "m_camera position:\n{" + pos_strings[0] + ","  + pos_strings[1] + "," + pos_strings[2] };

  const std::string camera_front
  { "m_camera front:\n{" + front_strings[0] + ","  + front_strings[1] + "," + front_strings[2] };

  const std::string camera_right
  { "m_camera right:\n{" + right_strings[0] + ","  + right_strings[1] + "," + right_strings[2] };

  const std::string camera_up
  { "m_camera up:\n{" + up_strings[0] + ","  + up_strings[1] + "," + up_strings[2] };

  const std::string min_dist
  { "Minimum distance:\n{" + distance_string };

  const std::string diff
  { "m_min_difference:\n{" + difference_strings[0] + ","  + difference_strings[1] + "," + difference_strings[2] };

  const char *array_pos
  { camera_pos.c_str() };

  const char *array_front
  { camera_front.c_str() };

  const char *array_right
  { camera_right.c_str() };

  const char *array_up
  { camera_up.c_str() };

  const char *array_dist
  { min_dist.c_str() };

  const char *array_diff
  { diff.c_str() };

  DrawText(array_pos, 10, 40, 20, GREEN);
  DrawText(array_front, 10, 100, 20, GREEN);
  DrawText(array_right, 10, 160, 20, GREEN);
  DrawText(array_up, 10, 220, 20, GREEN);
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
    this->play_key_bindings();

    wrapping(m_position, m_wrap);

    m_camera.target = Vector3Add(m_position, m_forward);

    m_camera.position = m_position;

    // if (IsKeyDown('Z')) m_camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };

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

      BeginMode3D(m_camera);
      {
        for (int count_x { -m_horizon }; count_x <= m_horizon; ++count_x)
        {
          const int coord_x
          { pos_x + count_x };

          int index
          { coord_x };

          if (coord_x < -m_dungeon_radius)
          { index += m_dungeon_span; }
          else if (coord_x > m_dungeon_radius)
          { index -= m_dungeon_span; }

          for (int count_y { -m_horizon }; count_y <= m_horizon; ++count_y)
          {
            int coord_y
            { pos_y + count_y };

            int indey
            { coord_y };

            if (coord_y < -m_dungeon_radius)
            { indey += m_dungeon_span; }
            else if (coord_y > m_dungeon_radius)
            { indey -= m_dungeon_span; }

            for (int count_z { -m_horizon }; count_z <= m_horizon; ++count_z)
            {
              int coord_z
              { pos_z + count_z };

              int indez
              { coord_z };

              if (coord_z < -m_dungeon_radius)
              { indez += m_dungeon_span; }
              else if (coord_z > m_dungeon_radius)
              { indez -= m_dungeon_span; }

              const int mult
              { 1 };

              const int dungeon_x
              { index + mult*m_dungeon_radius };

              const int dungeon_y
              { indey + mult*m_dungeon_radius };

              const int dungeon_z
              { indez + mult*m_dungeon_radius };

              const cube_type c_type
              { m_type_volume[unsigned(dungeon_x)]
                             [unsigned(dungeon_y)]
                             [unsigned(dungeon_z)] };

              if (c_type != cube_type::none)
              {
                if (index >= 0 && index < m_dungeon_span &&
                    indey >= 0 && indey < m_dungeon_span &&
                    indez >= 0 && indez < m_dungeon_span &&
                    false)
                { m_fracta_cube.set_pos_type(coord_x, coord_y, coord_z, c_type); }
                else
                { m_fracta_cube.set_pos_type(coord_x, coord_y, coord_z, cube_type::concrete); }

                m_fracta_cube.set_pos_type(coord_x, coord_y, coord_z, c_type);

                // const float distance
                // { Vector3Distance(m_position, Vector3Scale(m_fracta_cube.get_position(), m_multiplier)) };

                if (display_selector(m_position,
                                     Vector3Scale(m_fracta_cube.get_position(), m_multiplier),
                                     m_forward, m_cam_field, m_multiplier))
                {
                  m_fracta_cube.display(m_position, m_forward, m_cube_color, m_edge_color,
                                        m_cam_field, m_sight, m_decay, m_multiplier);
                }
              }

            }
          }
        }
      }
      EndMode3D();

      this->info_display();

      this->display_pos(pos_x, pos_y, pos_z);
    }

    EndDrawing();
  }
}

