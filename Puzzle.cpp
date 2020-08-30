#include "Puzzle.h"

#include "Preview.h"
#include "Weapon.h"

#define PUZZLE_PREVIEW_X 89
#define PUZZLE_PREVIEW_Y 0

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

void Puzzle::swap()
{
  swap(cursor, cursor + 1);
}

void Puzzle::queuePreviewGem()
{
  Preview::queueGem();
}

void Puzzle::update()
{
  if (Preview::gemCount == 0)
  {
    Preview::queueGem();
    Preview::queueGem();
  }
}

void Puzzle::render(
  uint8_t x,
  uint8_t y
)
{
  Preview::render(
    x + PUZZLE_PREVIEW_X,
    y + PUZZLE_PREVIEW_Y
  );

  for (uint8_t i = 0; i < PUZZLE_WEAPON_COUNT; i++)
  {
    weapons[weaponPositions[i]].render(
      x + PUZZLE_WEAPONS_X,
      y + PUZZLE_WEAPONS_Y + weaponYOffsets[i],
      i == cursor || i == cursor + 1
    );
  }
}
