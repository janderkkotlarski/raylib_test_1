#include "cube_type.h"

#include "misc_functions.h"

unsigned type2index(const cube_type c_type)
{
  switch (c_type)
  {
    case cube_type::none:
      return 0;
      break;
    case cube_type::concrete:
      return 1;
      break;
    case cube_type::alabaster:
      return 2;
      break;
    case cube_type::invisible:
      return 3;
      break;
    case cube_type::transparent:
      return 4;
      break;
    case cube_type::next:
      return 5;
      break;
    case cube_type::special:
      return 6;
      break;
    case cube_type::previous:
      return 7;
      break;
    case cube_type::setback:
      return 8;
      break;
    case cube_type::catalyst:
      return 9;
      break;
    case cube_type::trigger:
      return 10;
      break;
    case cube_type::miscellaneous:
      return 11;
      break;
    case cube_type::ruby:
      return 12;
      break;
    case cube_type::citrine:
      return 13;
      break;
    case cube_type::emerald:
      return 14;
      break;
    case cube_type::sapphire:
      return 15;
      break;
  }

  return 0;
}

bool type_collision(const cube_type c_type)
noexcept
{
  if (c_type == cube_type::concrete ||
      c_type == cube_type::alabaster ||
      c_type == cube_type::invisible ||
      c_type == cube_type::transparent)
  { return true; }

  return false;
}

Color type_color(const cube_type c_type,
                 const Vector3 &spectral_profile)
noexcept
{
  Color color
  { 0, 0, 0, 255 };

  switch (c_type)
  {
    case cube_type::none:
      color = Color{ 0, 0, 0, 255 };
      break;
    case cube_type::concrete:
      color = Color{ 63, 63, 63, 255 };
      break;
    case cube_type::alabaster:
      color = Color{ 255, 255, 255, 255 };
      break;
    case cube_type::invisible:
      color = Color{ 0, 0, 0, 0 };
      break;
    case cube_type::transparent:
      color = Color{ 0, 0, 0, 0 };
      break;
    case cube_type::next:
      color = profile2color(spectral_profile);
      break;
    case cube_type::special:
      color = Color{ 127, 255, 255, 255 };
      break;
    case cube_type::previous:
      color = Color{ 127, 0, 255, 255 };
      break;
    case cube_type::setback:
      color = Color{ 0, 0, 0, 23 };
      break;
    case cube_type::catalyst:
      color = Color{ 127, 255, 191, 255 };
      break;
    case cube_type::trigger:
      color = Color{ 255, 191, 127, 255 };
      break;
    case cube_type::miscellaneous:
      color = Color{ 255, 191, 127, 255 };
      break;
    case cube_type::ruby:
      color = Color{ 255, 0, 0, 255 };
      break;
    case cube_type::citrine:
      color = Color{ 255, 255, 0, 255 };
      break;
    case cube_type::emerald:
      color = Color{ 0, 255, 0, 255 };
      break;
    case cube_type::sapphire:
      color = Color{ 0, 0, 255, 255 };
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
