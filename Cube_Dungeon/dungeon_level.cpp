#include "dungeon_level.h"

#include <cassert>

#include "dungeon_maze.h"

void next_scanner(const std::vector< std::vector <std::vector <cube_type>>> &type_volume,
                  std::vector <int> &next_pos_int,
                  const int radius)
noexcept
{
  assert(next_pos_int.size() == 3);

  next_pos_int = { -1, -1, -1 };

  const int span
  { 2*radius + 1 };

  for (int x{ 0 }; x < span; ++x)
  {
    for (int y{ 0 }; y < span; ++y)
    {
      for (int z{ 0 }; z < span; ++z)
      {
        if (type_volume[x][y][z] == cube_type::next)
        { next_pos_int = { x, y, z }; }
      }
    }
  }
}

void level_wipe(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
                const int radius)
noexcept
{
  const int span
  { 2*radius + 1 };

  for (int x{ 0 }; x < span; ++x)
  {
    for (int y{ 0 }; y < span; ++y)
    {
      for (int z{ 0 }; z < span; ++z)
      { type_volume[x][y][z] = cube_type::none; }
    }
  }
}

void next_side(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
               const int span)
noexcept
{
  const std::vector <int> twin_coord
  { (rand() % (span - 2)) + 1,
    (rand() % (span - 2)) + 1 };

  const int one_pos
  { rand() % 3 };

  int twin
  { 0 };

  std::vector <int> next_pos;

  for (int count{ 0 }; count < 3; ++count)
  {
    if (count == one_pos)
    { next_pos.push_back(1); }
    else if (twin < 2)
    {
      next_pos.push_back(twin_coord[twin]);

      ++twin;
    }
  }

  type_volume[next_pos[0]][next_pos[1]][next_pos[2]] = cube_type::next;
}

void three_d_life(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
                  const std::vector <int> &pos_int,
                  const int radius)
noexcept
{
  const int span
  { 2*radius + 1 };

  const std::vector< std::vector <std::vector <cube_type>>> old_type_volume
  { type_volume };

  for (int x{ 0 }; x < span; ++x)
  {
    for (int y{ 0 }; y < span; ++y)
    {
      for (int z{ 0 }; z < span; ++z)
      {
        int conc
        { 0 };

        int empty
        { 0 };

        for (int a{ -1 }; a < 2; ++a)
        {
          const int xa = ((x + a) % span < 0) ? (span - 1) : ((x + a) % span);

          assert(xa >= 0);
          assert(xa < span);

          for (int b{ -1 }; b < 2; ++b)
          {
            const int yb = ((y + b) % span < 0) ? (span - 1) : ((y + b) % span);

            assert(yb >= 0);
            assert(yb < span);

            for (int c{ -1 }; c < 2; ++c)
            {
              const int zc = ((z + c) % span < 0) ? (span - 1) : ((z + c) % span);

              assert(zc >= 0);
              assert(zc < span);

              const cube_type old_type
              { old_type_volume[xa][yb][zc] };

              if (old_type == cube_type::concrete)
              { ++conc; }

              if (old_type == cube_type::none)
              { ++empty; }
            }
          }
        }

        const cube_type old_type
        { old_type_volume[x][y][z] };

        cube_type new_type
        { old_type };

        if (old_type == cube_type::concrete)
        {
          if (conc % 2 == 1)
          { new_type = cube_type::none; }
        }

        if (old_type == cube_type::none)
        {
          if (empty % 2 == 1)
          { new_type = cube_type::concrete; }
        }

        type_volume[x][y][z] = new_type;
      }
    }
  }

  type_volume[pos_int[0]][pos_int[1]][pos_int[2]] = cube_type::none;
}

void levels(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
            const int level, int &radius,
            std::vector <int> &start_posint)
noexcept
{
  assert(start_posint.size() == 3);

  block_of_cubes(type_volume, cube_type::none, 0, 2*radius, 0, 2*radius, 0, 2*radius);

  switch (level)
  {
    case 0:
      level_0(type_volume, level, radius, start_posint);
      break;
    case 1:
      level_1(type_volume, level, radius, start_posint);
      break;
    case 2:
      level_2(type_volume, level, radius, start_posint);
      break;
    case 3:
      level_3(type_volume, level, radius, start_posint);
      break;
    case 4:
      level_4(type_volume, level, radius, start_posint);
      break;
    case 5:
      level_5(type_volume, level, radius, start_posint);
      break;
    case 6:
      level_6(type_volume, level, radius, start_posint);
      break;
    case 7:
      level_7(type_volume, level, radius, start_posint);
      break;
    case 8:
      level_8(type_volume, level, radius, start_posint);
      break;
    case 9:
      level_9(type_volume, level, radius, start_posint);
      break;
    case 10:
      level_10(type_volume, level, radius, start_posint);
      break;
  }
}

void level_0(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  radius = 10;

  start_posint = { 2, radius, radius };

  dungeon_filler(type_volume, level, radius);

  single_placements(type_volume, radius, level);

  block_of_cubes(type_volume, cube_type::concrete, 1, 1, 0, 2*radius, 0, 2*radius);
  block_of_cubes(type_volume, cube_type::concrete, 2*radius - 1, 2*radius - 1, 0, 2*radius, 0, 2*radius);

  block_of_cubes(type_volume, cube_type::concrete, 0, 2*radius, 1, 1, 0, 2*radius);
  block_of_cubes(type_volume, cube_type::concrete, 0, 2*radius, 2*radius - 1, 2*radius - 1, 0, 2*radius);

  block_of_cubes(type_volume, cube_type::concrete, 0, 2*radius, 0, 2*radius, 1, 1);
  block_of_cubes(type_volume, cube_type::concrete, 0, 2*radius, 0, 2*radius, 2*radius - 1, 2*radius - 1);
}

void level_1(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  radius = 6;

  start_posint = { 1, radius, radius };

  block_of_cubes(type_volume, cube_type::concrete, 0, 2*radius, 0, 2*radius, 0, 2*radius);

  block_of_cubes(type_volume, cube_type::none, 1, 2*radius - 2, radius, radius, radius, radius);

  type_volume[2*radius - 1][radius][radius] = cube_type::next;
}

void level_2(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  radius = 6;

  start_posint = { 2, radius, radius };

  block_of_cubes(type_volume, cube_type::concrete, 0, 2*radius, 0, 2*radius, 0, 2*radius);

  block_of_cubes(type_volume, cube_type::none, 1, 2*radius - 2, radius, radius, radius, radius);

  block_of_cubes(type_volume, cube_type::none, radius - 1, radius + 1, radius - 1, radius + 1, radius - 1, radius + 1);

  type_volume[radius][radius][radius] = cube_type::concrete;

  type_volume[2*radius - 1][radius][radius] = cube_type::next;

  type_volume[1][radius][radius] = cube_type::previous;
}

void level_3(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  radius = 6;

  start_posint = { 2, radius, radius };

  block_of_cubes(type_volume, cube_type::concrete, 0, 2*radius, 0, 2*radius, 0, 2*radius);

  block_of_cubes(type_volume, cube_type::none, 1, 2*radius - 2, radius, radius, radius, radius);

  block_of_cubes(type_volume, cube_type::none, radius, radius, 0, 2*radius, radius, radius);

  block_of_cubes(type_volume, cube_type::none, radius, radius, radius, radius, 1, 2*radius - 1);

  type_volume[radius][radius][1] = cube_type::next;

  type_volume[1][radius][radius] = cube_type::previous;
}

void level_4(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  radius = 6;

  start_posint = { 2, radius, radius };

  block_of_cubes(type_volume, cube_type::concrete, 0, 2*radius, 0, 2*radius, 0, 2*radius);

  block_of_cubes(type_volume, cube_type::none, 1, 2*radius - 2, radius, radius, radius, radius);

  type_volume[radius][radius][radius] = cube_type::alabaster;

  type_volume[2*radius - 1][radius][radius] = cube_type::next;

  type_volume[1][radius][radius] = cube_type::previous;
}

void level_5(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  radius = 6;

  start_posint = { 2, radius, radius };

  block_of_cubes(type_volume, cube_type::none, 0, 2*radius, 0, 2*radius, 0, 2*radius);

  block_of_cubes(type_volume, cube_type::concrete, 1, 2*radius - 1, 1, 2*radius - 1, 1, 2*radius - 1);

  block_of_cubes(type_volume, cube_type::concrete, 0, 0, radius - 1, radius + 1, radius - 1, radius + 1);
  block_of_cubes(type_volume, cube_type::concrete, 2*radius , 2*radius, radius - 1, radius + 1, radius - 1, radius + 1);
  block_of_cubes(type_volume, cube_type::none, 0, 2*radius, radius, radius, radius, radius);

  block_of_cubes(type_volume, cube_type::concrete, radius - 1, radius + 1, 0, 0, radius - 1, radius + 1);
  block_of_cubes(type_volume, cube_type::concrete, radius - 1, radius + 1, 2*radius , 2*radius, radius - 1, radius + 1);
  type_volume[radius][0][radius + 1] = cube_type::alabaster;
  block_of_cubes(type_volume, cube_type::none, radius, radius, 0, 2*radius, radius, radius);

  block_of_cubes(type_volume, cube_type::concrete, radius - 1, radius + 1, radius - 1, radius + 1, 0, 0);
  block_of_cubes(type_volume, cube_type::concrete, radius - 1, radius + 1, radius - 1, radius + 1, 2*radius , 2*radius);
  block_of_cubes(type_volume, cube_type::none, radius, radius, radius, radius, 0, 2*radius);

  type_volume[2*radius][2*radius][2*radius] = cube_type::next;
  type_volume[1][radius][radius] = cube_type::previous;
}

void level_6(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  radius = 6;

  start_posint = { radius, radius, radius };

  block_of_cubes(type_volume, cube_type::concrete, 0, 2*radius, 0, 2*radius, 0, 2*radius);

  block_of_cubes(type_volume, cube_type::none, 1, 2*radius - 1, 1, 2*radius - 1, 1, 2*radius - 1);

  type_volume[1][1][1] = cube_type::next;

  type_volume[radius - 1][radius][radius] = cube_type::previous;
}

void level_7(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  radius = 2*level;

  start_posint = { 2, radius, radius };

  dungeon_filler(type_volume, level, radius);

  single_placements(type_volume, radius, level);
}

void level_hidden_1(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  radius = 10;

  start_posint = { radius + 2, radius, radius };

  block_of_cubes(type_volume, cube_type::none, 0, 2*radius, 0, 2*radius, 0, 2*radius);

  block_of_cubes(type_volume, cube_type::concrete, 1, 2*radius - 1, 1, 2*radius - 1, 1, 2*radius - 1); // concrete

  block_of_cubes(type_volume, cube_type::invisible, 0, 0, 0, 2*radius, 0, 2*radius);
  block_of_cubes(type_volume, cube_type::invisible, 2*radius, 2*radius, 0, 2*radius, 0, 2*radius);
  block_of_cubes(type_volume, cube_type::invisible, 0, 2*radius, 0, 0, 0, 2*radius);
  block_of_cubes(type_volume, cube_type::invisible, 0, 2*radius, 2*radius, 2*radius, 0, 2*radius);
  block_of_cubes(type_volume, cube_type::invisible, 0, 2*radius, 0, 2*radius, 0, 0);
  block_of_cubes(type_volume, cube_type::invisible, 0, 2*radius, 0, 2*radius, 2*radius, 2*radius);

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

  block_of_cubes(type_volume, cube_type::transparent, radius + 10, radius + 10, radius + 8, radius + 8, radius - 8, radius - 6);
  block_of_cubes(type_volume, cube_type::none, radius + 9, radius + 9, radius + 8, radius + 8, radius - 6, radius + 7);
  type_volume[radius + 9][radius + 8][radius + 8] = cube_type::special;

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

  block_of_cubes(type_volume, cube_type::none, radius - 5, radius - 5, radius + 8, radius + 8, radius - 6, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius - 5, radius - 5, radius - 8, radius + 8, radius + 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius - 5, radius - 5, radius - 8, radius - 8, radius - 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius - 5, radius - 5, radius - 8, radius + 8, radius - 8, radius - 8);

  type_volume[radius - 6][radius + 8][radius - 6] = cube_type::alabaster;

  block_of_cubes(type_volume, cube_type::none, radius - 7, radius - 7, radius + 8, radius + 8, radius - 6, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius - 7, radius - 7, radius - 8, radius + 8, radius + 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius - 7, radius - 7, radius - 8, radius - 8, radius - 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius - 7, radius - 7, radius - 8, radius + 8, radius - 8, radius - 8);

  type_volume[radius - 8][radius + 8][radius - 8] = cube_type::alabaster;

  block_of_cubes(type_volume, cube_type::none, radius - 9, radius - 9, radius + 8, radius + 8, radius - 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius - 9, radius - 9, radius - 8, radius + 8, radius + 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius - 9, radius - 9, radius - 8, radius - 8, radius - 8, radius + 8);
  block_of_cubes(type_volume, cube_type::none, radius - 9, radius - 9, radius - 8, radius + 6, radius - 8, radius - 8);

  type_volume[radius - 9][radius + 6][radius - 7] = cube_type::alabaster;

  block_of_cubes(type_volume, cube_type::none, radius - 9, radius - 9, radius - 6, radius + 6, radius - 6, radius - 6);
  block_of_cubes(type_volume, cube_type::none, radius - 9, radius - 9, radius - 6, radius - 6, radius - 6, radius + 6);
  block_of_cubes(type_volume, cube_type::none, radius - 9, radius - 9, radius - 6, radius + 6, radius + 6, radius + 6);
  block_of_cubes(type_volume, cube_type::none, radius - 9, radius - 9, radius + 6, radius + 6, radius - 4, radius + 6);

  type_volume[radius - 8][radius + 6][radius - 4] = cube_type::alabaster;

  block_of_cubes(type_volume, cube_type::none, radius - 7, radius - 7, radius - 6, radius + 6, radius - 6, radius - 6);
  block_of_cubes(type_volume, cube_type::none, radius - 7, radius - 7, radius - 6, radius - 6, radius - 6, radius + 6);
  block_of_cubes(type_volume, cube_type::none, radius - 7, radius - 7, radius - 6, radius + 6, radius + 6, radius + 6);
  block_of_cubes(type_volume, cube_type::none, radius - 7, radius - 7, radius + 6, radius + 6, radius - 4, radius + 6);

  type_volume[radius - 6][radius + 6][radius - 6] = cube_type::alabaster;

  block_of_cubes(type_volume, cube_type::none, radius - 5, radius - 5, radius - 6, radius + 4, radius - 6, radius - 6);
  block_of_cubes(type_volume, cube_type::none, radius - 5, radius - 5, radius - 6, radius - 6, radius - 6, radius + 6);
  block_of_cubes(type_volume, cube_type::none, radius - 5, radius - 5, radius - 6, radius + 6, radius + 6, radius + 6);
  block_of_cubes(type_volume, cube_type::none, radius - 5, radius - 5, radius + 6, radius + 6, radius - 6, radius + 6);

  type_volume[radius - 4][radius + 4][radius - 6] = cube_type::alabaster;

  block_of_cubes(type_volume, cube_type::none, radius - 3, radius - 3, radius - 6, radius + 4, radius - 6, radius - 6);
  block_of_cubes(type_volume, cube_type::none, radius - 3, radius - 3, radius - 6, radius - 6, radius - 6, radius + 6);
  block_of_cubes(type_volume, cube_type::none, radius - 3, radius - 3, radius - 6, radius + 6, radius + 6, radius + 6);
  block_of_cubes(type_volume, cube_type::none, radius - 3, radius - 3, radius + 6, radius + 6, radius - 6, radius + 6);

  type_volume[radius - 2][radius + 6][radius - 6] = cube_type::alabaster;

  block_of_cubes(type_volume, cube_type::none, radius - 1, radius - 1, radius - 6, radius + 6, radius - 6, radius - 6);
  block_of_cubes(type_volume, cube_type::none, radius - 1, radius - 1, radius - 6, radius - 6, radius - 6, radius + 6);
  block_of_cubes(type_volume, cube_type::none, radius - 1, radius - 1, radius - 6, radius + 6, radius + 6, radius + 6);
  block_of_cubes(type_volume, cube_type::none, radius - 1, radius - 1, radius + 6, radius + 6, radius - 4, radius + 6);

  type_volume[radius - 0][radius + 6][radius - 4] = cube_type::alabaster;

  block_of_cubes(type_volume, cube_type::none, radius + 1, radius + 1, radius - 6, radius + 6, radius - 6, radius - 6);
  block_of_cubes(type_volume, cube_type::none, radius + 1, radius + 1, radius - 6, radius - 6, radius - 6, radius + 6);
  block_of_cubes(type_volume, cube_type::none, radius + 1, radius + 1, radius - 6, radius + 6, radius + 6, radius + 6);
  block_of_cubes(type_volume, cube_type::none, radius + 1, radius + 1, radius + 6, radius + 6, radius - 4, radius + 6);

  type_volume[radius + 2][radius + 6][radius - 6] = cube_type::alabaster;

  block_of_cubes(type_volume, cube_type::none, radius + 3, radius + 3, radius - 6, radius + 4, radius - 6, radius - 6);
  block_of_cubes(type_volume, cube_type::none, radius + 3, radius + 3, radius - 6, radius - 6, radius - 6, radius + 6);
  block_of_cubes(type_volume, cube_type::none, radius + 3, radius + 3, radius - 6, radius + 6, radius + 6, radius + 6);
  block_of_cubes(type_volume, cube_type::none, radius + 3, radius + 3, radius + 6, radius + 6, radius - 6, radius + 6);

  type_volume[radius + 4][radius + 4][radius - 6] = cube_type::alabaster;

  block_of_cubes(type_volume, cube_type::none, radius + 5, radius + 5, radius - 6, radius + 4, radius - 6, radius - 6);
  block_of_cubes(type_volume, cube_type::none, radius + 5, radius + 5, radius - 6, radius - 6, radius - 6, radius + 6);
  block_of_cubes(type_volume, cube_type::none, radius + 5, radius + 5, radius - 6, radius + 6, radius + 6, radius + 6);
  block_of_cubes(type_volume, cube_type::none, radius + 5, radius + 5, radius + 6, radius + 6, radius - 6, radius + 6);

  type_volume[radius + 6][radius + 6][radius - 6] = cube_type::alabaster;

  block_of_cubes(type_volume, cube_type::none, radius + 7, radius + 7, radius - 6, radius + 6, radius - 6, radius - 6);
  block_of_cubes(type_volume, cube_type::none, radius + 7, radius + 7, radius - 6, radius - 6, radius - 6, radius + 6);
  block_of_cubes(type_volume, cube_type::none, radius + 7, radius + 7, radius - 6, radius + 6, radius + 6, radius + 6);
  block_of_cubes(type_volume, cube_type::none, radius + 7, radius + 7, radius + 6, radius + 6, radius - 4, radius + 6);

  type_volume[radius + 7][radius + 5][radius - 4] = cube_type::alabaster;

  cube_type strobo = cube_type::none;

  for (int count{ 6 }; count >= 0; --count)
  {
    if (count % 2 == 0)
    { strobo = cube_type::none; }
    else
    { strobo = cube_type::concrete; }

    block_of_cubes(type_volume, strobo,
                   radius - 9 + 6 - count, radius + 7,
                   radius - count, radius + count,
                   radius - count, radius + count);
  }

  type_volume[radius + 3][radius - 5][radius + 2] = cube_type::transparent;
  type_volume[radius - 3][radius + 2][radius - 3] = cube_type::transparent;
  type_volume[radius - 4][radius][radius] = cube_type::setback;

  type_volume[radius - 1][radius][radius] = cube_type::next;
  type_volume[radius][radius][radius] = cube_type::concrete;
  type_volume[radius + 1][radius][radius] = cube_type::previous;

  block_of_cubes(type_volume, cube_type::none,
                 radius + 2, radius + 9,
                 radius, radius,
                 radius, radius);
}

void level_8(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  radius = level;

  const int span
  { 2*radius + 1 };

  for (int x{ 0 }; x < span; ++x)
  {
    for (int y{ 0 }; y < span; ++y)
    {
      for (int z{ 0 }; z < span; ++z)
      {
        const int promille
        { rand() % 1000 };

        if (promille < 400)
        { type_volume[x][y][z] = cube_type::concrete; }
        else if (promille < 500)
        { type_volume[x][y][z] = cube_type::ruby; }
        else if (promille < 525)
        { type_volume[x][y][z] = cube_type::citrine; }
        else if (promille < 531)
        { type_volume[x][y][z] = cube_type::emerald; }
        else if (promille < 533)
        { type_volume[x][y][z] = cube_type::sapphire; }
        else if (promille < 550)
        { type_volume[x][y][z] = cube_type::setback; }
        else
        { type_volume[x][y][z] = cube_type::none; }
      }
    }
  }

  type_volume[radius][radius][radius] = cube_type::previous;
  type_volume[radius + 1][radius][radius] = cube_type::none;

  start_posint = { radius + 1, radius, radius };

  next_side(type_volume, span);
}

void level_9(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  radius = level;

  const int span
  { 2*radius + 1 };

  level_wipe(type_volume, radius);

  start_posint = { radius + 1, radius, radius };

  for (int count{ 0 }; count < 12; ++count)
  { type_volume[radius + 4][radius - 6 + count][radius] = index2type(count); }

  type_volume[radius][radius][radius] = cube_type::previous;
  type_volume[radius + 1][radius][radius] = cube_type::none;

  next_side(type_volume, span);
}

void level_10(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept
{
  radius = level;

  const int span
  { 2*radius + 1 };

  for (int x{ 0 }; x < span; ++x)
  {
    for (int y{ 0 }; y < span; ++y)
    {
      for (int z{ 0 }; z < span; ++z)
      {
        const int promille
        { rand() % 1000 };

        if (promille < 500)
        { type_volume[x][y][z] = cube_type::concrete; }
        else
        { type_volume[x][y][z] = cube_type::none; }
      }
    }
  }

  start_posint = { radius + 1, radius, radius };

  block_of_cubes(type_volume, cube_type::concrete, radius, radius + 3, radius - 1, radius + 1, radius - 1, radius + 1);

  type_volume[radius][radius][radius] = cube_type::previous;
  type_volume[radius + 1][radius][radius] = cube_type::none;
  type_volume[radius + 2][radius][radius] = cube_type::none;

  next_side(type_volume, span);
}

void demo_1(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
            const int level, int &radius, std::vector<int> &start_posint)
noexcept
{ level_1(type_volume, level, radius, start_posint); }

void demo_2(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
            const int level, int &radius, std::vector<int> &start_posint)
noexcept
{ level_2(type_volume, level, radius, start_posint); }
