#ifndef COUNTER_H
#define COUNTER_H

#include "global.h"

#define COUNTER_FRAME_COUNT_DEFAULT 1
#define COUNTER_FRAME_DURATION_DEFAULT 10
#define COUNTER_DIRECTION_DEFAULT 1

struct Counter
{
  bool running = false;
  uint8_t mode;
  int frame = 0;
  int previousFrame = 0;
  int frameCount = 1;
  int direction = 1;
  int frameDuration = 10;
  void (*onComplete)();

  Counter();
  Counter(int, int);
  Counter(int, int, void(*)());

  void init(int, int);
  void init(int, int, void (*)());
  void reset();
  void run();
  void loop();
  void alternate();
  void stop();
  bool frameJustCompleted(int);
  void update();
};

#endif
