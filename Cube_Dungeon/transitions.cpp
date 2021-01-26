#include "transitions.h"

#include <vector>

#include "raylib_functions.h"

void transit_next_level(const cube_type collide_type, const float time, const float period,
                        const std::vector <float> &chromatic_profile, const float light_intensity,
                        const int screen_width, const int screen_height)
noexcept
{
  float screen_opacity
  { 0.0f };

  if (transit(collide_type))
  {
    screen_opacity = time/period;

    Color screen_color
    { profile2color(chromatic_profile) };

    scale_color(screen_color, light_intensity);
    scale_color(screen_color, 1.5f);

    change_opacity(screen_color, 4.0f*screen_opacity);

    for (int count{ 0 }; count < 3; ++count)
    { DrawRectangle(0, 0, screen_width, screen_height, screen_color); }
  }  
}

// tests

void test_transit_next_level()
noexcept
{
  // transit_next_level();
}

