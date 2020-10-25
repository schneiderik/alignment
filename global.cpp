#include "global.h"

Arduboy2 arduboy;
Sprites sprites;
ArduboyTones sound(arduboy.audio.enabled);

void noop() {};

void swapValues(int& a, int& b)
{
  int tmp = a;
  a = b;
  b = tmp;
}

void swapValues(bool& a, bool& b)
{
  bool tmp = a;
  a = b;
  b = tmp;
}
