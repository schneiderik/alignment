#include "Hearts.h"

void Hearts::init(Player player) {
  player_ = &player;
}

void Hearts::render(int x, int y) {
  for (int i = 0; i < HEALTH_MAX; i++) {  
    sprites.drawErase(
      x + (i * (heartSprite[0] + 1)),
      y,
      heartSprite,
      i < player_->getHealth() ? 0 : 1
    );
  }  
}
