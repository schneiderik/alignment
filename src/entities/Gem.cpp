#include "Gem.h"
#include "../../Game.h"

void Gem::init(int x, int y) {
  type_ = random(0, COUNT);
  x_ = x;
  y_ = y;
  state_ = STATE_INACTIVE;
}

void Gem::render() {
  sprites.drawPlusMask(x_, y_, gemSpritePlusMask, type_);
}

void Gem::update() {
  switch (state_) {
    case STATE_FALLING:
      updateX_();
      break;
    case STATE_POPPING:
      updatePop_();
      break;
    case STATE_CLEARING:
      updateClear_();
      break;
  }
}

void Gem::updateX_() {
  if (arduboy.everyXFrames(game->getGameSpeed())) {
    x_ += MOVE_X_INCREMENT;
  }
}

void Gem::updateClear_() {
  if (arduboy.everyXFrames(5)) {
    if (y_ < SCREEN_HEIGHT) {
      y_ += yVel_;
      x_ += xVel_;
      yVel_ += GRAVITY_ACCELERATION;
    } else {
      hide();
    }
  }
}

void Gem::updatePop_() {
  if (arduboy.everyXFrames(5)) {
    if (type_ < POPPING_ANIMATION_END_FRAME) {
      type_++;
    } else {
      hide();
    }
  }
}

void Gem::stop() { state_ = STATE_INACTIVE; }
void Gem::drop() { state_ = STATE_FALLING; }
void Gem::hide() { state_ = STATE_HIDDEN; }

void Gem::clear() {
  xVel_ = random(0, 3) - 1;
  yVel_ = random(0, 3) - 2;
  state_ = STATE_CLEARING;
}

void Gem::pop() {
  type_ = POPPING_ANIMATION_START_FRAME;
  state_ = STATE_POPPING;
}


bool Gem::isInactive() { return state_ == STATE_INACTIVE; }
bool Gem::isFalling() { return state_ == STATE_FALLING; }
bool Gem::isClearing() { return state_ == STATE_CLEARING; }
bool Gem::isPopping() { return state_ == STATE_POPPING; }
bool Gem::isHidden() { return state_ == STATE_HIDDEN; }

Gem* Gem::getNext() const { return next_; }
void Gem::setNext(Gem* next) { next_ = next; }
int Gem::getX() const { return x_; }
int Gem::getY() const { return y_; }
void Gem::setY(int y) { y_ = y; }
int Gem::getType() const { return type_; }
