#include "Preview.h"

#define PREVIEW_GEM_MAX 4

#define PREVIEW_GEM_DATA_LENGTH 2
#define PREVIEW_GEM_DATA_POSITION 0
#define PREVIEW_GEM_DATA_TYPE 1

#define PREVIEW_GEM_X 2
#define PREVIEW_GEM_Y 0

#define PREVIEW_DIVIDER_X 0
#define PREVIEW_DIVIDER_Y 0
#define PREVIEW_DIVIDER_WIDTH 1
#define PREVIEW_DIVIDER_HEIGHT 49

uint8_t Preview::gemCount = 0;

namespace
{
  uint8_t gemYOffsets[PREVIEW_GEM_MAX] = {0, 12, 24, 36};
  uint8_t gems[PREVIEW_GEM_MAX][PREVIEW_GEM_DATA_LENGTH] = {
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0}
  };

  uint8_t emptyPreviewPosition() {
    uint8_t position = random(0, PREVIEW_GEM_MAX);
    bool empty = true;

    for (uint8_t i = 0; i < Preview::gemCount; i++) {
      if (gems[i][PREVIEW_GEM_DATA_POSITION] == position)
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

void Preview::queueGem()
{
  if (gemCount == PREVIEW_GEM_MAX) return;

  gems[gemCount][PREVIEW_GEM_DATA_POSITION] = emptyPreviewPosition();
  gems[gemCount][PREVIEW_GEM_DATA_TYPE] = random(0, GEM_TYPE_COUNT);
  gemCount++;
}

void Preview::render(
  uint8_t x,
  uint8_t y
)
{
  arduboy.fillRect(
    x + PREVIEW_DIVIDER_X,
    y + PREVIEW_DIVIDER_Y,
    PREVIEW_DIVIDER_WIDTH,
    PREVIEW_DIVIDER_HEIGHT
  );

  for (uint8_t i = 0; i < gemCount; i++)
  {
    sprites.drawPlusMask(
      x + PREVIEW_GEM_X,
      y + PREVIEW_GEM_Y + gemYOffsets[gems[i][PREVIEW_GEM_DATA_POSITION]],
      gemSpritePlusMask,
      gems[i][PREVIEW_GEM_DATA_TYPE]
    );
  }
}
