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

          c_type = level_filler(level, dungeon_radius, x, y, z);

          type_volume[x + dungeon_radius]
                     [y + dungeon_radius]
                     [z + dungeon_radius] = c_type;
        }
      }
    }
  }
}

cube_type level_filler(const int level,
                     const int dungeon_radius,
                     const int x,
                     const int y,
                     const int z)
noexcept
{
  cube_type c_type
  { cube_type::none };

  if (level < 20)
  { c_type = wall_to_wall_dungeon(level, dungeon_radius, x, y, z); }

  return c_type;
}

cube_type wall_to_wall_dungeon(const int level,
                               const int dungeon_radius,
                               const int x,
                               const int y,
                               const int z)
noexcept
{
  cube_type c_type
  { wall_type(level) };

  if ((abs(x) % 2 == 1 &&
       abs(y) % 2 == 1) ||
      (abs(x) % 2 == 1 &&
       abs(z) % 2 == 1) ||
      (abs(z) % 2 == 1 &&
       abs(y) % 2 == 1))
  { return cube_type::concrete; }
  else if((abs(x) % 2 == 1 ||
           abs(y) % 2 == 1 ||
           abs(z) % 2 == 1) &&
           rand() % 100 < wall_percentage(c_type, level))
  { return c_type; }

  if (abs(x) == dungeon_radius ||
      abs(y) == dungeon_radius ||
      abs(z) == dungeon_radius)
  { return cube_type::concrete; }

  return c_type;
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
