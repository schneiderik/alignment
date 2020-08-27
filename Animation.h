#ifndef ANIMATION_H
#define ANIMATION_H

#include "global.h"

#include "Counter.h"

struct Animation: public Counter
{
  char* sprite;

  void init(char*, int, int);
  void render(int, int);
};

#endif
