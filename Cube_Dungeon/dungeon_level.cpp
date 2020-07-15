#include "dungeon_level.h"

#include <cassert>

#include "dungeon_maze.h"

void levels(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
            const int level, int &radius,
            std::vector <int> &start_posint)
noexcept
{
  block_of_cubes(type_volume, cube_type::none, 0, 2*radius, 0, 2*radius, 0, 2*radius);

  if (level == 1)
  { level_1(type_volume, level, radius, start_posint); }

  if (level == 2)
  { level_2(type_volume, level, radius, start_posint); }

  if (level == 3)
  { level_3(type_volume, level, radius, start_posint); }

  if (level == 4)
  { level_4(type_volume, level, radius, start_posint); }
}

void level_1(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  assert(start_posint.size() == 3);

  radius = 6;

  start_posint = { radius + 1, radius, radius };

  block_of_cubes(type_volume, cube_type::alabaster, 0, 2*radius, 0, 2*radius, 0, 2*radius);

  block_of_cubes(type_volume, cube_type::none, 0, radius - 2, radius, radius, radius, radius);

  block_of_cubes(type_volume, cube_type::none, radius + 1, 2*radius, radius, radius, radius, radius);

  type_volume[radius - 1][radius][radius] = cube_type::next;
}

void level_2(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  assert(start_posint.size() == 3);

  radius = 6;

  start_posint = { radius + 2, radius, radius };

  block_of_cubes(type_volume, cube_type::alabaster, 0, 2*radius, 0, 2*radius, 0, 2*radius);

  block_of_cubes(type_volume, cube_type::none, radius + 2, 2*radius, radius, radius, radius, radius);

  block_of_cubes(type_volume, cube_type::none, 0, radius - 3, radius, radius, radius, radius);

  block_of_cubes(type_volume, cube_type::none, radius - 2, radius - 2, 0, 2*radius, radius, radius);

  block_of_cubes(type_volume, cube_type::none, radius - 2, radius - 2, 1, 1, 0, 2*radius);

  block_of_cubes(type_volume, cube_type::none, radius, radius, radius, radius, 0, radius - 1);

  block_of_cubes(type_volume, cube_type::none, radius, radius, radius, radius, radius + 2, 2*radius);

  block_of_cubes(type_volume, cube_type::none, radius, radius, 0, radius - 1, radius + 2, radius + 2);

  block_of_cubes(type_volume, cube_type::none, radius, radius, radius + 1, 2*radius, radius + 2, radius + 2);

  block_of_cubes(type_volume, cube_type::none, 0, 2*radius, 2* radius - 1, 2*radius - 1, radius + 2, radius + 2);

  type_volume[radius + 2][0][radius + 2] = cube_type::none;
  type_volume[radius + 2][2*radius][radius + 2] = cube_type::none;

  type_volume[radius][radius][radius] = cube_type::next;
}

void level_3(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  assert(start_posint.size() == 3);

  radius = 6;

  start_posint = { radius + 2, radius, radius };

  block_of_cubes(type_volume, cube_type::concrete, 0, 2*radius, 0, 2*radius, 0, 2*radius);

  block_of_cubes(type_volume, cube_type::none, radius + 2, 2*radius, radius, radius, radius, radius);

  block_of_cubes(type_volume, cube_type::none, 0, radius - 3, radius, radius, radius, radius);

  block_of_cubes(type_volume, cube_type::none, radius - 2, radius - 2, 0, 2*radius, radius, radius);

  block_of_cubes(type_volume, cube_type::none, radius - 2, radius - 2, 2*radius - 1, 2*radius - 1, 0, 2*radius);

  block_of_cubes(type_volume, cube_type::none, radius, radius, radius, radius, 0, radius - 2);

  block_of_cubes(type_volume, cube_type::none, radius, radius, radius, radius, radius + 1, 2*radius);

  block_of_cubes(type_volume, cube_type::none, radius, radius, radius + 1, 2*radius, radius - 2, radius - 2);

  block_of_cubes(type_volume, cube_type::none, radius, radius, 0, radius - 1, radius - 2, radius - 2);

  block_of_cubes(type_volume, cube_type::none, 0, 2*radius, 1, 1, radius - 2, radius - 2);

  type_volume[radius + 1][radius][radius] = cube_type::previous;

  type_volume[radius - 2][0][radius - 2] = cube_type::none;
  type_volume[radius - 2][2*radius][radius - 2] = cube_type::none;

  type_volume[radius][radius][radius] = cube_type::next;
}

void level_4(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  assert(start_posint.size() == 3);

  radius = 6;

  start_posint = { radius + 1, radius, radius };

  block_of_cubes(type_volume, cube_type::concrete, 0, 2*radius, 0, 2*radius, 0, 2*radius);

  block_of_cubes(type_volume, cube_type::none, radius - 1, radius + 1, radius - 1, radius + 1, radius - 1, radius + 1);

  block_of_cubes(type_volume, cube_type::none, 0, 2*radius, radius, radius, radius, radius);

  block_of_cubes(type_volume, cube_type::none, radius, radius, 0, 2*radius, radius, radius);

  block_of_cubes(type_volume, cube_type::none, radius, radius, radius, radius, 0, 2*radius);

  type_volume[radius][radius][radius] = cube_type::previous;
}

void demo_1(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
            const int level, int &radius, std::vector<int> &start_posint)
noexcept
{ level_1(type_volume, level, radius, start_posint); }
