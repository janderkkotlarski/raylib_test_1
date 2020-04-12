#include "cube_type.h"

raylib::Color type_color(const cube_type ct)
noexcept
{
  raylib::Color color
  { 0, 0, 0 };

  switch (ct)
  {
    case cube_type::none:
      color = raylib::Color{ 0, 0, 0 };
      break;
    case cube_type::concrete:
      color = raylib::Color{ 127, 127, 127 };
      break;
  }

  return color;
}
