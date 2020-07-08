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
  if (level == 1)
  { c_type = cube_type::ruby; }

  if (level == 2)
  {
    const int dist
    { 5 };

    if ((abs(x) - dist) % (2*dist) == 0 ||
        (abs(y) - dist) % (2*dist) == 0 ||
        (abs(z) - dist) % (2*dist) == 0)
    { c_type = cube_type::concrete; }

    if (abs(x) % (2*dist) == 0 &&
        abs(y) % (2*dist) == 0 &&
        abs(z) % (2*dist) == 0)
    { c_type = cube_type::catalyst; }
  }

  if (level >= 3)
  { pillars(c_type, cube_type::concrete, x, y, z); }

  if (level >= 3 &&
      level < 20)
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

void single_placements(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
                       const int level,
                       const int dungeon_radius)
noexcept
{
  if (level <= 2)
  {
    type_volume[dungeon_radius - 2]
               [dungeon_radius - 2]
               [dungeon_radius - 2] = cube_type::next;

    /*
    plus_3d(type_volume, cube_type::ruby,
            dungeon_radius,
            dungeon_radius,
            dungeon_radius);
            */
  }

  if (level >= 3)
  {
    plus_3d(type_volume, cube_type::none,
            2*dungeon_radius - 2,
            dungeon_radius,
            dungeon_radius);

    type_volume[2*dungeon_radius - 1]
               [dungeon_radius]
               [dungeon_radius] = cube_type::next;

    plus_3d(type_volume, cube_type::none,
            2,
            dungeon_radius,
            dungeon_radius);
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

void cube_of_cubes(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
                   const cube_type &c_type,
                   const unsigned x1, const unsigned x2,
                   const unsigned y1, const unsigned y2,
                   const unsigned z1, const unsigned z2)
noexcept
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

void plane(cube_type &c_type,
           const cube_type &p_type,
           const unsigned pos,
           const unsigned plane_pos)
noexcept
{
  if (pos == plane_pos)
  { c_type = p_type; }
}
