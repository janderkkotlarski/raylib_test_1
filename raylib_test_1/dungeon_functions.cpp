#include "dungeon_functions.h"

#include <cmath>

void dungeon_filler(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
                    const int level,
                    const int dungeon_radius)
noexcept
{
  {
    for(int count_x{ -dungeon_radius }; count_x <= dungeon_radius; ++count_x)
    {
      std::vector <std::vector <cube_type>> area;

      for(int count_y{ -dungeon_radius }; count_y <= dungeon_radius; ++count_y)
      {
       std::vector <cube_type> line;

        for(int count_z{ -dungeon_radius }; count_z <= dungeon_radius; ++count_z)
        {
          cube_type c_type
          { cube_type::none };

          c_type = level_filler(level, dungeon_radius, count_x, count_y, count_z);

          type_volume[count_x + dungeon_radius]
                     [count_y + dungeon_radius]
                     [count_z + dungeon_radius] = c_type;
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
  { cube_type::none };

  if ((abs(x) % 2 == 1 &&
       abs(y) % 2 == 1) ||
      (abs(x) % 2 == 1 &&
       abs(z) % 2 == 1) ||
      (abs(z) % 2 == 1 &&
       abs(y) % 2 == 1))
  { c_type = cube_type::concrete; }

  return c_type;
}

// cube_type wall_to_wall_crawler
