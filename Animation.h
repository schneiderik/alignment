#ifndef ANIMATION_H
#define ANIMATION_H

#include "global.h"

#include "Counter.h"

struct Animation: public Counter
{
  unsigned char* sprite;

  void init(unsigned char*, int, int);
  void render(int, int);
};

#endif
