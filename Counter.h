#ifndef COUNTER_H
#define COUNTER_H

#include "global.h"

struct Counter
{
  bool running = false;
  uint8_t mode;
  int value = 0;
  int count = 1;
  int direction = 1;
  int interval = 10;

  Counter();
  Counter(int, int);

  void init(int, int);
  void reset();
  void run();
  void loop();
  void alternate();
  void stop();
  void update();
};

#endif
