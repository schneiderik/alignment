#include "Gem.h"

#define GEM_FALL_INCREMENT -3

void Gem::init(int type_)
{
  type = type_;
  reset();
}

void Gem::reset()
{
  xOffset = 0; 
  yOffset = 0;
  velX = random(0, 3) - 1;
  velY = random(0, 3) - 2;
}

void Gem::swap(Gem& other)
{
  swapValues(type, other.type);
  swapValues(xOffset, other.xOffset);
  swapValues(yOffset, other.yOffset);
  swapValues(velX, other.velX);
  swapValues(velY, other.velY);
}

void Gem::fall()
{
  xOffset += GEM_FALL_INCREMENT;
}

void Gem::render(int x, int y)
{
  sprites.drawPlusMask(
    x + xOffset,
    y + yOffset,
    gemSpritePlusMask,
    type
  );  
}
