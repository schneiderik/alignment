#include "Animation.h"

void Animation::init(int frameCount_, int interval_) {
  frameCount = frameCount_;
  interval = interval_;
}

void Animation::reset() {
  frame = 0;
}

void Animation::run()
{
  running = true;
}

void Animation::stop()
{
  running = false;
}

void Animation::update()
{
  if (!running) return;

  if (arduboy.everyXFrames(interval))
  {
    frame += direction;

    if (frame == frameCount - 1)
    {
      stop();
    }
  }
}

void AnimationLoop::update()
{
  if (!running) return;

  if (arduboy.everyXFrames(interval))
  {
    frame += direction;

    if (frame == frameCount)
    {
      reset();
    }
  }
}

void AnimationBounce::update()
{
  if (!running) return;

  if (arduboy.everyXFrames(interval))
  {
    frame += direction;

    if (frame == frameCount - 1)
    {
      direction = -1;
    }

    if (frame == 0)
    {
      direction = 1;
    }
  }
}
