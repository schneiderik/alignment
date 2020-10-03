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

#define WEAPON_PREVIEW_GEM_X 91
#define WEAPON_GEMS_X 16

#define WEAPON_GEM_Y 0

#define WEAPON_FALLING_GEM_X_INCREMENT -3
#define WEAPON_FALLING_GEM_INTERVAL 8

void Weapon::init(uint8_t type_)
{
  type = type_;
}

void Weapon::dropPreviewGem()
{
  if (previewGem >= 0 && fallingGem == -1)
  {
    fallingGem = previewGem;
    previewGem = -1;
    fallingGemX = WEAPON_PREVIEW_GEM_X;
  }
}

void Weapon::queuePreviewGem()
{
  previewGem = random(0, GEM_TYPE_COUNT);
}

void Weapon::stackGem(uint8_t gem)
{
  gems[gemCount] = gem;
  gemCount++;
}

void Weapon::update()
{
  if (fallingGem != -1)
  {
    if (arduboy.everyXFrames(WEAPON_FALLING_GEM_INTERVAL))
    {
      fallingGemX += WEAPON_FALLING_GEM_X_INCREMENT;
    }

    if (fallingGemX <= WEAPON_GEMS_X + (gemCount * gemSpritePlusMask[0]))
    {
      stackGem(fallingGem);
      fallingGem = -1;
    }
  }
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
      y + WEAPON_GEM_Y,
      gemSpritePlusMask,
      previewGem
    );  
  }

  if (fallingGem >= 0) {
    sprites.drawPlusMask(
      x + fallingGemX,
      y + WEAPON_GEM_Y,
      gemSpritePlusMask,
      fallingGem
    );  
  }

  for (uint8_t i = 0; i < gemCount; i++)
  {
    sprites.drawPlusMask(
      x + WEAPON_GEMS_X + (gemSpritePlusMask[0] * i),
      y + WEAPON_GEM_Y,
      gemSpritePlusMask,
      gems[i]
    );  
  }
}
