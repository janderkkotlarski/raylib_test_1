#include <iostream>
#include <string>
#include <vector>
#include <random>

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

raylib::Vector3 sub_vector3(const raylib::Vector3 &vec_1,
                            const raylib::Vector3 &vec_2)
noexcept
{
  raylib::Vector3 out_vec;

  out_vec.x = vec_1.x - vec_2.x;
  out_vec.y = vec_1.y - vec_2.y;
  out_vec.z = vec_1.z - vec_2.z;

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

raylib::Vector3 unit_vectorize(const raylib::Vector3 &vec)
noexcept
{
  const float abs_length
  { sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z) };

  if (abs_length > 0.0f)
  {
    const raylib::Vector3 out
    { vec.x/abs_length, vec.y/abs_length, vec.z/abs_length };

    return out;
  }

  return vec;
}

float inproduct(const raylib::Vector3 &vec_1,
                const raylib::Vector3 &vec_2)
noexcept
{ return vec_1.x*vec_2.x + vec_1.y*vec_2.y + vec_1.z*vec_2.z; }

void rotate_first_second(raylib::Vector3 &first,
                         raylib::Vector3 &second,
                         raylib::Vector3 &inv_first,
                         raylib::Vector3 &inv_second,
                         const float theta)
noexcept
{
  raylib::Vector3 new_first
  { add_vector3(multiply_vector3(first, cos(theta)), multiply_vector3(second, sin(theta))) };

  raylib::Vector3 new_second
  { add_vector3(multiply_vector3(first, -sin(theta)), multiply_vector3(second, cos(theta))) };

  unit_vectorize(new_first);
  unit_vectorize(new_second);

  first = new_first;
  second = new_second;

  inv_first = multiply_vector3(first, -1);
  inv_second = multiply_vector3(second, -1);
}

void key_bindings(raylib::Camera &camera,
                  raylib::Vector3 &position,
                  raylib::Vector3 &forward,
                  raylib::Vector3 &backward,
                  raylib::Vector3 &rightward,
                  raylib::Vector3 &leftward,
                  raylib::Vector3 &upward,
                  raylib::Vector3 &downward,
                  const float velocity,
                  const float theta)
noexcept
{
  if (IsKeyDown('W'))
  { position = add_vector3(position, multiply_vector3(forward, velocity)); }

  if (IsKeyDown('S'))
  { position = add_vector3(position, multiply_vector3(backward, velocity)); }

  if (IsKeyDown('D'))
  { position = add_vector3(position, multiply_vector3(rightward, velocity)); }

  if (IsKeyDown('A'))
  { position = add_vector3(position, multiply_vector3(leftward, velocity)); }

  if (IsKeyDown('E'))
  { position = add_vector3(position, multiply_vector3(upward, velocity)); }

  if (IsKeyDown('Q'))
  { position = add_vector3(position, multiply_vector3(downward, velocity)); }

  if (IsKeyDown('L'))
  { rotate_first_second(forward, rightward, backward, leftward, theta); }

  if (IsKeyDown('J'))
  { rotate_first_second(forward, leftward, backward, rightward, theta); }

  if (IsKeyDown('I'))
  {
    rotate_first_second(forward, upward, backward, downward, theta);
    camera.up = upward;
  }

  if (IsKeyDown('K'))
  {
    rotate_first_second(forward, downward, backward, upward, theta);
    camera.up = upward;
  }

  if (IsKeyDown('O'))
  {
    rotate_first_second(upward, rightward, downward, leftward, theta);
    camera.up = upward;
  }

  if (IsKeyDown('U'))
  {
    rotate_first_second(upward, leftward, downward, rightward, theta);
    camera.up = upward;
  }
}

void wrapper(float &dim,
             const float wrap)
noexcept
{
  if (wrap > 0.0f &&
      abs(dim) > wrap)
  { dim -= 2.0f*wrap*dim/abs(dim); }
}

void wrapping(raylib::Vector3 &position,
              const float wrap)
noexcept
{
  wrapper(position.x, wrap);
  wrapper(position.y, wrap);
  wrapper(position.z, wrap);
}

float randist(std::random_device &rand,
              const float dist_min,
              const float dist_max)
noexcept
{
  float fraction
  { static_cast<float>(rand())/static_cast<float>(rand.max()) };

  if (rand() > rand.max()/2)
  { fraction *= -1.0f; }

  return dist_min + fraction*(dist_max - dist_min);
}

raylib::Vector3 ranpos(std::random_device &rand,
                       const float dist_min,
                       const float dist_max)
noexcept
{
  raylib::Vector3 position;

  bool loop
  { true };

  while (loop)
  {
    position.x = randist(rand, dist_min, dist_max);
    position.y = randist(rand, dist_min, dist_max);
    position.z = randist(rand, dist_min, dist_max);

    if (abs(position.x) > dist_min ||
        abs(position.y) > dist_min ||
        abs(position.z) > dist_min)
    { loop = false; }
  }

  return position;
}

unsigned char dimming(const float mult,
                      unsigned char channel)
noexcept
{ return static_cast<char>(mult*static_cast<float>(channel)); }

raylib::Color dimmer(const raylib::Vector3 &difference,
                     raylib::Color &cube_color,
                     const float decay)
noexcept
{
  const float distance
  { sqrt(inproduct(difference, difference)) };

  const float mult
  { pow(decay, distance) };

  return raylib::Color(dimming(mult, cube_color.r), dimming(mult, cube_color.g), dimming(mult, cube_color.b));
}

void display_cube(const raylib::Vector3 &position,
                  raylib::Vector3 &cube_position,
                  const raylib::Vector3 &cube_dims,
                  const raylib::Vector3 &forward,
                  raylib::Color &cube_color,
                  raylib::Color &edge_color,
                  const float cam_angle,
                  const float sight,
                  const float decay)
noexcept
{
  const raylib::Vector3 difference
  { sub_vector3(cube_position, position) };

  if (inproduct(unit_vectorize(difference), forward) > cam_angle &&
      inproduct(difference, difference) <= sight*sight)
  {
    const raylib::Color dim_color
    { dimmer(difference, cube_color, decay) };

    const raylib::Color dedge_color
    { dimmer(difference, edge_color, decay) };

    cube_position.DrawCube(cube_dims, dim_color);
    cube_position.DrawCubeWires(cube_dims, dedge_color);
  }
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

  const float wrap
  { 20.0f };

  const float decay
  { 0.5f };

  const float sight
  { 5.0f };

  const raylib::Vector3 cube_dims
  { side, side, side };

  const float dist_min
  { 3.0f };

  const float dist_max
  { 20.0f };

  raylib::Color cube_color
  { 127, 127, 127 };

  raylib::Color edge_color
  { 255, 255, 255 };

  std::random_device rand;

  const bool randomode
  { false };

  const int cube_amount
  { 1000 };

  std::vector <raylib::Vector3> cube_positions;

  for(int count{ 0 }; count < cube_amount; ++count)
  { cube_positions.push_back(ranpos(rand, dist_min, dist_max)); }

  raylib::Vector3 cube_position
  { 0.0f, 0.0f, 0.0f };
  // { ranpos(rand, dist_min, dist_max) };

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

  const float cam_angle
  { 0.3f };

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
    key_bindings(camera, position, forward, backward,
                 rightward, leftward, upward, downward,
                 velocity, theta);

    wrapping(position, wrap);

    camera.target = add_vector3(position, forward);

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
        if (randomode)
        {
          for (raylib::Vector3 cube_pos: cube_positions)
          {
            display_cube(position, cube_pos, cube_dims, forward,
                         cube_color, edge_color, cam_angle, sight, decay);
          }
        }
        else
        {
          display_cube(position, cube_position, cube_dims, forward,
                       cube_color, edge_color, cam_angle, sight, decay);
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
