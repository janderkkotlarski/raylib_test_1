#include <iostream>
#include <string>
#include <vector>
#include <random>

#include <raylib.h>

#include "misc_functions.h"
#include "fractacube.h"

int main()
{
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 800;

  const float fps
  { 60.0f };

  const float multiplier
  { 100.0f };

  const float speed
  { 5.0f };

  const float velocity
  { multiplier*speed/fps };

  const float angle
  { 2.0f };

  const float theta
  { angle/fps };

  const float side
  { multiplier*1.0f };

  const float wrap
  { multiplier*20.0f };

  const float decay
  { 0.9f };

  const float sight
  { multiplier*20.0f };

  const Vector3 cube_dims
  { side, side, side };

  const float dist_min
  { multiplier*3.0f };

  const float dist_max
  { multiplier*20.0f };

  Color cube_color
  { 127, 127, 127, 255};

  Color edge_color
  { 255, 255, 255, 255};

  fractacube cube
  { 5, 0, 0, cube_type::concrete };

  std::random_device rand;

  const bool randomode
  { false };

  const int cube_amount
  { 1000 };

  std::vector <Vector3> cube_positions;

  for(int count{ 0 }; count < cube_amount; ++count)
  { cube_positions.push_back(ranpos(rand, dist_min, dist_max)); }

  Vector3 cube_position
  { 0.0f, 0.0f, 0.0f };
  // { ranpos(rand, dist_min, dist_max) };

  Vector3 forward
  { 1.0f, 0.0f, 0.0f };

  Vector3 backward
  { -1.0f, 0.0f, 0.0f };

  Vector3 rightward
  { 0.0f, -1.0f, 0.0f };

  Vector3 leftward
  { 0.0f, 1.0f, 0.0f };

  Vector3 upward
  { 0.0f, 0.0f, 1.0f };

  Vector3 downward
  { 0.0f, 0.0f, -1.0f };

  Vector3 position
  { 0.0f, 0.0f, 0.0f };

  InitWindow(screenWidth, screenHeight, "Test 1 for raylib");

  // Define the camera to look into our 3d world
  Camera3D camera
  {};

  camera.position = position; // Camera position
  camera.target = add_vector3(position, forward); // Vector3Add(camera.position, forward);      // Camera looking at point
  camera.up = upward;          // Camera up vector (rotation towards target)
  camera.fovy = 60.0f;                                // Camera field-of-view Y
  // camera.type = CAMERA_PERSPECTIVE; // Camera mode type
  camera.type = CAMERA_PERSPECTIVE;

  const float cam_angle
  { 0.3f };

  // SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode

  SetCameraMode(camera, CAMERA_FREE);


  SetTargetFPS(fps);  // Set our game to run at fps frames-per-second
  //--------------------------------------------------------------------------------------

  const Color background
  {0, 0, 0, 255};

  // raylib

  // Main game loop
  while (!WindowShouldClose())        // Detect window close button or ESC key
  {
    key_bindings(camera, position, forward, backward,
                 rightward, leftward, upward, downward,
                 velocity, theta);

    wrapping(position, wrap);

    camera.target = add_vector3(position, forward);

    camera.position = position;

    const std::vector <std::string> pos_strings
    { vector3_to_strings(camera.position) };

    const std::vector <std::string> front_strings
    { vector3_to_strings(forward) };

    const std::vector <std::string> right_strings
    { vector3_to_strings(rightward) };

    const std::vector <std::string> up_strings
    { vector3_to_strings(upward) };

    // if (IsKeyDown('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };

    BeginDrawing();
    {
      ClearBackground(background);

      BeginMode3D(camera);
      {
        if (randomode)
        {
          for (Vector3 cube_pos: cube_positions)
          {
            display_cube(position, cube_pos, cube_dims, forward,
                         cube_color, edge_color, cam_angle, sight, decay, multiplier);
          }
        }
        else
        {
          display_cube(position, cube_position, cube_dims, forward,
                       cube_color, edge_color, cam_angle, sight, decay, multiplier);
        }
      }
      EndMode3D();

      DrawFPS(10, 10);

      // DrawRectangle( 10, 10, 320, 133, Fade(SKYBLUE, 0.5f));
      // DrawRectangleLines( 10, 10, 320, 133, BLUE);

      const std::string camera_pos
      { "Camera position:\n{" + pos_strings[0] + ","  + pos_strings[1] + "," + pos_strings[2] };

      const std::string camera_front
      { "Camera front:\n{" + front_strings[0] + ","  + front_strings[1] + "," + front_strings[2] };

      const std::string camera_right
      { "Camera right:\n{" + right_strings[0] + ","  + right_strings[1] + "," + right_strings[2] };

      const std::string camera_up
      { "Camera upt:\n{" + up_strings[0] + ","  + up_strings[1] + "," + up_strings[2] };

      const char *array_pos
      { camera_pos.c_str() };

      const char *array_front
      { camera_front.c_str() };

      const char *array_right
      { camera_right.c_str() };

      const char *array_up
      { camera_up.c_str() };

      DrawText(array_pos, 10, 40, 20, GREEN);
      DrawText(array_front, 10, 100, 20, GREEN);
      DrawText(array_right, 10, 160, 20, GREEN);
      DrawText(array_up, 10, 220, 20, GREEN);

      // DrawText("Free camera default controls:", 20, 20, 10, BLACK);
      // DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
      // DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
      // DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, DARKGRAY);
      // DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 100, 10, DARKGRAY);
      // DrawText("- Z to zoom to (0, 0, 0)", 40, 120, 10, DARKGRAY);
    }

    EndDrawing();

  }

  return 0;
}
