#ifndef CUBE_TYPE_H
#define CUBE_TYPE_H

#include <raylib.h>

enum class cube_type
{
  none,
  // absorbable, empty
  // black

  player,
  // player
  // parts in color sync with all "next" squares

  trigger,
  // absorbable, inedible
  // presence or nonpresence will change certain other squares
  // orange

  special,
  // absorbable, edible, +500 points
  // portal to a special level
  // repeatedly spectrally rotating from blue to red

  invisible,
  // inabsorbable, inedible
  // brick
  // black

  transparent,
  // absorbable, inedible
  // brick
  // black

  concrete,
  // inabsorbable, inedible
  // brick
  // grey

  alabaster,
  // absorbable, inedible
  // brick
  // white

  catalyst,
  // absorbable, inedible
  // reacts with certain other squares
  // teal

  next,
  // absorbable, edible, +100 points
  // portal to next level
  // repeatedly rotating from red to blue

  previous,
  // absorbable, edible, -50 points
  // portal to previous level
  // purple

  setback,
  // absorbable, edible, -25 points
  // transports back to the start
  // superdark

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

bool type_collision(const cube_type ct)
noexcept;

Color type_color(const cube_type ct,
                 const Vector3 &spectral_profile)
noexcept;

bool transit(const cube_type &transit_type)
noexcept;

#endif // CUBE_TYPE_H
