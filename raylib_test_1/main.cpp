#include <iostream>
#include <string>
#include <vector>
#include <random>

#include <raylib.h>

#include "misc_functions.h"
#include "fractacube.h"
#include "dungeon_loop.h"

int main()
{
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 1200;
  const int screenHeight = 600;

  // Init VR simulator (Oculus Rift CV1 parameters)




  InitWindow(screenWidth, screenHeight, "Test 1 for raylib");






  //--------------------------------------------------------------------------------------

  dungeon_loop d_loop;

  d_loop.run();

  UnloadShader(distortion);   // Unload distortion shader

  CloseVrSimulator();         // Close VR simulator

  CloseWindow();

  return 0;
}
