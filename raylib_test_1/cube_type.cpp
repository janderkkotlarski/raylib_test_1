#include "cube_type.h"

#include "misc_functions.h"

bool type_collision(const cube_type ct)
noexcept
{
  if (ct == cube_type::concrete ||
      ct == cube_type::alabaster ||
      ct == cube_type::invisible)
  { return true; }

  return false;
}

Color type_color(const cube_type ct,
                 const Vector3 &spectral_profile)
noexcept
{
  Color color
  { 0, 0, 0, 255 };

  switch (ct)
  {
    case cube_type::none:
      color = Color{ 0, 0, 0, 255 };
      break;
    case cube_type::alabaster:
      color = Color{ 255, 255, 255, 255 };
      break;
    case cube_type::concrete:
      color = Color{ 63, 63, 63, 255 };
      break;
    case cube_type::invisible:
      color = Color{ 0, 0, 0, 0 };
      break;
    case cube_type::next:
      color = profile2color(spectral_profile);
      break;
    case cube_type::special:
      color = Color{ 127, 255, 255, 255 };
      break;
    case cube_type::trigger:
      color = Color{ 255, 191, 127, 255 };
      break;
    case cube_type::setback:
      color = Color{ 0, 0, 0, 23 };
      break;

  }

  return color;
}

bool transit(const cube_type &transit_type)
noexcept
{
  if (transit_type == cube_type::next ||
      transit_type == cube_type::setback)
  { return true; }

  return false;
}
