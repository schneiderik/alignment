#include "global.h"

Arduboy2 arduboy;
Sprites sprites;
ArduboyTones sound(arduboy.audio.enabled);

Game* game;
Player* player;
Enemy* enemy;
WeaponManager* weaponManager;
GemManager* gemManager;
