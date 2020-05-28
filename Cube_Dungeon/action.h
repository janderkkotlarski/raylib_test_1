#ifndef ACTION_H
#define ACTION_H

#include <vector>

enum class action
{
  none,
  forward,
  backward,
  right,
  left,
  up,
  down,
  rotate_right,
  rotate_left,
  rotate_up,
  rotate_down,
  roll_right,
  roll_left,
  inhale,
  exhale,
  catalyze
};

action direct2action(const std::vector <std::vector <int>> &directs,
                     const std::vector <int> &direct)
noexcept;

#endif // ACTION_H
