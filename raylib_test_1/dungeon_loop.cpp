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
        { line.push_back(cube_type::concrete); }
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

  const std::string m_camera_pos
  { "m_camera position:\n{" + pos_strings[0] + ","  + pos_strings[1] + "," + pos_strings[2] };

  const std::string m_camera_front
  { "m_camera front:\n{" + front_strings[0] + ","  + front_strings[1] + "," + front_strings[2] };

  const std::string m_camera_right
  { "m_camera right:\n{" + right_strings[0] + ","  + right_strings[1] + "," + right_strings[2] };

  const std::string m_camera_up
  { "m_camera upt:\n{" + up_strings[0] + ","  + up_strings[1] + "," + up_strings[2] };

  const char *array_pos
  { m_camera_pos.c_str() };

  const char *array_front
  { m_camera_front.c_str() };

  const char *array_right
  { m_camera_right.c_str() };

  const char *array_up
  { m_camera_up.c_str() };

  DrawText(array_pos, 10, 40, 20, GREEN);
  DrawText(array_front, 10, 100, 20, GREEN);
  DrawText(array_right, 10, 160, 20, GREEN);
  DrawText(array_up, 10, 220, 20, GREEN);

  // DrawRectangle( 10, 10, 320, 133, Fade(SKYBLUE, 0.5f));
  // DrawRectangleLines( 10, 10, 320, 133, BLUE);


  // DrawText("Free m_camera default controls:", 20, 20, 10, BLACK);
  // DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
  // DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
  // DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, DARKGRAY);
  // DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 100, 10, DARKGRAY);
  // DrawText("- Z to zoom to (0, 0, 0)", 40, 120, 10, DARKGRAY);

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

      BeginMode3D(m_camera);
      {
        if (m_randomode)
        {
          for(int count_x{ -m_dungeon_radius }; count_x <= m_dungeon_radius; ++count_x)
          {
            for(int count_y{ -m_dungeon_radius }; count_y <= m_dungeon_radius; ++count_y)
            {
              for(int count_z{ -m_dungeon_radius }; count_z <= m_dungeon_radius; ++count_z)
              {
                fractacube f_cube(count_x, count_y, count_z, cube_type::concrete);

                f_cube.display(m_position, m_forward, m_cube_color, m_edge_color,
                               m_cam_field, m_sight, m_decay, m_multiplier);
              }
            }
          }

          for (Vector3 &cube_pos: m_cube_positions)
          {
            display_cube(m_position, cube_pos, m_cube_dims, m_forward,
                         m_cube_color, m_edge_color, m_cam_field, m_sight, m_decay, m_multiplier);
          }
        }
        else
        {
          /*
          for(int count_x{ -m_dungeon_radius }; count_x <= m_dungeon_radius; ++count_x)
          {
            for(int count_y{ -m_dungeon_radius }; count_y <= m_dungeon_radius; ++count_y)
            {
              for(int count_z{ -m_dungeon_radius }; count_z <= m_dungeon_radius; ++count_z)
              {
                fractacube f_cube(count_x, count_y, count_z, cube_type::concrete);

                // f_cube.display(m_position, m_forward, m_cube_color, m_edge_color,
                //                m_cam_field, m_sight, m_decay, m_multiplier);
              }
            }
          }
          */

          // fractacube f_cube(1, 0, 0, cube_type::concrete);

          // f_cube.display(m_position, m_forward, m_cube_color, m_edge_color,
          //                m_cam_field, m_sight, m_decay, m_multiplier);

          // display_cube(m_position, m_cube_position, m_cube_dims, m_forward,
          //              m_cube_color, m_edge_color, m_cam_field, m_sight, m_decay, m_multiplier);

          for (fractacube &f_cube: m_fracta_cubes)
          {
            f_cube.display(m_position, m_forward, m_cube_color, m_edge_color,
                           m_cam_field, m_sight, m_decay, m_multiplier);
          }
        }
      }
      EndMode3D();

      this->info_display();
    }

    EndDrawing();
  }
}

