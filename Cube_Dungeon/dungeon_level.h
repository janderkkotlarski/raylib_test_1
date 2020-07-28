#ifndef DUNGEON_LEVEL_H
#define DUNGEON_LEVEL_H

#include <vector>

#include "cube_type.h"

void levels(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
            const int level, int &radius,
            std::vector <int> &start_posint)
noexcept;

void level_1(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius,
             std::vector <int> &start_posint)
noexcept;

void level_2(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept;

void level_3(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept;

void level_4(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept;

void level_5(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept;

void level_6(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept;

void demo_1(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
            const int level, int &radius, std::vector<int> &start_posint)
noexcept;

#endif // DUNGEON_LEVEL_H
