#include "Player.h"

void Player::reset() {
  score_ = 0;
  resetHealth();
}

unsigned long int Player::getScore() {
  return score_;
}

void Player::addScore(int points) {
  score_ += points;
}

bool Player::isDead() {
  return health_ == 0;
}

void Player::takeDamage() {
  health_--;
}

int Player::getHealth() {
  return health_;
}

void Player::resetHealth() {
  health_ = HEALTH_MAX;
}
