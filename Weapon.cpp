#include "Weapon.h"

#define WEAPON_ACTIVE_INDICATOR_X 0
#define WEAPON_ACTIVE_INDICATOR_Y 0
#define WEAPON_ACTIVE_INDICATOR_WIDTH 12
#define WEAPON_ACTIVE_INDICATOR_HEIGHT 12

#define WEAPON_ICON_X 2
#define WEAPON_ICON_Y 2

#define WEAPON_DIVIDER_X 14
#define WEAPON_DIVIDER_Y 1
#define WEAPON_DIVIDER_WIDTH 1
#define WEAPON_DIVIDER_HEIGHT 10

#define WEAPON_PREVIEW_DIVIDER_X 89
#define WEAPON_PREVIEW_DIVIDER_Y 0
#define WEAPON_PREVIEW_DIVIDER_WIDTH 1
#define WEAPON_PREVIEW_DIVIDER_HEIGHT 14

#define WEAPON_PREVIEW_GEM_X 92
#define WEAPON_PREVIEW_GEM_Y 1

void Weapon::init(uint8_t type_)
{
  type = type_;
}

void Weapon::render(uint8_t x, uint8_t y, bool active)
{
  arduboy.fillRect(
    x + WEAPON_DIVIDER_X,
    y + WEAPON_DIVIDER_Y,
    WEAPON_DIVIDER_WIDTH,
    WEAPON_DIVIDER_HEIGHT
  );

  if (active)
  {
    arduboy.fillRect(
      x + WEAPON_ACTIVE_INDICATOR_X,
      y + WEAPON_ACTIVE_INDICATOR_Y,
      WEAPON_ACTIVE_INDICATOR_WIDTH,
      WEAPON_ACTIVE_INDICATOR_HEIGHT
    ); 

    sprites.drawErase(
      x + WEAPON_ICON_X,
      y + WEAPON_ICON_Y,
      weaponSprite,
      type
    );  
  }
  else
  {
    sprites.drawOverwrite(
      x + WEAPON_ICON_X,
      y + WEAPON_ICON_Y,
      weaponSprite,
      type
    );  
  }  

  arduboy.fillRect(
    x + WEAPON_PREVIEW_DIVIDER_X,
    y + WEAPON_PREVIEW_DIVIDER_Y,
    WEAPON_PREVIEW_DIVIDER_WIDTH,
    WEAPON_PREVIEW_DIVIDER_HEIGHT,
    WHITE
  );

  if (previewGem >= 0) {
    sprites.drawPlusMask(
      x + WEAPON_PREVIEW_GEM_X,
      y + WEAPON_PREVIEW_GEM_Y,
      gemSpritePlusMask,
      previewGem
    );  
  }
}
