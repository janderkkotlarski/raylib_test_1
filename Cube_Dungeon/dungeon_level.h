#ifndef DUNGEON_LEVEL_H
#define DUNGEON_LEVEL_H

#include <vector>

#include "cube_type.h"

void next_scanner(const std::vector< std::vector <std::vector <cube_type>>> &type_volume,
                  std::vector <int> &next_pos_int,
                  const int radius)
noexcept;

void level_wipe(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
                const int radius)
noexcept;

void next_side(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
               const int span)
noexcept;

void three_d_life(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
                  const std::vector <int> &pos_int, const int radius)
noexcept;

void levels(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
            const int level, int &radius, std::vector <int> &start_posint)
noexcept;

void level_0(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept;

void level_1(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector <int> &start_posint)
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

void level_7(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept;

void level_8(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept;

void level_9(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept;

void level_10(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
             const int level, int &radius, std::vector<int> &start_posint)
noexcept;



void demo_1(std::vector< std::vector <std::vector <cube_type>>> &type_volume,
            const int level, int &radius, std::vector<int> &start_posint)
noexcept;

#endif // DUNGEON_LEVEL_H
