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

#define WEAPON_ALIGN_INCREMENT 2

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
  hasPreviewGem = false;
  hasFallingGem = false;
}

void Weapon::dropPreviewGem()
{
  if (!hasPreviewGem || hasFallingGem) return;

  fallingGem.init(previewGem.type);
  hasFallingGem = true;
  hasPreviewGem = false;
}

void Weapon::queuePreviewGem()
{
  if (hasPreviewGem) return;

  previewGem.init(random(0, GEM_TYPE_COUNT));
  hasPreviewGem = true;
}

void Weapon::stackGem(uint8_t gemType)
{
  if (isFull()) return;

  gems[gemCount].init(gemType);
  hasFallingGem = false;
  gemCount++;
  onGemStack();
}

bool Weapon::hasMatch()
{
  if (gemCount <= 1) return false;

  return gems[gemCount - 1].type == gems[gemCount - 2].type;
}

void Weapon::handleMatch()
{
  gemCount -= 2;
  onMatch();
}

void Weapon::update(int fallSpeed)
{
  if (isClearing()) 
  {
    if (arduboy.everyXFrames(WEAPON_CLEARING_GEM_INTERVAL)) updateClearingGems();
    return;
  }

  if (hasMatch()) handleMatch();
  if (isFull()) clearStack();
  if (!isAligned()) align();

  if (hasFallingGem)
  {
    if (arduboy.everyXFrames(fallSpeed)) fallingGem.fall();
    if (!fallingGem.isAligned()) fallingGem.align();
    if (!fallingGemIsAboveX(getEndOfStackX())) stackGem(fallingGem.type);
  }
}

void Weapon::updateClearingGems()
{
  clearingGemCount = WEAPON_GEMS_MAX;

  for (uint8_t i = 0; i < WEAPON_GEMS_MAX; i++)
  {
    if (gems[i].isCleared())
    {
      gems[i].clear();
    }
    else
    {
      clearingGemCount--;
    }
  }

  if (!isClearing()) {
    gemCount = 0;
    onCleared();
  }
}

void Weapon::swap(Weapon& other, int y)
{
  if (
    fallingGemIsAboveX(other.getEndOfStackX())
    || other.fallingGemIsAboveX(getEndOfStackX())
  )
  {
    fallingGem.swap(other.fallingGem);
    swapValues(hasFallingGem, other.hasFallingGem);
  }
  else {
    fallingGem.yOffset = y;
    other.fallingGem.yOffset = -y;
  }

  yOffset = y;
  other.yOffset = -y;

  previewGem.swap(other.previewGem);
  swapValues(hasPreviewGem, other.hasPreviewGem);
}

void Weapon::align()
{
  yOffset += (yOffset > 0 ? -1 : 1) * WEAPON_ALIGN_INCREMENT;
}

void Weapon::clearStack()
{
  clearingGemCount = WEAPON_GEMS_MAX;
  onClear();
}

void Weapon::render(uint8_t x, uint8_t y, bool active)
{
  arduboy.fillRect(
    x + WEAPON_DIVIDER_X,
    y + yOffset + WEAPON_DIVIDER_Y,
    WEAPON_DIVIDER_WIDTH,
    WEAPON_DIVIDER_HEIGHT
  );

  if (active)
  {
    arduboy.fillRect(
      x + WEAPON_ACTIVE_INDICATOR_X,
      y + yOffset + WEAPON_ACTIVE_INDICATOR_Y,
      WEAPON_ACTIVE_INDICATOR_WIDTH,
      WEAPON_ACTIVE_INDICATOR_HEIGHT
    ); 

    sprites.drawErase(
      x + WEAPON_ICON_X,
      y + yOffset + WEAPON_ICON_Y,
      weaponSprite,
      type
    );  
  }
  else
  {
    sprites.drawOverwrite(
      x + WEAPON_ICON_X,
      y + yOffset + WEAPON_ICON_Y,
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
    previewGem.render(
      x + WEAPON_PREVIEW_GEM_X,
      y + WEAPON_GEM_Y
    );  
  }

  if (hasFallingGem) {
    fallingGem.render(
      x + WEAPON_PREVIEW_GEM_X,
      y + WEAPON_GEM_Y
    );  
  }

  for (uint8_t i = 0; i < gemCount; i++)
  {
    gems[i].render(
      x + WEAPON_GEMS_X + (gemSpritePlusMask[0] * i),
      y + yOffset + WEAPON_GEM_Y
    );  
  }
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
  return hasFallingGem && fallingGem.xOffset >= x - WEAPON_PREVIEW_GEM_X;
}

int Weapon::getGemX(uint8_t i)
{
  return WEAPON_GEMS_X + (i * gemSpritePlusMask[0]);
}

int Weapon::getEndOfStackX()
{
  return getGemX(gemCount);
}

bool Weapon::isAligned()
{
  return yOffset == 0;
}
