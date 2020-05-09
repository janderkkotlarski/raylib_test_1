#include "cube_type.h"

#include "misc_functions.h"

unsigned type2index(const cube_type c_type)
noexcept
{
  switch (c_type)
  {
    case cube_type::concrete:
      return 0;
      break;
    case cube_type::alabaster:
      return 1;
      break;
    case cube_type::next:
      return 2;
      break;
    case cube_type::special:
      return 3;
      break;
    case cube_type::previous:
      return 4;
      break;
    case cube_type::catalyst:
      return 5;
      break;
    case cube_type::trigger:
      return 6;
      break;
    case cube_type::miscellaneous:
      return 7;
      break;
    case cube_type::ruby:
      return 8;
      break;
    case cube_type::citrine:
      return 9;
      break;
    case cube_type::emerald:
      return 10;
      break;
    case cube_type::sapphire:
      return 11;
      break;
  }

  return 42;
}

cube_type index2type(const unsigned index)
noexcept
{
  switch (index)
  {
    case 0:
      return cube_type::concrete;
      break;
    case 1:
      return cube_type::alabaster;
      break;
    case 2:
      return cube_type::next;
      break;
    case 3:
      return cube_type::special;
      break;
    case 4:
      return cube_type::previous;
      break;
    case 5:
      return cube_type::catalyst;
      break;
    case 6:
      return cube_type::trigger;
      break;
    case 7:
      return cube_type::miscellaneous;
      break;
    case 8:
      return cube_type::ruby;
      break;
    case 9:
      return cube_type::citrine;
      break;
    case 10:
      return cube_type::emerald;
      break;
    case 11:
      return cube_type::sapphire;
      break;
  }

  return cube_type::none;
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
                 const std::vector <float> &spectral_profile,
                 const std::vector <float> &chromatic_profile)
noexcept
{
  Color color
  { 0, 0, 0, 255 };

  switch (c_type)
  {
    case cube_type::none:
      color = Color{ 0, 0, 0, 0 };
      break;
    case cube_type::concrete:
      color = Color{ 127, 127, 127, 255 };
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
      color = profile2color(chromatic_profile);
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
