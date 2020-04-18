#include "keybindings.h"

#include <raylib.h>

action key_bind_actions()
noexcept
{
  action act
  { action::none };

  if (IsKeyDown('W'))
  { act = action::forward; }
  if (IsKeyDown('S'))
  { act = action::backward; }
  if (IsKeyDown('D'))
  { act = action::right; }
  if (IsKeyDown('A'))
  { act = action::left; }
  if (IsKeyDown('E'))
  { act = action::up; }
  if (IsKeyDown('Q'))
  { act = action::down; }
  if (IsKeyDown('L'))
  { act = action::rotate_right; }
  if (IsKeyDown('J'))
  { act = action::rotate_left; }
  if (IsKeyDown('I'))
  { act = action::rotate_up; }
  if (IsKeyDown('K'))
  { act = action::rotate_down; }
  if (IsKeyDown('O'))
  { act = action::roll_right; }
  if (IsKeyDown('U'))
  { act = action::roll_left; }

  return act;
}
