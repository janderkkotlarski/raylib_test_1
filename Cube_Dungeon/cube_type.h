#ifndef CUBE_TYPE_H
#define CUBE_TYPE_H

#include <raylib.h>

enum class cube_type
{
  none,
  // absorbable, empty
  // black

  concrete,
  // inabsorbable, inedible
  // brick
  // grey

  alabaster,
  // absorbable, inedible
  // brick
  // white

  invisible,
  // inabsorbable, inedible
  // brick
  // black

  transparent,
  // absorbable, inedible
  // brick
  // black

  next,
  // absorbable, edible, +100 points
  // portal to next level
  // repeatedly rotating from red to blue

  special,
  // absorbable, edible, +500 points
  // portal to a special level
  // repeatedly spectrally rotating from blue to red

  previous,
  // absorbable, edible, -50 points
  // portal to previous level
  // purple

  setback,
  // absorbable, edible, -25 points
  // transports back to the start
  // superdark

  catalyst,
  // absorbable, inedible
  // reacts with certain other squares
  // teal

  trigger,
  // absorbable, inedible
  // presence or nonpresence will change certain other squares
  // orange

  miscellaneous,
  // a type for whatever purpose needed

  ruby,
  // absorbable, edible, +1 point
  // candy
  // red

  citrine,
  // absorbable, edible, +5 points
  // candy
  // yellow

  emerald,
  // absorbable, edible, +25 points
  // candy
  // green

  sapphire
  // absorbable, edible, +125 points
  // candy
  // blue
};

unsigned type2index(const cube_type c_type)
noexcept;

cube_type index2type(const unsigned index)
noexcept;

bool type_collision(const cube_type c_type)
noexcept;

Color type_color(const cube_type c_type,
                 const Vector3 &spectral_profile)
noexcept;

bool transit(const cube_type &transit_type)
noexcept;

#endif // CUBE_TYPE_H
