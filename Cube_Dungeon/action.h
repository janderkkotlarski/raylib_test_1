#ifndef ACTION_H
#define ACTION_H

#include <vector>
#include <string>

enum class action
/// Actions to take when certain consitions are met
/// As longas an action is taken, no other action should be taken
{
  none, // Do nothing
  forward, // Move forward
  backward, // Move backward
  right, // Move right
  left, // Move left
  up, // Move up
  down, // Move down
  rotate_right, // Rotate right
  rotate_left, // Rotate left
  rotate_up, // Rotate up
  rotate_down, // Rotate down
  roll_right, // Barrel roll right
  roll_left, // Barrel roll left
  inhale, // Inhale cube in front
  exhale, // Exhale cube to front
  catalyze // Catalyze ingredients
};

action direct2action(const std::vector <std::vector <int>> &directs,
                     const std::vector <int> &direct)
noexcept;

std::vector <float> action2direction(const std::vector <std::vector <float>> &directs,
                                     const action act)
noexcept;

std::string action2string(const action act)
noexcept;

#endif // ACTION_H
