#ifndef COUNTER_H
#define COUNTER_H

#include "global.h"

struct Counter
{
  bool running = false;
  uint8_t mode;
  int frame = 0;
  int previousFrame = 0;
  int frameCount = 1;
  int direction = 1;
  int frameDuration = 10;

  Counter();
  Counter(int, int);

  void init(int, int);
  void reset();
  void run();
  void loop();
  void alternate();
  void stop();
  bool frameJustCompleted(int);
  void update();
};

#endif
