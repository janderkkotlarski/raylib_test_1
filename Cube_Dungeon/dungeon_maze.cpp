#include "dungeon_maze.h"

#include <cmath>
#include <time.h>
#include <cassert>

void dungeon_init(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
                  const int max_dungeon_radius)
noexcept
{
  assert(type_volume.size() == 0);

  for(int count_x{ 0 }; count_x <= 2*max_dungeon_radius; ++count_x)
  {
    std::vector <std::vector <cube_type>> area;

    for(int count_y{ 0 }; count_y <= 2*max_dungeon_radius; ++count_y)
    {
      std::vector <cube_type> line;

      for(int count_z{ 0 }; count_z <= 2*max_dungeon_radius; ++count_z)
      { line.push_back(cube_type::none); }

      assert(line.size() == unsigned(2*max_dungeon_radius + 1));
      area.push_back(line);
    }

    assert(area.size() == unsigned(2*max_dungeon_radius + 1));
    type_volume.push_back(area);
  }

  assert(type_volume.size() == unsigned(2*max_dungeon_radius + 1));
}

void dungeon_filler(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
                    const int level,
                    const int dungeon_radius)
noexcept
{
  srand (time(NULL));

  {
    for(int x{ 0 }; x <= 2*dungeon_radius; ++x)
    {
      std::vector <std::vector <cube_type>> area;

      for(int y{ 0 }; y <= 2*dungeon_radius; ++y)
      {
       std::vector <cube_type> line;

        for(int z{ 0 }; z <= 2*dungeon_radius; ++z)
        {
          cube_type c_type
          { cube_type::none };

          level_filler(c_type, level, dungeon_radius, x, y, z);

          type_volume[x]
                     [y]
                     [z] = c_type;
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
  c_type = cube_type::none;

  random_wall(c_type, level, dungeon_radius, x, y, z);

  outer_wall(c_type, cube_type::concrete, dungeon_radius, x, y, z);

  pillars(c_type, cube_type::concrete, dungeon_radius, x, y, z);
}



void outer_wall(cube_type &c_type,
                const cube_type w_type,
                const int dungeon_radius,
                const int x,
                const int y,
                const int z)
noexcept
{
  if ((abs(x - dungeon_radius) == dungeon_radius ||
       abs(y - dungeon_radius) == dungeon_radius ||
       abs(z - dungeon_radius) == dungeon_radius))
  { c_type = w_type; }
}

void pillars(cube_type &c_type,
             const cube_type w_type,
             const int dungeon_radius,
             const int x,
             const int y,
             const int z)
noexcept
{
  if ((abs(x - dungeon_radius) % 2 == 1 &&
       abs(y - dungeon_radius) % 2 == 1) ||
      (abs(x - dungeon_radius) % 2 == 1 &&
       abs(z - dungeon_radius) % 2 == 1) ||
      (abs(z - dungeon_radius) % 2 == 1 &&
       abs(y - dungeon_radius) % 2 == 1))
  { c_type = w_type; }
}

void random_wall(cube_type &c_type,
                 const int level,
                 const int dungeon_radius,
                 const int x,
                 const int y,
                 const int z)
noexcept
{
  const cube_type w_type
  { wall_type(level) };

  if (((abs(x - dungeon_radius) % 2 == 1 && abs(y - dungeon_radius) % 2 == 0 && abs(z - dungeon_radius) % 2 == 0) ||
       (abs(y - dungeon_radius) % 2 == 1 && abs(z - dungeon_radius) % 2 == 0 && abs(x - dungeon_radius) % 2 == 0)||
       (abs(z - dungeon_radius) % 2 == 1 && abs(x - dungeon_radius) % 2 == 0 && abs(y - dungeon_radius) % 2 == 0)) &&
       rand() % 100 < wall_percentage(w_type, level))
  { c_type = w_type; }
}

cube_type wall_type(const int level)
noexcept
{
  if (level >= 0 &&
      level <= 12)
  { return cube_type::concrete; }

  if (level == 13)
  { return cube_type::transparent; }

  if (level >= 14)
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

void single_placements(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
                       const int dungeon_radius, const int level)
noexcept
{


    plus_3d(type_volume, cube_type::none,
            2,
            dungeon_radius,
            dungeon_radius);

    if (level != 0)
    {
      plus_3d(type_volume, cube_type::none,
              2*dungeon_radius - 2,
              dungeon_radius,
              dungeon_radius);

      type_volume[2*dungeon_radius - 1]
                 [dungeon_radius]
                 [dungeon_radius] = cube_type::next;

      type_volume[1]
                 [dungeon_radius]
                 [dungeon_radius] = cube_type::previous;
    }
}

void plus_3d(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const cube_type &c_type,
             const int x,
             const int y,
             const int z)
noexcept
{
  for (unsigned sign { 0 }; sign < 2; ++sign)
  {
    type_volume[x - 1 + 2*sign][y][z] = c_type;
    type_volume[x][y - 1 + 2*sign][z] = c_type;
    type_volume[x][y][z - 1 + 2*sign] = c_type;
  }
}

void block_of_cubes(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
                    const cube_type &c_type,
                    const unsigned x1, const unsigned x2,
                    const unsigned y1, const unsigned y2,
                    const unsigned z1, const unsigned z2)
noexcept
{
  if (x1 <= x2 &&
      y1 <= y2 &&
      z1 <= z2)
  {
    for (unsigned index{ x1 }; index <= x2; ++index)
    {
      for (unsigned indey{ y1 }; indey <= y2; ++indey)
      {
        for (unsigned indez{ z1 }; indez <= z2; ++indez)
        { type_volume[index][indey][indez] = c_type; }
      }
    }
  }
}

void plane(cube_type &c_type,
           const cube_type &p_type,
           const unsigned pos,
           const unsigned plane_pos)
noexcept
{
  if (pos == plane_pos)
  { c_type = p_type; }
}
