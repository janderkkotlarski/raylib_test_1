#include "action.h"

#include "misc_functions.h"

action direct2action(const std::vector <std::vector <int>> &directs,
                     const std::vector <int> &direct)
noexcept
{
  if (direct == directs[0])
  { return action::forward; }
  if (direct == negate_int_vector(directs[0]))
  { return action::backward; }

  if (direct == directs[1])
  { return action::right; }
  if (direct == negate_int_vector(directs[1]))
  { return action::left; }

  if (direct == directs[2])
  { return action::up; }
  if (direct == negate_int_vector(directs[2]))
  { return action::down; }

  return action::none;
}
