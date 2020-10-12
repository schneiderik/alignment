#include "Counter.h"

#define COUNTER_MODE_DEFAULT 0
#define COUNTER_MODE_LOOP 1
#define COUNTER_MODE_ALTERNATE 2

Counter::Counter() {}

Counter::Counter(int frameCount_, int frameDuration_) 
{
  init(frameCount_, frameDuration_);
}

void Counter::init(int frameCount_, int frameDuration_)
{
  frameCount = frameCount_;
  frameDuration = frameDuration_;
}

void Counter::reset()
{
  frame = 0;
  previousFrame = 0;
}

void Counter::run()
{
  reset();
  mode = COUNTER_MODE_DEFAULT;
  running = true;
}

void Counter::loop()
{
  reset();
  mode = COUNTER_MODE_LOOP;
  running = true;
}

void Counter::alternate()
{
  reset();
  mode = COUNTER_MODE_ALTERNATE;
  running = true;
}

bool Counter::frameJustCompleted(int target)
{
  return previousFrame == target && previousFrame != frame;
}

void Counter::stop()
{
  running = false;
}

void Counter::update(void (*onComplete)())
{
  if (!running) return;

  previousFrame = frame;

  if (arduboy.everyXFrames(frameDuration))
  {
    switch (mode)
    {
      case COUNTER_MODE_LOOP:
        frame += direction;

        if (frame == frameCount)
        {
          reset();
        }
        break;
      case COUNTER_MODE_ALTERNATE:
        frame += direction;

        if (frame == frameCount - 1)
        {
          direction = -1;
        }

        if (frame == 0)
        {
          direction = 1;
        }
        break;
      default:
        if (frame == frameCount - 1)
        {
          stop();
          onComplete();
        }
        else
        {
          frame += direction;
        }
        break;
    }
  }
}

void Counter::update()
{
  update(&noop);
}
