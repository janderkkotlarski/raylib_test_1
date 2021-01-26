#ifndef TRANSITIONS_H
#define TRANSITIONS_H

#include <cube_type.h>



void transit_next_level(const cube_type collide_type, const float time, const float period,
                        const std::vector <float> &chromatic_profile, const float light_intensity,
                        const int screen_width, const int screen_height)
noexcept;

// tests



void test_transit_next_level()
noexcept;

#endif // TRANSITIONS_H
