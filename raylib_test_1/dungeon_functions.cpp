#include "dungeon_functions.h"

#include <cmath>
#include <time.h>

void dungeon_filler(std::vector< std::vector <std::vector <cube_type>>> &type_volume,

                    const int level,
                    const int dungeon_radius)
noexcept
{
  srand (time(NULL));

  {
    for(int x{ -dungeon_radius }; x <= dungeon_radius; ++x)
    {
      std::vector <std::vector <cube_type>> area;

      for(int y{ -dungeon_radius }; y <= dungeon_radius; ++y)
      {
       std::vector <cube_type> line;

        for(int z{ -dungeon_radius }; z <= dungeon_radius; ++z)
        {
          cube_type c_type
          { cube_type::none };

          level_filler(c_type, level, dungeon_radius, x, y, z);

          type_volume[x + dungeon_radius]
                     [y + dungeon_radius]
                     [z + dungeon_radius] = c_type;
        }
      }
    }
  }
}

void level_filler(cube_type &c_type,
                  const int level,
                  const int dungeon_radius,
                  const int x,
                  const int y,
                  const int z)
noexcept
{
  pillars(c_type, cube_type::concrete, x, y, z);

  if (level < 20)
  { random_wall(c_type, level, x, y, z); }

  outer_wall(c_type, cube_type::concrete, dungeon_radius, x, y, z);
}

void outer_wall(cube_type &c_type,
                const cube_type w_type,
                const int dungeon_radius,
                const int x,
                const int y,
                const int z)
noexcept
{
  if ((abs(x) == dungeon_radius ||
       abs(y) == dungeon_radius ||
       abs(z) == dungeon_radius))
  { c_type = w_type; }
}

void pillars(cube_type &c_type,
             const cube_type w_type,
             const int x,
             const int y,
             const int z)
noexcept
{
  if ((abs(x) % 2 == 1 &&
       abs(y) % 2 == 1) ||
      (abs(x) % 2 == 1 &&
       abs(z) % 2 == 1) ||
      (abs(z) % 2 == 1 &&
       abs(y) % 2 == 1))
  { c_type = w_type; }
}

void random_wall(cube_type &c_type,
                 const int level,
                 const int x,
                 const int y,
                 const int z)
noexcept
{
  const cube_type w_type
  { wall_type(level) };

  if (((abs(x) % 2 == 1 && abs(y) % 2 == 0 && abs(z) % 2 == 0) ||
       (abs(y) % 2 == 1 && abs(z) % 2 == 0 && abs(x) % 2 == 0)||
       (abs(z) % 2 == 1 && abs(x) % 2 == 0 && abs(y) % 2 == 0)) &&
       rand() % 100 < wall_percentage(w_type, level))
  { c_type = w_type; }
}

cube_type wall_type(const int level)
noexcept
{
  // return cube_type::none;

  if (level <= 4)
  { return cube_type::alabaster; }

  if (level >= 5 &&
      level <= 8)
  { return cube_type::concrete; }

  if (level == 9)
  { return cube_type::transparent; }

  if (level >= 10)
  { return cube_type::invisible; }

  return cube_type::none;
}

int wall_percentage(const cube_type c_type,
                    const int level)
noexcept
{
  if (c_type == cube_type::concrete ||
      c_type == cube_type::alabaster ||
      c_type == cube_type::invisible ||
      c_type == cube_type::transparent)
  {
    const int min_perc
    { 40 };

    const int max_perc
    { 80 };

    if (level < 40)
    { return min_perc + level; }
    else
    { return max_perc; }
  }

  return 0;
}

// cube_type wall_to_wall_crawler
