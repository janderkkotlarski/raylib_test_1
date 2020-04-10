#include <iostream>

#include "raylib.h"

#include "raylib.hpp"

raylib::Vector3 add_vector3(const raylib::Vector3 &vec_1,
                            const raylib::Vector3 &vec_2)
{
  raylib::Vector3 vec_3;

  vec_3.x = vec_1.x + vec_2.x;
  vec_3.y = vec_1.y + vec_2.y;
  vec_3.z = vec_1.z + vec_2.z;

  return vec_3;
}

int main()
{
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 800;

  raylib::Vector3 cube_position
  { 3.0f, 0.0f, 0.0f };

  raylib::Vector3 forward
  { 1.0f, 0.0f, 0.0f };

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
  camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
  camera.fovy = 90.0f;                                // Camera field-of-view Y
  camera.type = CAMERA_PERSPECTIVE;                   // Camera mode type



  // SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode

  camera.SetMode(CAMERA_FREE);

  window.SetTargetFPS(60);            // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  const raylib::Color background
  {0, 0, 0};

  // raylib

  // Main game loop
  while (!window.ShouldClose())        // Detect window close button or ESC key
  {
    // Update
    //---------------------------------------------------------------------------------

    camera.Update(); // Update camera

    // if (IsKeyDown('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };



    window.BeginDrawing();
    {
      ClearBackground(background);

      camera.BeginMode3D();
      {
        cube_position.DrawCube(2.0f, 2.0f, 2.0f, ORANGE);

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
