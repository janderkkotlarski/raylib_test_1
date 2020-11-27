#include "transitions.h"

void transit_next_level()
noexcept
{
  m_screen_opacity = 0.0f;

  if (transit(m_collide_type))
  {
    m_screen_opacity = m_time/m_period;

    Color screen_color
    { profile2color(m_chromatic_profile) };

    scale_color(screen_color, m_light_intensity);
    scale_color(screen_color, 1.5f);

    change_opacity(screen_color, 4.0f*m_screen_opacity);

    for (int count{ 0 }; count < 3; ++count)
    { DrawRectangle(0, 0, m_screen_width, m_screen_height, screen_color); }
  }

  candy_blink(m_candy_factor, m_delta_time, m_candy_up);

  dark_shift(m_cube_vein_profile, m_delta_time, m_dark_opacity, m_dark_up);
}

// tests

void test_transit_next_level()
noexcept
{
  transit_next_level();
}

