#ifndef GEM_H
#define GEM_H

#include "../../global.h"

struct Gem
{
  int type;
  int x = 0;
  int y = 0;
  int velX = 0;
  int velY = 0;

  void init(int);
  void reset();
};

#endif
