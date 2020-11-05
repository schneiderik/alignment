#ifndef GEM_H
#define GEM_H

#include "../../global.h"

struct Gem
{
  int type;
  int x;
  int y;
  int velX;
  int velY;

  void init(int);
  void reset();
};

#endif
