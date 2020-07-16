#include "cube_type.h"

#include <cassert>
#include <math.h>

#include "misc_functions.h"

unsigned type2index(const cube_type c_type)
/// Assign an index number to a cube type.
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
/// Assign cube type to an index number.
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
/// Determine when a collision takes place.
{
  if (c_type == cube_type::concrete ||
      c_type == cube_type::alabaster ||
      c_type == cube_type::invisible ||
      c_type == cube_type::transparent ||
      c_type == cube_type::catalyst ||
      c_type == cube_type::trigger ||
      c_type == cube_type::miscellaneous)
  { return true; }

  return false;
}

bool type2profile(const cube_type c_type,
                  std::vector <float> &profile)
noexcept
/// Determine the color profile for the given cube type.
{
  if (profile.size() == 4)
  {
    switch (c_type)
    {
      case cube_type::concrete:
        profile = std::vector <float>{0.25f, 0.25f, 0.25f, 1.0f };
        return true;
        break;
      case cube_type::alabaster:
        profile = std::vector <float>{1.0f, 1.0f, 1.0f, 1.0f };
        return true;
        break;
      case cube_type::previous:
        profile = std::vector <float>{0.25f, 0.0f, 0.5f, 1.0f };
        return true;
        break;
      case cube_type::catalyst:
        profile = std::vector <float>{0.5f, 1.0f, 0.75f, 1.0f };
        return true;
        break;
      case cube_type::trigger:
        profile = std::vector <float>{1.0f, 0.75f, 0.5f, 1.0f };
        return true;
        break;
      case cube_type::miscellaneous:
        profile = std::vector <float>{0.5f, 0.25f, 0.0f, 1.0f };
        return true;
        break;
    }
  }

  return false;
}

bool type2proflex (const cube_type c_type,
                   std::vector <float> &profile,
                   const std::vector <float> &spectral_profile,
                   const std::vector <float> &chromatic_profile,
                   const float candy_factor)
noexcept
/// Determine bthe varying color profile for a given cube type.
{
  if (profile.size() == 4)
  {
    const float candy_scale
    { 0.5f - 0.5f*cos(0.5f*PI*candy_factor) };

    switch (c_type)
    {
      case cube_type::next:
        profile = spectral_profile;
        return true;
        break;
      case cube_type::special:
        profile = chromatic_profile;
        return true;
        break;
      case cube_type::ruby:
        profile = std::vector <float>{candy_scale, 0.0f, 0.0f, 1.0f };
        return true;
        break;
      case cube_type::citrine:
        profile = std::vector <float>{candy_scale, candy_scale, 0.0f, 1.0f };
        return true;
        break;
      case cube_type::emerald:
        profile = std::vector <float>{0.0f, candy_scale, 0.0f, 1.0f };
        return true;
        break;
      case cube_type::sapphire:
        profile = std::vector <float>{0.0f, 0.0f, candy_scale, 1.0f };
        return true;
        break;
    }
  }

  return false;
}

void scale_profile(std::vector <float> &profile,
                   const float scale)
noexcept
/// Multiply each color part by the given scalar.
{
  for (float &part: profile)
  { part *= scale; }

  profile[3] = 1.0f;
}

bool transit(const cube_type transit_type)
noexcept
/// Determine whether a transition scene is needed.
{
  if (transit_type == cube_type::next ||
      transit_type == cube_type::setback)
  { return true; }

  return false;
}

std::string type2string(const cube_type c_type)
noexcept
{
  switch (c_type)
  {
    case cube_type::none:
      return "none";
      break;
    case cube_type::concrete:
      return "concrete";
      break;
    case cube_type::alabaster:
      return "alabaster";
      break;
    case cube_type::invisible:
      return "invisible";
      break;
    case cube_type::transparent:
      return "transparent";
      break;
    case cube_type::next:
      return "next";
      break;
    case cube_type::special:
      return "special";
      break;
    case cube_type::previous:
      return "previous";
      break;
    case cube_type::setback:
      return "setback";
      break;
    case cube_type::catalyst:
      return "catalyst";
      break;
    case cube_type::trigger:
      return "trigger";
      break;
    case cube_type::miscellaneous:
      return "miscellaneous";
      break;
    case cube_type::ruby:
      return "ruby";
      break;
    case cube_type::citrine:
      return "citrine";
      break;
    case cube_type::emerald:
      return "emerald";
      break;
    case cube_type::sapphire:
      return "sapphire";
      break;
  }

  return "none";
}
