#include "cube_type.h"

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
    case cube_type::concrete:
      color = Color{ 127, 127, 127, 255 };
      break;
    case cube_type::next:
      color = Color{ 31, 0, 63, 255 };
      break;
  }

  return color;
}
