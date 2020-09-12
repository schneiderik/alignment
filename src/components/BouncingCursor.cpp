#include "BouncingCursor.h"

#include "../../Counter.h"

#define BOUNCING_CURSOR_FRAME_COUNT 3
#define BOUNCING_CURSOR_INTERVAL 8

namespace
{
  Counter counter(
    BOUNCING_CURSOR_FRAME_COUNT,
    BOUNCING_CURSOR_INTERVAL
  );
}

void BouncingCursor::init()
{
  counter.alternate();
}

void BouncingCursor::update()
{
  counter.update();
}

void BouncingCursor::render(uint8_t x, uint8_t y)
{
  sprites.drawOverwrite(
    x,
    y + counter.frame - 1,
    questCursorImage,
    0
  );  
}
