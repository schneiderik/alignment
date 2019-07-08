#include "Player.h"

bool Player::isDead() {
  return hearts.get() == 0;
}

void Player::reset() {
  hearts.reset();
  score.reset();
}

