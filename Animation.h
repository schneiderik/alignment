#ifndef ANIMATION_H
#define ANIMATION_H

#include "global.h"

struct Animation
{
  bool running = false;
  int frame = 0;
  int frameCount = 1;
  int direction = 1;
  int interval = 10;

  void init(int, int);
  void reset();
  void run();
  void stop();
  void update();
};

struct AnimationLoop: public Animation
{
  void update();
};

struct AnimationBounce: public Animation
{
  void update();
};

#endif
