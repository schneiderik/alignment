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
  uint8_t previewGemCount = 0;
  uint8_t fallingGemCount = 0;

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
  int tmpPreviewGem = weapons[weaponPositions[a]].previewGem;
  weapons[weaponPositions[a]].previewGem = weapons[weaponPositions[b]].previewGem;
  weapons[weaponPositions[b]].previewGem = tmpPreviewGem;

  uint8_t tmp = weaponPositions[a];
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
  if (previewGemCount == PUZZLE_WEAPON_COUNT) return;

  Weapon& weapon = getRandomWeapon();

  if (weapon.previewGem == -1)
  {
    weapon.queuePreviewGem();
  }
  else
  {
    queueRandomPreviewGem();
  }
}

void Puzzle::update()
{
  previewGemCount = 0;
  fallingGemCount = 0;

  for (uint8_t i = 0; i < PUZZLE_WEAPON_COUNT; i++)
  {
    weapons[i].update();

    if (weapons[i].fallingGem != -1) fallingGemCount++;
    if (weapons[i].previewGem != -1) previewGemCount++;
  }

  if (previewGemCount == 0)
  {
    queueRandomPreviewGem();
    queueRandomPreviewGem();
  }

  if (fallingGemCount == 0 && previewGemCount > 0)
  {
    for (uint8_t i = 0; i < PUZZLE_WEAPON_COUNT; i++)
    {
      weapons[i].dropPreviewGem();
    }
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
