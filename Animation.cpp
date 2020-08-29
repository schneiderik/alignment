#include "Animation.h"

void Animation::init(unsigned char* sprite_, int frameCount_, int frameDuration_)
{
  sprite = sprite_;
  frameCount = frameCount_;
  frameDuration = frameDuration_;
}

void Animation::render(int x, int y)
{
  {
    sprites.drawOverwrite(
      x,
      y,
      sprite,
      frame
    );
  }
}
