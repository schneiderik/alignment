#include "global.h"

Arduboy2 arduboy;
Sprites sprites;
ArduboyTones sound(arduboy.audio.enabled);

int weapons[WEAPON_COUNT][WEAPON_DATA_LENGTH] = {
  {0, weaponYOffsets[0], 0},
  {1, weaponYOffsets[1], 0},
  {2, weaponYOffsets[2], 0},
  {3, weaponYOffsets[3], 0}
};
