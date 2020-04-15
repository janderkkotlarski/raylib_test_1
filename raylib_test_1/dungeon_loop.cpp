#include "dungeon_loop.h"

#include <raymath.h>

#include "misc_functions.h"

dungeon_loop::dungeon_loop()
{
  std::random_device rand;

  for(int count{ 0 }; count < cube_amount; ++count)
  { m_cube_positions.push_back(ranpos(rand, dist_min, dist_max)); }
}

dungeon_loop::key_bindings(const float velocity,
                           const float theta)
noexcept
{
 if (IsKeyDown('W'))
 { m_position = Vector3Add(m_position, Vector3Scale(m_forward, velocity)); }

 if (IsKeyDown('S'))
 { m_position = Vector3Add(m_position, Vector3Scale(m_backward, velocity)); }

 if (IsKeyDown('D'))
 { m_position = Vector3Add(m_position, Vector3Scale(m_rightward, velocity)); }

 if (IsKeyDown('A'))
 { m_position = Vector3Add(m_position, Vector3Scale(m_leftward, velocity)); }

 if (IsKeyDown('E'))
 { m_position = Vector3Add(m_position, Vector3Scale(m_upward, velocity)); }

 if (IsKeyDown('Q'))
 { m_position = Vector3Add(m_position, Vector3Scale(m_downward, velocity)); }

 if (IsKeyDown('L'))
 { rotate_first_second(m_forward, m_rightward, m_backward, m_leftward, theta); }

 if (IsKeyDown('J'))
 { rotate_first_second(m_forward, m_leftward, m_backward, m_rightward, theta); }

 if (IsKeyDown('I'))
 {
   rotate_first_second(m_forward, m_upward, m_backward, m_downward, theta);
   m_camera.up = m_upward;
 }

 if (IsKeyDown('K'))
 {
   rotate_first_second(m_forward, m_downward, m_backward, m_upward, theta);
   m_camera.up = m_upward;
 }

 if (IsKeyDown('O'))
 {
   rotate_first_second(m_upward, m_rightward, m_downward, m_leftward, theta);
   m_camera.up = m_upward;
 }

 if (IsKeyDown('U'))
 {
   rotate_first_second(m_upward, m_leftward, m_downward, m_rightward, theta);
   m_camera.up = m_upward;
 }
}

dungeon_loop::run()
{

  key_bindings(m_camera, m_position, m_forward, m_backward,
               m_rightward, m_leftward, m_upward, m_downward,
               velocity, theta);

  wrapping(m_position, wrap);

  m_camera.target = Vector3Add(m_position, m_forward);

  m_camera.position = m_position;

  const std::vector <std::string> pos_strings
  { vector3_to_strings(m_camera.m_position) };

  const std::vector <std::string> front_strings
  { vector3_to_strings(m_forward) };

  const std::vector <std::string> right_strings
  { vector3_to_strings(m_rightward) };

  const std::vector <std::string> up_strings
  { vector3_to_strings(m_upward) };

  // if (IsKeyDown('Z')) m_camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };

  BeginDrawing();
  {
    ClearBackground(background);

    BeginMode3D(m_camera);
    {
      if (randomode)
      {
        for (Vector3 cube_pos: cube_positions)
        {
          display_cube(m_position, cube_pos, cube_dims, m_forward,
                       cube_color, edge_color, cam_angle, sight, decay, multiplier);
        }
      }
      else
      {
        display_cube(m_position, cube_position, cube_dims, m_forward,
                     cube_color, edge_color, cam_angle, sight, decay, multiplier);
      }
    }
    EndMode3D();

    DrawFPS(10, 10);

    // DrawRectangle( 10, 10, 320, 133, Fade(SKYBLUE, 0.5f));
    // DrawRectangleLines( 10, 10, 320, 133, BLUE);

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

    // DrawText("Free m_camera default controls:", 20, 20, 10, BLACK);
    // DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
    // DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
    // DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, DARKGRAY);
    // DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 100, 10, DARKGRAY);
    // DrawText("- Z to zoom to (0, 0, 0)", 40, 120, 10, DARKGRAY);
  }

  EndDrawing();

}

