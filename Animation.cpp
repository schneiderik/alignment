#include "Animation.h"

void Animation::init(char* sprite_, int count_, int interval_)
{
  sprite = sprite_;
  count = count_;
  interval = interval_;
}

void Animation::render(int x, int y)
{
  {
    sprites.drawOverwrite(
      x,
      y,
      sprite,
      value
    );
  }
}
