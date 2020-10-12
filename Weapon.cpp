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

#define WEAPON_CLEARING_GEM_DATA_X 0
#define WEAPON_CLEARING_GEM_DATA_Y 1
#define WEAPON_CLEARING_GEM_DATA_VEL_X 2
#define WEAPON_CLEARING_GEM_DATA_VEL_Y 3

#define WEAPON_CLEARING_GEM_INTERVAL 4

void Weapon::init(uint8_t type_)
{
  type = type_;
}

void Weapon::dropPreviewGem()
{
  if (hasPreviewGem() && !hasFallingGem())
  {
    setFallingGem(previewGem);
    clearPreviewGem();
  }
}

void Weapon::queuePreviewGem()
{
  previewGem = random(0, GEM_TYPE_COUNT);
}

void Weapon::stackGem(uint8_t gem)
{
  if (isFull()) return;

  gems[gemCount] = gem;
  gemCount++;
}

void Weapon::update()
{
  if (hasFallingGem())
  {
    if (arduboy.everyXFrames(WEAPON_FALLING_GEM_INTERVAL))
    {
      fallingGemX += WEAPON_FALLING_GEM_X_INCREMENT;
    }

    if (fallingGemX < getEndOfStackX())
    {
      stackGem(fallingGem);
      clearFallingGem();
    }
  }

  if (isClearing())
  {
    if (arduboy.everyXFrames(WEAPON_CLEARING_GEM_INTERVAL))
    {
      updateClearingGems();
    }
  }
  else if (isFull())
  {
    clearStack();
  }
}

void Weapon::updateClearingGems()
{
  clearingGemCount = WEAPON_GEMS_MAX;

  arduboy.setCursor(48, 0);
  arduboy.print(gemCount);
  arduboy.print(clearingGemData[0][WEAPON_CLEARING_GEM_DATA_Y]);
  arduboy.print(clearingGemCount);

  for (uint8_t i = 0; i < WEAPON_GEMS_MAX; i++)
  {
    if (clearingGemData[i][WEAPON_CLEARING_GEM_DATA_Y] < SCREEN_HEIGHT)
    {
      clearingGemData[i][WEAPON_CLEARING_GEM_DATA_X] += clearingGemData[i][WEAPON_CLEARING_GEM_DATA_VEL_X];
      clearingGemData[i][WEAPON_CLEARING_GEM_DATA_Y] += clearingGemData[i][WEAPON_CLEARING_GEM_DATA_VEL_Y];
      clearingGemData[i][WEAPON_CLEARING_GEM_DATA_VEL_Y] += GRAVITY;
    }
    else
    {
      clearingGemCount--;
    }
  }

  if (clearingGemCount == 0) {
    gemCount = 0;
  }
}

void Weapon::clearStack()
{
  clearingGemCount = WEAPON_GEMS_MAX;

  for (uint8_t i = 0; i < WEAPON_GEMS_MAX; i++)
  {
    clearingGemData[i][WEAPON_CLEARING_GEM_DATA_X] = getGemX(i);
    clearingGemData[i][WEAPON_CLEARING_GEM_DATA_Y] = WEAPON_GEM_Y;
    clearingGemData[i][WEAPON_CLEARING_GEM_DATA_VEL_X] = random(0, 3) - 1;
    clearingGemData[i][WEAPON_CLEARING_GEM_DATA_VEL_Y] = random(0, 3) - 2;
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

  if (hasPreviewGem()) {
    sprites.drawPlusMask(
      x + WEAPON_PREVIEW_GEM_X,
      y + WEAPON_GEM_Y,
      gemSpritePlusMask,
      previewGem
    );  
  }

  if (hasFallingGem()) {
    sprites.drawPlusMask(
      x + fallingGemX,
      y + WEAPON_GEM_Y,
      gemSpritePlusMask,
      fallingGem
    );  
  }

  for (uint8_t i = 0; i < gemCount; i++)
  {
    if (isClearing())
    {
      sprites.drawPlusMask(
        x + clearingGemData[i][WEAPON_CLEARING_GEM_DATA_X],
        y + clearingGemData[i][WEAPON_CLEARING_GEM_DATA_Y],
        gemSpritePlusMask,
        gems[i]
      );  
    }
    else
    {
      sprites.drawPlusMask(
        x + WEAPON_GEMS_X + (gemSpritePlusMask[0] * i),
        y + WEAPON_GEM_Y,
        gemSpritePlusMask,
        gems[i]
      );  
    }
  }
}

void Weapon::clearPreviewGem()
{
  previewGem = -1;
}

void Weapon::clearFallingGem()
{
  fallingGem = -1;
}

void Weapon::setFallingGem(uint8_t type)
{
  fallingGem = type;
  fallingGemX = WEAPON_PREVIEW_GEM_X;
}

bool Weapon::hasPreviewGem()
{
  return previewGem != -1;
}

bool Weapon::hasFallingGem()
{
  return fallingGem != -1;
}

bool Weapon::isClearing()
{
  return clearingGemCount > 0;
}

bool Weapon::isFull()
{
  return gemCount == WEAPON_GEMS_MAX;
}

bool Weapon::fallingGemIsAboveX(int x)
{
  return hasFallingGem() && fallingGemX >= x;
}

int Weapon::getGemX(uint8_t i)
{
  return WEAPON_GEMS_X + (i * gemSpritePlusMask[0]);
}

int Weapon::getEndOfStackX()
{
  return getGemX(gemCount);
}
