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

  Weapon weapons[PUZZLE_WEAPON_COUNT];
  uint8_t weaponPositions[PUZZLE_WEAPON_COUNT] = {0, 1, 2, 3};
  uint8_t weaponYOffsets[PUZZLE_WEAPON_COUNT] = {0, 12, 24, 36};

  void queuePreviewGemOnWeapon(uint8_t weaponIndex)
  {
    if (previewGemCount == PUZZLE_WEAPON_COUNT) return;

    if (weapons[weaponIndex].previewGem >= 0)
    {
      queuePreviewGemOnWeapon(random(0, PUZZLE_WEAPON_COUNT));
    }
    else
    {
      previewGemCount++;
      weapons[weaponIndex].previewGem = random(0, GEM_TYPE_COUNT);
    }
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

void Puzzle::queuePreviewGem()
{
  queuePreviewGemOnWeapon(random(0, PUZZLE_WEAPON_COUNT));
}

void Puzzle::update()
{
  if (previewGemCount == 0)
  {
    queuePreviewGem();
    queuePreviewGem();
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
