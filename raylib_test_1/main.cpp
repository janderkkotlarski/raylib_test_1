#include <iostream>
#include <string>
#include <vector>

// #include "raylib.h"

#include "raylib.hpp"

raylib::Vector3 add_vector3(const raylib::Vector3 &vec_1,
                            const raylib::Vector3 &vec_2)
noexcept
{
  raylib::Vector3 out_vec;

  out_vec.x = vec_1.x + vec_2.x;
  out_vec.y = vec_1.y + vec_2.y;
  out_vec.z = vec_1.z + vec_2.z;

  return out_vec;
}

raylib::Vector3 multiply_vector3(const raylib::Vector3 &vec_1,
                                 const float mult)
noexcept
{
  raylib::Vector3 out_vec;

  out_vec.x = vec_1.x*mult;
  out_vec.y = vec_1.y*mult;
  out_vec.z = vec_1.z*mult;

  return out_vec;
}

std::vector <std::string> vector3_to_strings(const raylib::Vector3 &vec)
noexcept
{
  std::vector <std::string> strings;

  strings.push_back(std::to_string(vec.x));
  strings.push_back(std::to_string(vec.y));
  strings.push_back(std::to_string(vec.z));

  return strings;
}

void rotate_front(raylib::Vector3 &front,
                  raylib::Vector3 &perp,
                  const float theta)
{
  raylib::Vector3 new_front
  { add_vector3(multiply_vector3(front, cos(theta)), multiply_vector3(perp, sin(theta))) };

  raylib::Vector3 new_perp
  { add_vector3(multiply_vector3(front, -sin(theta)), multiply_vector3(perp, cos(theta))) };

  front = new_front;
  perp = new_perp;
}


int main()
{
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 800;

  const float fps
  { 60.0f };

  const float speed
  { 5.0f };

  const float velocity
  { speed/fps };

  const float angle
  { 2.0f };

  const float theta
  { angle/fps };

  const float side
  { 1.0f };

  const raylib::Vector3 cube_dims
  { side, side, side };

  std::vector <raylib::Vector3> cube_positions
  { raylib::Vector3(1.0f, 0.0f, 0.0f),
    raylib::Vector3(1.0f, 2.0f, 0.0f)};

  raylib::Vector3 forward
  { 1.0f, 0.0f, 0.0f };

  raylib::Vector3 backward
  { -1.0f, 0.0f, 0.0f };

  raylib::Vector3 rightward
  { 0.0f, -1.0f, 0.0f };

  raylib::Vector3 leftward
  { 0.0f, 1.0f, 0.0f };

  raylib::Vector3 upward
  { 0.0f, 0.0f, 1.0f };

  raylib::Vector3 downward
  { 0.0f, 0.0f, -1.0f };

  raylib::Vector3 position
  { 0.0f, 0.0f, 0.0f };

  raylib::Window window(screenWidth, screenHeight, "Test 1 for raylib");

  // Define the camera to look into our 3d world
  raylib::Camera3D camera;  

  camera.position = position; // Camera position
  camera.target = add_vector3(position, forward); // Vector3Add(camera.position, forward);      // Camera looking at point
  camera.up = upward;          // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;                                // Camera field-of-view Y
  camera.type = CAMERA_PERSPECTIVE;                   // Camera mode type

  std::vector <std::string> pos_strings
  { vector3_to_strings(camera.position) };

  // SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode

  camera.SetMode(CAMERA_FREE);

  window.SetTargetFPS(fps);            // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  const raylib::Color background
  {0, 0, 0};

  // raylib

  // Main game loop
  while (!window.ShouldClose())        // Detect window close button or ESC key
  {
    if (IsKeyDown('W'))
    { position = add_vector3(camera.position,
                             multiply_vector3(forward, velocity)); }

    if (IsKeyDown('S'))
    { position = add_vector3(camera.position,
                             multiply_vector3(backward, velocity)); }

    if (IsKeyDown('D'))
    { position = add_vector3(camera.position,
                             multiply_vector3(rightward, velocity)); }

    if (IsKeyDown('A'))
    { position = add_vector3(camera.position,
                             multiply_vector3(leftward, velocity)); }

    if (IsKeyDown('E'))
    { position = add_vector3(camera.position,
                             multiply_vector3(upward, velocity)); }

    if (IsKeyDown('Q'))
    { position = add_vector3(camera.position,
                             multiply_vector3(downward, velocity)); }

    if (IsKeyDown('L'))
    {
      rotate_front(forward, rightward, theta);

      backward = multiply_vector3(forward, -1.0f);
      leftward = multiply_vector3(rightward, -1.0f);
    }

    if (IsKeyDown('J'))
    {
      rotate_front(forward, leftward, theta);

      backward = multiply_vector3(forward, -1.0f);
      rightward = multiply_vector3(leftward, -1.0f);
    }

    if (IsKeyDown('I'))
    {
      rotate_front(forward, upward, theta);

      backward = multiply_vector3(forward, -1.0f);
      downward = multiply_vector3(upward, -1.0f);

      camera.up = upward;
    }

    if (IsKeyDown('K'))
    {
      rotate_front(forward, downward, theta);

      backward = multiply_vector3(forward, -1.0f);
      upward = multiply_vector3(downward, -1.0f);

      camera.up = upward;
    }

    if (IsKeyDown('O'))
    {
      rotate_front(upward, rightward, theta);

      downward = multiply_vector3(upward, -1.0f);
      leftward = multiply_vector3(rightward, -1.0f);

      camera.up = upward;
    }

    if (IsKeyDown('U'))
    {
      rotate_front(upward, leftward, theta);

      downward = multiply_vector3(upward, -1.0f);
      rightward = multiply_vector3(leftward, -1.0f);

      camera.up = upward;
    }


    // if (IsKeyDown('L'))
    // { camera. }

    camera.target = add_vector3(position, forward); // add_vector3(camera.position, forward);

    camera.Update(); // Update camera

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

    window.BeginDrawing();
    {
      ClearBackground(background);

      camera.BeginMode3D();
      {
        for (raylib::Vector3 position: cube_positions)
        {
          position.DrawCube(cube_dims, DARKPURPLE);

          position.DrawCubeWires(cube_dims, ORANGE);
        }
      }

      camera.EndMode3D();

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
    window.EndDrawing();

  }

  return 0;
}
