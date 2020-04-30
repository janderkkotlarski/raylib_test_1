#ifndef DUNGEON_FUNCTIONS_H
#define DUNGEON_FUNCTIONS_H

#include <vector>
#include <random>

#include "cube_type.h"

void dungeon_filler(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
                    const int level,
                    const int dungeon_radius)
noexcept;

cube_type level_filler(const int level,
                       const int dungeon_radius,
                       const int x,
                       const int y,
                      const int z)
noexcept;

cube_type wall_to_wall_dungeon(const int level,
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

#endif // DUNGEON_FUNCTIONS_H
