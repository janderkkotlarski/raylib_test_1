#ifndef DUNGEON_FUNCTIONS_H
#define DUNGEON_FUNCTIONS_H

#include <vector>
#include <random>

#include "cube_type.h"

void dungeon_init(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
                  const int max_dungeon_radius)
noexcept;

void dungeon_filler(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
                    const int level,
                    const int dungeon_radius)
noexcept;

void level_filler(cube_type &c_type,
                  const int level,
                  const int dungeon_radius,
                  const int x,
                  const int y,
                  const int z)
noexcept;

void outer_wall(cube_type &c_type,
                const cube_type w_type,
                const int dungeon_radius,
                const int x,
                const int y,
                const int z)
noexcept;

void pillars(cube_type &c_type,
             const cube_type w_type,
             const int dungeon_radius,
             const int x,
             const int y,
             const int z)
noexcept;

void random_wall(cube_type &c_type,
                 const int level,
                 const int dungeon_radius,
                 const int x,
                 const int y,
                 const int z)
noexcept;

cube_type wall_type(const int level)
noexcept;

int wall_percentage(const cube_type c_type,
                    const int level)
noexcept;

void single_placements(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
                       const int level,
                       const int dungeon_radius)
noexcept;

void plus_3d(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const cube_type &c_type,
             const int x,
             const int y,
             const int z)
noexcept;

void block_of_cubes(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
                   const cube_type &c_type,
                   const unsigned x1, const unsigned x2,
                   const unsigned y1, const unsigned y2,
                   const unsigned z1, const unsigned z2)
noexcept;

void plane(cube_type &c_type,
           const cube_type &p_type,
           const unsigned pos,
           const unsigned plane_pos)
noexcept;

#endif // DUNGEON_FUNCTIONS_H
