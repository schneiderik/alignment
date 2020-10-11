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

  Weapon weapons[PUZZLE_WEAPON_COUNT];
  uint8_t weaponPositions[PUZZLE_WEAPON_COUNT] = {0, 1, 2, 3};
  uint8_t weaponYOffsets[PUZZLE_WEAPON_COUNT] = {0, 12, 24, 36};

  Weapon& getRandomWeapon()
  {
    return weapons[random(0, PUZZLE_WEAPON_COUNT)];
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
  int tmp;
  Weapon& weaponA = weapons[weaponPositions[a]];
  Weapon& weaponB = weapons[weaponPositions[b]];

  tmp = weaponA.previewGem;
  weaponA.previewGem = weaponB.previewGem;
  weaponB.previewGem = tmp;

  if (
    (weaponA.hasFallingGem() && weaponA.fallingGemX >= weaponB.endOfStackX())
    || (weaponB.hasFallingGem() && weaponB.fallingGemX >= weaponA.endOfStackX())
  )
  {
    tmp = weaponA.fallingGem;
    weaponA.fallingGem = weaponB.fallingGem;
    weaponB.fallingGem = tmp;

    tmp = weaponA.fallingGemX;
    weaponA.fallingGemX = weaponB.fallingGemX;
    weaponB.fallingGemX = tmp;
  }

  tmp = weaponPositions[a];
  weaponPositions[a] = weaponPositions[b];
  weaponPositions[b] = tmp;
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

void Puzzle::update()
{
  bool hasPreviewGems = false;
  bool hasFallingGems = false;

  for (uint8_t i = 0; i < PUZZLE_WEAPON_COUNT; i++)
  {
    weapons[i].update();

    if (weapons[i].hasPreviewGem()) hasPreviewGems = true;
    if (weapons[i].hasFallingGem()) hasFallingGems = true;
  }

  if (!hasPreviewGems)
  {
    queueRandomPreviewGem();
    queueRandomPreviewGem();
  }

  if (hasPreviewGems && !hasFallingGems)
  {
    dropPreviewGems();
  }
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
