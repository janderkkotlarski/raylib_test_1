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

std::vector <std::string> vector3_to_strings(const raylib::Vector3 &vec)
{
  std::vector <std::string> strings;

  strings.push_back(std::to_string(vec.x));
  strings.push_back(std::to_string(vec.y));
  strings.push_back(std::to_string(vec.z));

  return strings;
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

  const float adjusted
  { speed/fps };

  const float side
  { 1.0f };

  std::vector <raylib::Vector3> cube_positions
  { raylib::Vector3(1.0f, 0.0f, 0.0f),
    raylib::Vector3(1.0f, 2.0f, 0.0f)};



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

  raylib::Window window(screenWidth, screenHeight, "Test 1 for raylib");

  // Define the camera to look into our 3d world
  raylib::Camera3D camera;  

  camera.position = { 0.0f, 0.0f, 0.0f }; // Camera position
  camera.target = add_vector3(camera.position, forward); // Vector3Add(camera.position, forward);      // Camera looking at point
  camera.up = { upward };          // Camera up vector (rotation towards target)
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



    // if (IsKeyDown('L'))
    // { camera. }

    camera.target = add_vector3(camera.position, forward);

    // Update
    //---------------------------------------------------------------------------------

    camera.Update(); // Update camera

    std::vector <std::string> pos_strings
    { vector3_to_strings(camera.position) };

    // if (IsKeyDown('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };

    window.BeginDrawing();
    {
      ClearBackground(background);

      camera.BeginMode3D();
      {
        for (raylib::Vector3 position: cube_positions)
        { position.DrawCube(side, side, side, ORANGE); }

        // DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

      }



      camera.EndMode3D();

      DrawFPS(10, 10);

      // DrawRectangle( 10, 10, 320, 133, Fade(SKYBLUE, 0.5f));
      // DrawRectangleLines( 10, 10, 320, 133, BLUE);

      const std::string camera_pos
      { "Camera position:\n{" + pos_strings[0] + ","  + pos_strings[1] + "," + pos_strings[2] };

      const char *array
      { camera_pos.c_str() };

      DrawText(array, 10, 40, 20, GREEN);

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
