#include "Gem.h"

void Gem::init(int type_)
{
  type = type_;
  reset();
}

void Gem::reset()
{
  xOffset = 0; 
  yOffset = 0;
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
