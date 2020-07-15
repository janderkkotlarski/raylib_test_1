#ifndef DUNGEON_LEVEL_H
#define DUNGEON_LEVEL_H

#include <vector>

#include "cube_type.h"

void level_1(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius,
             std::vector <int> &start_posint)
noexcept;

#endif // DUNGEON_LEVEL_H
