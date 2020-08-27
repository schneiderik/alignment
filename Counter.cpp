#include "Counter.h"

#define COUNTER_MODE_DEFAULT 0
#define COUNTER_MODE_LOOP 1
#define COUNTER_MODE_ALTERNATE 2

Counter::Counter() {}

Counter::Counter(int count_, int interval_) 
{
  init(count_, interval_);
}

void Counter::init(int count_, int interval_)
{
  count = count_;
  interval = interval_;
}

void Counter::reset()
{
  value = 0;
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

void Counter::stop()
{
  running = false;
}

void Counter::update()
{
  if (!running) return;

  if (arduboy.everyXFrames(interval))
  {
    value += direction;

    switch (mode)
    {
      case COUNTER_MODE_LOOP:
        if (value == count)
        {
          reset();
        }
        break;
      case COUNTER_MODE_ALTERNATE:
        if (value == count - 1)
        {
          direction = -1;
        }

        if (value == 0)
        {
          direction = 1;
        }
        break;
      default:
        if (value == count - 1)
        {
          stop();
        }
        break;
    }
  }
}
