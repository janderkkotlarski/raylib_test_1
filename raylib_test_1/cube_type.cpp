#include "cube_type.h"

bool type_collision(const cube_type ct)
noexcept
{
  if (ct == cube_type::concrete ||
      ct == cube_type::alabaster)
  { return true; }

  return false;
}

Color type_color(const cube_type ct)
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
      color = Color{ 127, 127, 127, 255 };
      break;
    case cube_type::next:
      color = Color{ 31, 0, 63, 255 };
      break;
    case cube_type::special:
      color = Color{ 127, 255, 255, 255 };
      break;
    case cube_type::trigger:
      color = Color{ 255, 191, 127, 255 };
      break;

  }

  return color;
}
