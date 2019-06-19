#include "Hearts.h"

void Hearts::render() {
  for (int i = 0; i < HEARTS_MAX; i++) {  
    sprites.drawOverwrite(
      HEARTS_X + (i * (heartSprite[0] + HEART_OFFSET)),
      HEARTS_Y,
      heartSprite,
      i <= num_ ? 0 : 1
    );
  }  
}

void Hearts::lose() {
  if (num_ > 0) { num_--; } 
}

void Hearts::gain() {
  if (num_ < HEARTS_MAX) { num_++; } 
}

void Hearts::reset() {
  num_ = HEARTS_MAX;
}
