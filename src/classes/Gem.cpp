#include "Gem.h"

void Gem::init(int type_)
{
  type = type_;
  reset();
}

void Gem::reset()
{
  x = 0; 
  y = 0;
}
