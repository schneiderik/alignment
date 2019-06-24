#include "Hearts.h"

void Hearts::render(int x, int y) {
  for (int i = 0; i < HEARTS_MAX; i++) {  
    sprites.drawOverwrite(
      x + (i * (heartSprite[0] + HEART_SPACING)),
      y,
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
