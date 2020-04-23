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

  dungeon_loop d_loop;

  d_loop.run();

  return 0;
}
