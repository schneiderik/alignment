#include "global.h"

Arduboy2 arduboy;
Sprites sprites;
ArduboyTones sound(arduboy.audio.enabled);

Game* game;
WeaponManager* weapons;
Enemy* enemy;
