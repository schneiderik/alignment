#include "Puzzle.h"

#include "../../Weapon.h"

#define PUZZLE_WEAPONS_X 0
#define PUZZLE_WEAPONS_Y 1

#define PUZZLE_CURSOR_MIN 0
#define PUZZLE_CURSOR_MAX 2

#define PUZZLE_WEAPON_COUNT 4

namespace
{
  uint8_t cursor = PUZZLE_CURSOR_MIN;
  uint8_t clearingWeaponCount = 0;
  uint8_t previewGemCount = 0;
  uint8_t fallingGemCount = 0;

  Weapon weapons[PUZZLE_WEAPON_COUNT];
  int weaponPositions[PUZZLE_WEAPON_COUNT] = {0, 1, 2, 3};
  uint8_t weaponYOffsets[PUZZLE_WEAPON_COUNT] = {0, 12, 24, 36};

  Weapon& getRandomWeapon()
  {
    return weapons[random(0, PUZZLE_WEAPON_COUNT)];
  }

  void swapValues(int& a, int& b)
  {
    int tmp = a;
    a = b;
    b = tmp;
  }
}

void Puzzle::init(
)
{
  for(uint8_t i = 0; i < PUZZLE_WEAPON_COUNT; i++)
  {
    weapons[i].init(i);
  }
}

void Puzzle::incrementCursor()
{
  if (cursor < PUZZLE_CURSOR_MAX)
  {
    cursor++;
  }
}

void Puzzle::decrementCursor()
{
  if (cursor > PUZZLE_CURSOR_MIN)
  {
    cursor--;
  }
}

void Puzzle::swap(uint8_t a, uint8_t b)
{
  Weapon& weaponA = weapons[weaponPositions[a]];
  Weapon& weaponB = weapons[weaponPositions[b]];

  if (
    weaponA.fallingGemIsAboveX(weaponB.getEndOfStackX())
    || weaponB.fallingGemIsAboveX(weaponA.getEndOfStackX())
  )
  {
    swapValues(weaponA.fallingGem, weaponB.fallingGem);
    swapValues(weaponA.fallingGemX, weaponB.fallingGemX);
  }

  swapValues(weaponA.previewGem, weaponB.previewGem);
  swapValues(weaponPositions[a], weaponPositions[b]);
}

void Puzzle::swapActiveWeapons()
{
  swap(cursor, cursor + 1);
}

void Puzzle::swapRandomWeapons()
{
  swap(cursor, cursor + 1);
}

void Puzzle::queueRandomPreviewGem()
{
  Weapon& weapon = getRandomWeapon();

  if (!weapon.hasPreviewGem())
  {
    weapon.queuePreviewGem();
  }
  else
  {
    queueRandomPreviewGem();
  }
}

void Puzzle::dropPreviewGems()
{
  for (uint8_t i = 0; i < PUZZLE_WEAPON_COUNT; i++)
  {
    weapons[i].dropPreviewGem();
  }
}

void Puzzle::updateClearingWeapons()
{
  for (uint8_t i = 0; i < PUZZLE_WEAPON_COUNT; i++)
  {
    Weapon& weapon = weapons[i];

    if (weapon.isClearing())
    {
      weapon.update();

      if (!weapon.isClearing()) clearingWeaponCount--;
    }
  }
}

void Puzzle::updateWeapons()
{
  if (previewGemCount == 0)
  {
    queueRandomPreviewGem();
    queueRandomPreviewGem();
  }

  if (previewGemCount > 0 && fallingGemCount == 0)
  {
    dropPreviewGems();
  }

  previewGemCount = 0;
  fallingGemCount = 0;
  clearingWeaponCount = 0;

  for (uint8_t i = 0; i < PUZZLE_WEAPON_COUNT; i++)
  {
    Weapon& weapon = weapons[i];

    weapon.update();

    if (weapon.hasPreviewGem()) previewGemCount++;
    if (weapon.hasFallingGem()) fallingGemCount++;
    if (weapon.isClearing()) clearingWeaponCount++;
  }
}

bool Puzzle::isClearing()
{
  return clearingWeaponCount > 0;
}

void Puzzle::update()
{
  clearingWeaponCount > 0
    ? updateClearingWeapons()
    : updateWeapons();
}

void Puzzle::render(
  uint8_t x,
  uint8_t y
)
{
  for (uint8_t i = 0; i < PUZZLE_WEAPON_COUNT; i++)
  {
    weapons[weaponPositions[i]].render(
      x + PUZZLE_WEAPONS_X,
      y + PUZZLE_WEAPONS_Y + weaponYOffsets[i],
      i == cursor || i == cursor + 1
    );
  }
}
