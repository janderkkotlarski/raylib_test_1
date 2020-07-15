#include "dungeon_level.h"

#include <cassert>

#include "dungeon_maze.h"

void level_1(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  assert(start_posint.size() == 3);

  radius = 6;

  start_posint = { radius + 1, radius, radius };

  block_of_cubes(type_volume, cube_type::alabaster, 0, 2*radius, 0, 2*radius, 0, 2*radius);

  block_of_cubes(type_volume, cube_type::none, 0, radius - 1, radius, radius, radius, radius);

  block_of_cubes(type_volume, cube_type::none, radius + 1, 2*radius, radius, radius, radius, radius);

}
