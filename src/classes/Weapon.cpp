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

#define WEAPON_CLEARING_GEM_DATA_X 0
#define WEAPON_CLEARING_GEM_DATA_Y 1
#define WEAPON_CLEARING_GEM_DATA_VEL_X 2
#define WEAPON_CLEARING_GEM_DATA_VEL_Y 3

#define WEAPON_CLEARING_GEM_INTERVAL 4

void Weapon::init(
  uint8_t type_,
  void (*onGemStack_)(),
  void (*onClear_)(),
  void (*onCleared_)(),
  void (*onMatch_)()
)
{
  type = type_;
  onGemStack = onGemStack_;
  onClear = onClear_;
  onCleared = onCleared_;
  onMatch = onMatch_;
  gemCount = 0;
  clearingGemCount = 0;
  clearPreviewGem();
  clearFallingGem();
}

void Weapon::dropPreviewGem()
{
  if (hasPreviewGem && !hasFallingGem)
  {
    setFallingGem(previewGem.type);
    clearPreviewGem();
  }
}

void Weapon::queuePreviewGem()
{
  previewGem.type = random(0, GEM_TYPE_COUNT);
  hasPreviewGem = true;
}

void Weapon::stackGem(uint8_t gem)
{
  if (isFull()) return;

  gems[gemCount].init(gem);
  gemCount++;
}

void Weapon::update(int fallSpeed)
{
  if (hasMatch())
  {
    onMatch();
    gemCount -= 2;
  }

  if (hasFallingGem)
  {
    if (arduboy.everyXFrames(fallSpeed))
    {
      fallingGem.x += WEAPON_FALLING_GEM_X_INCREMENT;
    }

    if (fallingGem.x < getEndOfStackX())
    {
      stackGem(fallingGem.type);
      onGemStack();
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
    onClear();
  }
}

bool Weapon::hasMatch()
{
  if (gemCount <= 1) return false;

  if (gems[gemCount - 1].type == gems[gemCount - 2].type) return true;
}

void Weapon::updateClearingGems()
{
  clearingGemCount = WEAPON_GEMS_MAX;

  for (uint8_t i = 0; i < WEAPON_GEMS_MAX; i++)
  {
    if (gems[i].y < SCREEN_HEIGHT)
    {
      gems[i].x += gems[i].velX;
      gems[i].y += gems[i].velY;
      gems[i].velY += GRAVITY;
    }
    else
    {
      clearingGemCount--;
    }
  }

  if (clearingGemCount == 0) {
    gemCount = 0;
    onCleared();
  }
}

void Weapon::swapGems(Weapon& other)
{
  if (
    fallingGemIsAboveX(other.getEndOfStackX())
    || other.fallingGemIsAboveX(getEndOfStackX())
  )
  {
    swapValues(fallingGem.type, other.fallingGem.type);
    swapValues(fallingGem.x, other.fallingGem.x);
    swapValues(hasFallingGem, other.hasFallingGem);
  }

  swapValues(previewGem.type, other.previewGem.type);
  swapValues(hasPreviewGem, other.hasPreviewGem);
}

void Weapon::clearStack()
{
  clearingGemCount = WEAPON_GEMS_MAX;

  for (uint8_t i = 0; i < WEAPON_GEMS_MAX; i++)
  {
    gems[i].reset();
    gems[i].velX = random(0, 3) - 1;
    gems[i].velY = random(0, 3) - 2;
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

  if (hasPreviewGem) {
    sprites.drawPlusMask(
      x + WEAPON_PREVIEW_GEM_X,
      y + WEAPON_GEM_Y,
      gemSpritePlusMask,
      previewGem.type
    );  
  }

  if (hasFallingGem) {
    sprites.drawPlusMask(
      x + fallingGem.x,
      y + WEAPON_GEM_Y,
      gemSpritePlusMask,
      fallingGem.type
    );  
  }

  for (uint8_t i = 0; i < gemCount; i++)
  {
    sprites.drawPlusMask(
      x + gems[i].x + WEAPON_GEMS_X + (gemSpritePlusMask[0] * i),
      y + gems[i].y + WEAPON_GEM_Y,
      gemSpritePlusMask,
      gems[i].type
    );  
  }
}

void Weapon::clearPreviewGem()
{
  hasPreviewGem = false;
}

void Weapon::clearFallingGem()
{
  hasFallingGem = false;
}

void Weapon::setFallingGem(uint8_t type)
{
  fallingGem.type = type;
  fallingGem.x = WEAPON_PREVIEW_GEM_X;
  hasFallingGem = true;
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
  return hasFallingGem && fallingGem.x >= x;
}

int Weapon::getGemX(uint8_t i)
{
  return WEAPON_GEMS_X + (i * gemSpritePlusMask[0]);
}

int Weapon::getEndOfStackX()
{
  return getGemX(gemCount);
}
