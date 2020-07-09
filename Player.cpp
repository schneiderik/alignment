#include "Player.h"

void Player::reset() {
  score_ = 0;
  resetHealth();
}

unsigned long int Player::getScore() {
  return score_;
}

void Player::onNotify(const Weapon& weapon, Event event) {
  switch (event) {
    case Event::WEAPON_OVERFLOW:
      takeDamage();
      break;
    case Event::WEAPON_MATCH:
      addScore(WEAPON_MATCH_POINTS);
      break;
  }
}

void Player::onNotify(const Gem& gem, Event event) {
  switch (event) {
    case Event::GEM_LOCK:
      addScore(GEM_LOCK_POINTS);
      break;
  }
}

void Player::addScore(int points) {
  score_ += points;
}

bool Player::isDead() {
  return health_ == 0;
}

void Player::takeDamage() {
  health_--;

  notify(*this, Event::PLAYER_DAMAGED);
  if (isDead()) notify(*this, Event::PLAYER_DEFEATED);
}

int Player::getHealth() {
  return health_;
}

void Player::resetHealth() {
  health_ = HEALTH_MAX;
}
