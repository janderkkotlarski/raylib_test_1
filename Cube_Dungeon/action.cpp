#include "action.h"

#include "misc_functions.h"

action direct2action(const std::vector <std::vector <int>> &directs,
                     const std::vector <int> &direct)
noexcept
/// Assign an movement action to a certain direction
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

std::vector <float> action2direction(const std::vector <std::vector <float>> &directs,
                                     const action &act)
noexcept
/// Assign a direction to a certain movement action
{
  if (act == action::forward)
  { return directs[0]; }
  if (act == action::backward)
  { return vector_negate(directs[0]); }

  if (act == action::right)
  { return directs[1]; }
  if (act == action::left)
  { return vector_negate(directs[1]); }

  if (act == action::up)
  { return directs[2]; }
  if (act == action::down)
  { return vector_negate(directs[2]); }

  return {0.0f, 0.0f, 0.0f};
}
