#include <iostream>

#include "raylib.h"

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

raylib::Vector3 divide_vector3(const raylib::Vector3 &vec_1,
                               const float div)
{
  raylib::Vector3 out_vec;

  if (div == 0.0f )
  {
    std::cerr << "Do not divide by 0!" << std::endl;

    throw 1;
  }

  out_vec.x = vec_1.x/div;
  out_vec.y = vec_1.y/div;
  out_vec.z = vec_1.z/div;

  return out_vec;
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
  { 1.0f };

  const float adjusted
  { speed/fps };

  raylib::Vector3 cube_position
  { 1.0f, 0.0f, 0.0f };

  const raylib::Vector3 forward
  { 1.0f, 0.0f, 0.0f };

  const raylib::Vector3 backward
  { -1.0f, 0.0f, 0.0f };

  const raylib::Vector3 rightward
  { 0.0f, -1.0f, 0.0f };

  const raylib::Vector3 leftward
  { 0.0f, 1.0f, 0.0f };

  const raylib::Vector3 upward
  { 0.0f, 0.0f, 1.0f };

  const raylib::Vector3 downward
  { 0.0f, 0.0f, -1.0f };

  raylib::Vector3 target
  { forward };

  raylib::Vector3 cam_pos
  { 0.0f, 0.0f, 0.0f };

  raylib::Window window(screenWidth, screenHeight, "Test 1 for raylib");

  // Define the camera to look into our 3d world
  raylib::Camera3D camera;

  target = add_vector3(cam_pos, forward);

  camera.position = { 0.0f, 0.0f, 0.0f }; // Camera position
  camera.target = add_vector3(camera.position, forward); // Vector3Add(camera.position, forward);      // Camera looking at point
  camera.up = { 0.0f, 0.0f, 1.0f };          // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;                                // Camera field-of-view Y
  camera.type = CAMERA_PERSPECTIVE;                   // Camera mode type


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
    { camera.SetPosition(add_vector3(camera.position,
                                     multiply_vector3(forward, adjusted))); }

    if (IsKeyDown('S'))
    { camera.SetPosition(add_vector3(camera.position,
                                     multiply_vector3(backward, adjusted))); }

    if (IsKeyDown('D'))
    { camera.SetPosition(add_vector3(camera.position,
                                     multiply_vector3(rightward, adjusted))); }

    if (IsKeyDown('A'))
    { camera.SetPosition(add_vector3(camera.position,
                                     multiply_vector3(leftward, adjusted))); }

    if (IsKeyDown('E'))
    { camera.SetPosition(add_vector3(camera.position,
                                     multiply_vector3(upward, adjusted))); }

    if (IsKeyDown('Q'))
    { camera.SetPosition(add_vector3(camera.position,
                                     multiply_vector3(downward, adjusted))); }

    camera.target = add_vector3(camera.position, forward);

    // Update
    //---------------------------------------------------------------------------------

    camera.Update(); // Update camera

    // if (IsKeyDown('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };



    window.BeginDrawing();
    {
      ClearBackground(background);

      camera.BeginMode3D();
      {
        cube_position.DrawCube(1.0f, 1.0f, 1.0f, ORANGE);

        // DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

      }

      camera.EndMode3D();

      // DrawRectangle( 10, 10, 320, 133, Fade(SKYBLUE, 0.5f));
      // DrawRectangleLines( 10, 10, 320, 133, BLUE);

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
