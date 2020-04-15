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
  const int screenWidth = 800;
  const int screenHeight = 800;

  InitWindow(screenWidth, screenHeight, "Test 1 for raylib");

  SetTargetFPS(fps);  // Set our game to run at fps frames-per-second
  //--------------------------------------------------------------------------------------

  dungeon_loop d_loop;

  d_loop.run();

  return 0;
}
