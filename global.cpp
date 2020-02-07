#include "global.h"

Arduboy2 arduboy;
Sprites sprites;
ArduboyTones sound(arduboy.audio.enabled);

int gameState = GAME_STATE_TITLE;
unsigned long int score = 0;
WeaponManager* weapons;
Gem* previewGems[PREVIEW_GEMS_MAX];
Gem* fallingGems[FALLING_GEMS_MAX];
Enemy* enemy;
