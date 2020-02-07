#include "global.h"

Arduboy2 arduboy;
Sprites sprites;
ArduboyTones sound(arduboy.audio.enabled);

Game* game;
unsigned long int score = 0;
WeaponManager* weapons;
Enemy* enemy;
