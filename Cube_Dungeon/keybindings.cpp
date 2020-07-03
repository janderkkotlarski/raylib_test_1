#include "keybindings.h"

#include <raylib.h>

void key_bind_actions(action &act)
noexcept
{
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
  if (IsKeyDown('G'))
  { act = action::inhale; }
  if (IsKeyDown('T'))
  { act = action::exhale; }
}

void gamepad_actions(action &act)
noexcept
{
  if (IsGamepadAvailable(GAMEPAD_PLAYER1))
  {
    if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_UP))
    { act = action::forward; }
    if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_DOWN))
    { act = action::backward; }
    if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))
    { act = action::right; }
    if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_LEFT))
    { act = action::left; }
    if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_TRIGGER_2))
    { act = action::up; }
    if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_TRIGGER_2))
    { act = action::down; }
    if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
    { act = action::rotate_right; }
    if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
    { act = action::rotate_left; }
    if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_UP))
    { act = action::rotate_up; }
    if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
    { act = action::rotate_down; }
    if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_TRIGGER_1))
    { act = action::roll_right; }
    if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_TRIGGER_1))
    { act = action::roll_left; }
    if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_THUMB))
    { act = action::inhale; }
    if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_THUMB))
    { act = action::exhale; }
  }
}
