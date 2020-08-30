#include "Puzzle.h"

#define PUZZLE_PREVIEW_DIVIDER_X 89
#define PUZZLE_PREVIEW_DIVIDER_Y 0
#define PUZZLE_PREVIEW_DIVIDER_WIDTH 1
#define PUZZLE_PREVIEW_DIVIDER_HEIGHT 49

#define PUZZLE_WEAPONS_X 0
#define PUZZLE_WEAPONS_Y 1

#define PUZZLE_CURSOR_MIN 0
#define PUZZLE_CURSOR_MAX 2

#define PUZZLE_WEAPON_COUNT 4

#define PUZZLE_GEM_TYPE_COUNT 5

#define PUZZLE_PREVIEW_GEM_DATA_LENGTH 2
#define PUZZLE_PREVIEW_GEM_DATA_POSITION 0
#define PUZZLE_PREVIEW_GEM_DATA_TYPE 1

#define PUZZLE_PREVIEW_GEM_X 91

#define PUZZLE_WEAPON_CURSOR_X 0
#define PUZZLE_WEAPON_CURSOR_WIDTH 12
#define PUZZLE_WEAPON_CURSOR_HEIGHT 12

#define PUZZLE_WEAPON_ICON_X 2
#define PUZZLE_WEAPON_ICON_Y 2

#define PUZZLE_WEAPON_DIVIDER_X 14
#define PUZZLE_WEAPON_DIVIDER_Y 1
#define PUZZLE_WEAPON_DIVIDER_WIDTH 1
#define PUZZLE_WEAPON_DIVIDER_HEIGHT 10

namespace
{
  uint8_t cursor = PUZZLE_CURSOR_MIN;
  uint8_t previewGemCount = 0;
  uint8_t preview[PUZZLE_WEAPON_COUNT][PUZZLE_PREVIEW_GEM_DATA_LENGTH] = {
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0}
  };

  uint8_t weaponPositions[PUZZLE_WEAPON_COUNT] = {0, 1, 2, 3};
  uint8_t weaponYOffsets[PUZZLE_WEAPON_COUNT] = {0, 12, 24, 36};

  uint8_t emptyPreviewPosition() {
    uint8_t position = random(0, PUZZLE_WEAPON_COUNT);
    bool empty = true;

    for (uint8_t i = 0; i < previewGemCount; i++) {
      if (preview[i][PUZZLE_PREVIEW_GEM_DATA_POSITION] == position)
      {
        empty = false;
      }
    }

    if (empty)
    {
      return position;
    }
    else {
      return emptyPreviewPosition();
    }
  }
}

void Puzzle::init(
)
{
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
  if (previewGemCount == PUZZLE_WEAPON_COUNT) return;

  preview[previewGemCount][PUZZLE_PREVIEW_GEM_DATA_POSITION] = emptyPreviewPosition();
  preview[previewGemCount][PUZZLE_PREVIEW_GEM_DATA_TYPE] = random(0, PUZZLE_GEM_TYPE_COUNT);
  previewGemCount++;
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
  arduboy.fillRect(
    x + PUZZLE_PREVIEW_DIVIDER_X,
    y + PUZZLE_PREVIEW_DIVIDER_Y,
    PUZZLE_PREVIEW_DIVIDER_WIDTH,
    PUZZLE_PREVIEW_DIVIDER_HEIGHT
  );

  for (uint8_t i = 0; i < previewGemCount; i++)
  {
    sprites.drawPlusMask(
      x + PUZZLE_PREVIEW_GEM_X,
      y + weaponYOffsets[preview[i][PUZZLE_PREVIEW_GEM_DATA_POSITION]],
      gemSpritePlusMask,
      preview[i][PUZZLE_PREVIEW_GEM_DATA_TYPE]
    );
  }

  for (uint8_t i = 0; i < PUZZLE_WEAPON_COUNT; i++)
  {
    arduboy.fillRect(
      x + PUZZLE_WEAPON_DIVIDER_X,
      y  + weaponYOffsets[i] + PUZZLE_WEAPON_DIVIDER_Y,
      PUZZLE_WEAPON_DIVIDER_WIDTH,
      PUZZLE_WEAPON_DIVIDER_HEIGHT
    );

    if (i == cursor || i == cursor + 1)
    {
      arduboy.fillRect(
        x + PUZZLE_WEAPON_CURSOR_X,
        y + weaponYOffsets[i],
        PUZZLE_WEAPON_CURSOR_WIDTH,
        PUZZLE_WEAPON_CURSOR_HEIGHT
      ); 

      sprites.drawErase(
        x + PUZZLE_WEAPON_ICON_X,
        y + weaponYOffsets[i] + PUZZLE_WEAPON_ICON_Y,
        weaponSprite,
        weaponPositions[i]
      );  
    }
    else
    {
      sprites.drawOverwrite(
        x + PUZZLE_WEAPON_ICON_X,
        y + weaponYOffsets[i] + PUZZLE_WEAPON_ICON_Y,
        weaponSprite,
        weaponPositions[i]
      );  
    }  
  }
}
