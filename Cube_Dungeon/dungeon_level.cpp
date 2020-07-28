#include "dungeon_level.h"

#include <cassert>

#include "dungeon_maze.h"

void levels(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
            const int level, int &radius,
            std::vector <int> &start_posint)
noexcept
{
  assert(start_posint.size() == 3);

  block_of_cubes(type_volume, cube_type::none, 0, 2*radius, 0, 2*radius, 0, 2*radius);

  if (level == 1)
  { level_1(type_volume, level, radius, start_posint); }

  if (level == 2)
  { level_2(type_volume, level, radius, start_posint); }

  if (level == 3)
  { level_3(type_volume, level, radius, start_posint); }

  if (level == 4)
  { level_4(type_volume, level, radius, start_posint); }

  if (level == 5)
  { level_5(type_volume, level, radius, start_posint); }

  if (level == 6)
  { level_6(type_volume, level, radius, start_posint); }

  if (level == 7)
  { level_7(type_volume, level, radius, start_posint); }
}

void level_1(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
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

  type_volume[radius - 2][0][radius + 2] = cube_type::none;
  type_volume[radius - 2][2*radius][radius + 2] = cube_type::none;

  type_volume[radius][radius][radius] = cube_type::next;
}

void level_3(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  radius = 12;

  start_posint = { radius + 2, radius, radius };

  block_of_cubes(type_volume, cube_type::concrete, 0, 2*radius, 0, 2*radius, 0, 2*radius);

  for (int count_x{ -3 }; count_x <= 2; ++count_x)
  {
    const int x = 4*count_x + 2;

    const int x2 = 4*count_x;

    for (int count_y{ -3 }; count_y <= 2; ++count_y)
    {
      const int y = 4*count_y + 2;

      const int y2 = 4*count_y;

      {
        block_of_cubes(type_volume, cube_type::none, 0, 2*radius,
                                                     radius + x, radius + x,
                                                     radius + y, radius + y);

        block_of_cubes(type_volume, cube_type::none, radius + x, radius + x,
                                                     0, 2*radius,
                                                     radius + y, radius + y);

        block_of_cubes(type_volume, cube_type::none, radius + x, radius + x,
                                                     radius + y, radius + y,
                                                     0, 2*radius);
      }

      if (abs(count_x) != 3 &&
          abs(count_y) != 3)
      {
        block_of_cubes(type_volume, cube_type::none, 0, 2*radius,
                                                     radius + x2, radius + x2,
                                                     radius + y2, radius + y2);

        block_of_cubes(type_volume, cube_type::none, radius + x2, radius + x2,
                                                     0, 2*radius,
                                                     radius + y2, radius + y2);

        block_of_cubes(type_volume, cube_type::none, radius + x2, radius + x2,
                                                     radius + y2, radius + y2,
                                                     0, 2*radius);
      }
    }
  }

  type_volume[radius - 2][radius - 1][radius] = cube_type::alabaster;
  type_volume[radius - 2][radius + 1][radius] = cube_type::alabaster;

  type_volume[radius - 2][radius][radius - 1] = cube_type::alabaster;
  type_volume[radius - 2][radius][radius + 1] = cube_type::alabaster;

  type_volume[radius - 1][radius - 2][radius] = cube_type::alabaster;
  type_volume[radius + 1][radius - 2][radius] = cube_type::alabaster;

  type_volume[radius][radius - 2][radius - 1] = cube_type::alabaster;
  type_volume[radius][radius - 2][radius + 1] = cube_type::alabaster;

  type_volume[radius - 1][radius + 2][radius] = cube_type::alabaster;
  type_volume[radius + 1][radius + 2][radius] = cube_type::alabaster;

  type_volume[radius][radius + 2][radius - 1] = cube_type::alabaster;
  type_volume[radius][radius + 2][radius + 1] = cube_type::alabaster;

  type_volume[radius][radius - 1][radius - 2] = cube_type::alabaster;
  type_volume[radius][radius + 1][radius - 2] = cube_type::alabaster;

  type_volume[radius - 1][radius][radius - 2] = cube_type::alabaster;
  type_volume[radius + 1][radius][radius - 2] = cube_type::alabaster;

  type_volume[radius][radius - 1][radius + 2] = cube_type::alabaster;
  type_volume[radius][radius + 1][radius + 2] = cube_type::alabaster;

  type_volume[radius - 1][radius][radius + 2] = cube_type::alabaster;
  type_volume[radius + 1][radius][radius + 2] = cube_type::alabaster;

  type_volume[radius - 1][radius][radius] = cube_type::concrete;
  type_volume[radius + 1][radius][radius] = cube_type::previous;

  type_volume[radius][radius - 1][radius] = cube_type::concrete;
  type_volume[radius][radius + 1][radius] = cube_type::concrete;

  type_volume[radius][radius][radius - 1] = cube_type::concrete;
  type_volume[radius][radius][radius + 1] = cube_type::concrete;

  type_volume[radius][radius][radius] = cube_type::next;
}

void level_4(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  assert(start_posint.size() == 3);

  radius = 10;

  start_posint = { radius + 1, radius, radius };

  block_of_cubes(type_volume, cube_type::concrete, 0, 2*radius, 0, 2*radius, 0, 2*radius);

  for (int count_x{ -1 }; count_x <= 1; ++count_x)
  {
    for (int count_y{ -1 }; count_y <= 1; ++count_y)
    {
      for (int count_z{ -1 }; count_z <= 1; ++count_z)
      {
        block_of_cubes(type_volume, cube_type::none, radius - 2 + 7*count_x, radius + 2 + 7*count_x,
                                                     radius - 2 + 7*count_y, radius + 2 + 7*count_y,
                                                     radius - 2 + 7*count_z, radius + 2 + 7*count_z);

        block_of_cubes(type_volume, cube_type::concrete, radius - 1 + 7*count_x, radius + 1 + 7*count_x,
                                                         radius - 1 + 7*count_y, radius + 1 + 7*count_y,
                                                         radius - 1 + 7*count_z, radius + 1 + 7*count_z);
      }
    }
  }

  for (int count_x{ -1 }; count_x <= 1; ++count_x)
  {
    for (int count_y{ -1 }; count_y <= 1; ++count_y)
    {
      block_of_cubes(type_volume, cube_type::none, 0, 2*radius,
                                                   radius + 7*count_x, radius + 7*count_x,
                                                   radius + 7*count_y, radius + 7*count_y);

      block_of_cubes(type_volume, cube_type::none, radius + 7*count_x, radius + 7*count_x,
                                                   0, 2*radius,
                                                   radius + 7*count_y, radius + 7*count_y);

      block_of_cubes(type_volume, cube_type::none, radius + 7*count_x, radius + 7*count_x,
                                                   radius + 7*count_y, radius + 7*count_y,
                                                   0, 2*radius);
    }
  }

  for (int count_x{ -1 }; count_x <= 1; ++count_x)
  {
    for (int count_y{ -1 }; count_y <= 1; ++count_y)
    {
      for (int count_z{ -1 }; count_z <= 1; ++count_z)
      { type_volume[radius + 7*count_x][radius + 7*count_y][radius + 7*count_z] = cube_type::previous; }
    }
  }
}

void level_5(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  radius = 10;

  start_posint = { radius + 2, radius, radius };

  block_of_cubes(type_volume, cube_type::concrete, 0, 2*radius, 0, 2*radius, 0, 2*radius);

  type_volume[radius + 1][radius][radius] = cube_type::previous;

  type_volume[radius - 1][radius][radius] = cube_type::next;

  block_of_cubes(type_volume, cube_type::none, radius + 2, 2*radius, radius, radius, radius, radius);
  block_of_cubes(type_volume, cube_type::none, 0, radius - 3, radius, radius, radius, radius);

  block_of_cubes(type_volume, cube_type::none, radius - 3, radius - 3, 0, 2*radius, radius, radius);
  block_of_cubes(type_volume, cube_type::none, radius - 3, radius - 3, radius, radius, 0, 2*radius);

  type_volume[radius - 3][radius - 1][radius] = cube_type::alabaster;
  type_volume[radius - 3][radius + 1][radius] = cube_type::alabaster;

  type_volume[radius - 3][radius][radius - 1] = cube_type::alabaster;
  type_volume[radius - 3][radius][radius + 1] = cube_type::alabaster;

  block_of_cubes(type_volume, cube_type::none, 2*radius - 1, 2*radius - 1, 1, 2*radius - 1, radius, radius);
  block_of_cubes(type_volume, cube_type::none, 2*radius - 1, 2*radius - 1, radius, radius, 1, 2*radius - 1);

  block_of_cubes(type_volume, cube_type::none, 2*radius - 1, 2*radius - 1, radius + 1, 2*radius - 1, 1, 1);
  block_of_cubes(type_volume, cube_type::none, 2*radius - 1, 2*radius - 1, 1, radius - 1, 2*radius - 1, 2*radius - 1);

  type_volume[2*radius - 1][radius - 3][radius] = cube_type::ruby;
  type_volume[2*radius - 1][radius + 3][radius] = cube_type::ruby;
  type_volume[2*radius - 1][radius][radius - 3] = cube_type::ruby;
  type_volume[2*radius - 1][radius][radius + 3] = cube_type::ruby;

  type_volume[2*radius - 1][3][radius] = cube_type::ruby;
  type_volume[2*radius - 1][2*radius - 3][radius] = cube_type::ruby;
  type_volume[2*radius - 1][radius][3] = cube_type::ruby;
  type_volume[2*radius - 1][radius][2*radius - 3] = cube_type::ruby;

  block_of_cubes(type_volume, cube_type::none, 2*radius - 1, 2*radius - 1, 1, 1,  1, radius - 1);
  block_of_cubes(type_volume, cube_type::none, 2*radius - 1, 2*radius - 1, 2*radius - 1, 2*radius - 1, radius + 1, 2*radius - 1);

  block_of_cubes(type_volume, cube_type::none, 1, 2*radius - 1, 1, 1,  1, 1);
  block_of_cubes(type_volume, cube_type::none, 1, 2*radius - 1, 2*radius - 1, 2*radius - 1,  2*radius - 1, 2*radius - 1);

  block_of_cubes(type_volume, cube_type::none, 1, 2*radius - 1, 1, 1,  2*radius - 1, 2*radius - 1);
  block_of_cubes(type_volume, cube_type::none, 1, 2*radius - 1, 2*radius - 1, 2*radius - 1,  1, 1);

  block_of_cubes(type_volume, cube_type::none, 1, 1, 1, radius - 2, 1, 1);
  block_of_cubes(type_volume, cube_type::none, 1, 1, radius + 2, 2*radius - 1, 2*radius - 1, 2*radius - 1);

  block_of_cubes(type_volume, cube_type::none, 1, 1, 1, 1, radius + 2, 2*radius - 1);
  block_of_cubes(type_volume, cube_type::none, 1, 1, 2*radius - 1, 2*radius - 1,  1, radius - 2);

  block_of_cubes(type_volume, cube_type::none, 1, 1, radius - 2, radius - 2, 1, radius - 2);
  block_of_cubes(type_volume, cube_type::none, 1, 1, radius + 2, radius + 2, radius + 2, 2*radius - 1);

  block_of_cubes(type_volume, cube_type::none, 1, 1, radius + 2, 2*radius - 1, radius - 2, radius - 2);
  block_of_cubes(type_volume, cube_type::none, 1, 1, 1, radius - 2, radius + 2, radius + 2);

  block_of_cubes(type_volume, cube_type::none, 1, 2*radius - 1, radius - 2, radius - 2, radius - 2, radius - 2);
  block_of_cubes(type_volume, cube_type::none, 1, 2*radius - 1, radius + 2, radius + 2, radius - 2, radius - 2);
  block_of_cubes(type_volume, cube_type::none, 1, 2*radius - 1, radius - 2, radius - 2, radius + 2, radius + 2);
  block_of_cubes(type_volume, cube_type::none, 1, 2*radius - 1, radius + 2, radius + 2, radius + 2, radius + 2);

  type_volume[radius - 1][radius - 2][radius - 1] = cube_type::alabaster;
  type_volume[radius - 1][radius - 2][radius] = cube_type::alabaster;
  type_volume[radius - 1][radius - 2][radius + 1] = cube_type::alabaster;
  type_volume[radius - 1][radius - 2][radius + 2] = cube_type::alabaster;

  type_volume[radius - 1][radius + 2][radius - 1] = cube_type::alabaster;
  type_volume[radius - 1][radius + 2][radius] = cube_type::alabaster;
  type_volume[radius - 1][radius + 2][radius + 1] = cube_type::alabaster;
  type_volume[radius - 1][radius + 2][radius + 2] = cube_type::alabaster;

  type_volume[radius - 1][radius - 1][radius - 2] = cube_type::alabaster;
  type_volume[radius - 1][radius][radius - 2] = cube_type::alabaster;
  type_volume[radius - 1][radius + 1][radius - 2] = cube_type::alabaster;
  type_volume[radius - 1][radius + 2][radius - 2] = cube_type::alabaster;

  type_volume[radius - 1][radius - 1][radius + 2] = cube_type::alabaster;
  type_volume[radius - 1][radius][radius + 2] = cube_type::alabaster;
  type_volume[radius - 1][radius + 1][radius + 2] = cube_type::alabaster;
  type_volume[radius - 1][radius + 2][radius + 2] = cube_type::alabaster;

  type_volume[radius - 1][radius - 1][radius] = cube_type::alabaster;
  type_volume[radius - 1][radius + 1][radius] = cube_type::alabaster;
  type_volume[radius - 1][radius][radius - 1] = cube_type::alabaster;
  type_volume[radius - 1][radius][radius + 1] = cube_type::alabaster;
}

void level_6(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  radius = 3*level;

  dungeon_filler(type_volume, level, radius);

  start_posint = { 2, radius, radius };

  type_volume[1][radius][radius] = cube_type::previous;
  type_volume[3][radius][radius] = cube_type::none;
  type_volume[2][radius - 1][radius] = cube_type::none;
  type_volume[2][radius + 1][radius] = cube_type::none;
  type_volume[2][radius][radius - 1] = cube_type::none;
  type_volume[2][radius][radius + 1] = cube_type::none;

  type_volume[2*radius - 1][radius][radius] = cube_type::next;
  type_volume[2*radius - 3][radius][radius] = cube_type::none;
  type_volume[2*radius - 2][radius - 1][radius] = cube_type::none;
  type_volume[2*radius - 2][radius + 1][radius] = cube_type::none;
  type_volume[2*radius - 2][radius][radius - 1] = cube_type::none;
  type_volume[2*radius - 2][radius][radius + 1] = cube_type::none;
}

void level_7(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  radius = 10;

  start_posint = { radius + 2, radius, radius };

  block_of_cubes(type_volume, cube_type::concrete, 0, 2*radius, 0, 2*radius, 0, 2*radius);

  block_of_cubes(type_volume, cube_type::none, radius + 2, radius + 9, radius, radius, radius, radius);

  type_volume[radius + 6][radius][radius] = cube_type::setback;

  block_of_cubes(type_volume, cube_type::none, radius + 9, radius + 9, radius, radius, radius, radius + 2);
  block_of_cubes(type_volume, cube_type::none, radius + 9, radius + 9, radius - 2, radius, radius + 2, radius + 2);

  block_of_cubes(type_volume, cube_type::none, radius + 9, radius + 9, radius - 2, radius - 2, radius - 2, radius + 2);
  block_of_cubes(type_volume, cube_type::none, radius + 9, radius + 9, radius - 2, radius + 2, radius - 2, radius - 2);

  block_of_cubes(type_volume, cube_type::none, radius + 9, radius + 9, radius + 2, radius + 2, radius - 2, radius + 4);
  block_of_cubes(type_volume, cube_type::none, radius + 9, radius + 9, radius - 4, radius + 2, radius + 4, radius + 4);

  block_of_cubes(type_volume, cube_type::none, radius + 9, radius + 9, radius - 4, radius - 4, radius - 4, radius + 4);
  block_of_cubes(type_volume, cube_type::none, radius + 9, radius + 9, radius - 4, radius + 4, radius - 4, radius - 4);

  block_of_cubes(type_volume, cube_type::none, radius + 9, radius + 9, radius + 4, radius + 4, radius - 4, radius + 6);
  block_of_cubes(type_volume, cube_type::none, radius + 9, radius + 9, radius - 6, radius + 4, radius + 6, radius + 6);

  block_of_cubes(type_volume, cube_type::none, radius + 9, radius + 9, radius - 6, radius - 6, radius - 6, radius + 6);
  block_of_cubes(type_volume, cube_type::none, radius + 9, radius + 9, radius - 6, radius + 6, radius - 6, radius - 6);

  block_of_cubes(type_volume, cube_type::none, radius + 9, radius + 9, radius + 6, radius + 6, radius - 6, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius + 9, radius + 9, radius - 8, radius + 6, radius + 8, radius + 8);

  block_of_cubes(type_volume, cube_type::none, radius + 9, radius + 9, radius - 8, radius - 8, radius - 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius + 9, radius + 9, radius - 8, radius + 8, radius - 8, radius - 8);

  type_volume[radius + 8][radius + 8][radius - 8] = cube_type::alabaster;

  block_of_cubes(type_volume, cube_type::none, radius + 7, radius + 7, radius + 8, radius + 8, radius - 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius + 7, radius + 7, radius - 8, radius + 8, radius + 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius + 7, radius + 7, radius - 8, radius - 8, radius - 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius + 7, radius + 7, radius - 8, radius + 6, radius - 8, radius - 8);

  type_volume[radius + 6][radius + 6][radius - 8] = cube_type::alabaster;

  block_of_cubes(type_volume, cube_type::none, radius + 5, radius + 5, radius + 8, radius + 8, radius - 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius + 5, radius + 5, radius - 8, radius + 8, radius + 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius + 5, radius + 5, radius - 8, radius - 8, radius - 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius + 5, radius + 5, radius - 8, radius + 6, radius - 8, radius - 8);

  type_volume[radius + 4][radius + 8][radius - 8] = cube_type::alabaster;

  block_of_cubes(type_volume, cube_type::none, radius + 3, radius + 3, radius + 8, radius + 8, radius - 6, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius + 3, radius + 3, radius - 8, radius + 8, radius + 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius + 3, radius + 3, radius - 8, radius - 8, radius - 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius + 3, radius + 3, radius - 8, radius + 8, radius - 8, radius - 8);

  type_volume[radius + 3][radius - 8][radius] = cube_type::setback;

  type_volume[radius + 2][radius + 8][radius - 6] = cube_type::alabaster;

  block_of_cubes(type_volume, cube_type::none, radius + 1, radius + 1, radius + 8, radius + 8, radius - 6, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius + 1, radius + 1, radius - 8, radius + 8, radius + 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius + 1, radius + 1, radius - 8, radius - 8, radius - 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius + 1, radius + 1, radius - 8, radius + 8, radius - 8, radius - 8);

  type_volume[radius + 0][radius + 8][radius - 8] = cube_type::alabaster;

  block_of_cubes(type_volume, cube_type::none, radius - 1, radius - 1, radius + 8, radius + 8, radius - 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius - 1, radius - 1, radius - 8, radius + 8, radius + 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius - 1, radius - 1, radius - 8, radius - 8, radius - 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius - 1, radius - 1, radius - 8, radius + 6, radius - 8, radius - 8);

  type_volume[radius - 2][radius + 6][radius - 8] = cube_type::alabaster;

  block_of_cubes(type_volume, cube_type::none, radius - 3, radius - 3, radius + 8, radius + 8, radius - 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius - 3, radius - 3, radius - 8, radius + 8, radius + 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius - 3, radius - 3, radius - 8, radius - 8, radius - 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius - 3, radius - 3, radius - 8, radius + 6, radius - 8, radius - 8);

  type_volume[radius - 4][radius + 8][radius - 8] = cube_type::alabaster;
}


void demo_1(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
            const int level, int &radius, std::vector<int> &start_posint)
noexcept
{ level_1(type_volume, level, radius, start_posint); }
