#include "Player.h"

void Player:update() {
}

void Player::render() {
  hearts.render();
  score.render();
}

void Player::reset() {
  hearts.reset();
  score.reset();
}

