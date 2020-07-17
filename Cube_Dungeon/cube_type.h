#ifndef CUBE_TYPE_H
#define CUBE_TYPE_H

#include <vector>
#include <string>

#include <raylib.h>

enum class cube_type
/// Cube types that may be encountered in the levels.
{
  none,
  // Empty, not visible, not absorbable, not halable
  // Transparent

  concrete,
  // Wall, visible, not absorbable, not halable
  // Grey

  alabaster,
  // Wall, visible, not absorbable, halable
  // White

  invisible,
  // Wall, not visible, not absorbable, not halable
  // Transparent

  transparent,
  // Wall, not visible, not absorbable, halable
  // Transparent

  next,
  // Exit, visible, absorbable, halable
  // Spectral progression

  special,
  // Exit, visible, absorbable, halable
  // Chromatic progression

  previous,
  // Exit, visible, absorbable, halable
  // Dark purple

  setback,
  // Transporter, barely visible, absorbable, halable
  // Very dark nearly fully transparent

  catalyst,
  // Tool, visible, absorbable, halable
  // Turquoise

  trigger,
  // Tool, visible, absorbable, halable
  // Orange

  miscellaneous,
  // Any other type, (not) visible,(not) absorbable, (not) halable
  // Any color

  ruby,
  // Point, visible, absorbable, halable
  // Red

  citrine,
  // Point, visible, absorbable, halable
  // Yellow

  emerald,
  // Point, visible, absorbable, halable
  // Green

  sapphire
  // Point, visible, absorbable, halable
  // Blue
};

unsigned type2index(const cube_type c_type)
noexcept;

cube_type index2type(const unsigned index)
noexcept;

bool type_collision(const cube_type c_type)
noexcept;

bool type2profile(const cube_type c_type,
                  std::vector <float> &profile)
noexcept;

bool type2proflex (const cube_type c_type,
                   std::vector <float> &profile,
                   const std::vector <float> &spectral_profile,
                   const std::vector <float> &chromatic_profile,
                   const float candy_factor)
noexcept;

void scale_profile(std::vector <float> &profile,
                   const float scale)
noexcept;

bool transit(const cube_type transit_type)
noexcept;

std::string type2string(const cube_type c_type)
noexcept;

#endif // CUBE_TYPE_H
