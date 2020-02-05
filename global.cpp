#include "global.h"

Arduboy2 arduboy;
Sprites sprites;
ArduboyTones sound(arduboy.audio.enabled);

Gem* tmpGem;
Weapon* tmpWeapon;
Weapon* weapons[WEAPON_COUNT];
Gem* weaponGems[WEAPON_COUNT][WEAPON_GEMS_MAX];
Gem* previewGems[PREVIEW_GEMS_MAX];
Gem* fallingGems[FALLING_GEMS_MAX];
Gem* clearingGems[CLEARING_GEMS_MAX];
