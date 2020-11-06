#ifndef GEM_H
#define GEM_H

#include "../../global.h"

struct Gem
{
  int type;
  int xOffset = 0;
  int yOffset = 0;
  int velX = 0;
  int velY = 0;

  void init(int);
  void reset();
  void swap(Gem&);
  void render(int, int);
};

#endif
