#include "Gem.h"
#include "../../Game.h"
#include "../../Player.h"
#include "Weapon.h"
#include "../collections/WeaponManager.h"

static const int Gem::Y_OFFSETS[Weapon::COUNT] = {14, 26, 38, 50};
static const int Gem::X_OFFSETS[Weapon::GEM_MAX] = {17, 29, 41, 53, 65, 77, 89};

void Gem::init(int row) {
  type_ = random(0, COUNT);
  row_ = row;
  x_ = PREVIEW_GEM_X;
  y_ = Y_OFFSETS[row];
  state_ = STATE_INACTIVE;
  next_ = NULL;
}

void Gem::render() {
  sprites.drawPlusMask(x_, y_, gemSpritePlusMask, type_);
}

void Gem::update() {
  switch (state_) {
    case STATE_FALLING:
      updateY();
      updateX();
      break;
    case STATE_STACKED:
      updateY();
      break;
    case STATE_POPPING:
      updatePop();
      break;
    case STATE_CLEARING:
      updateClear();
      break;
  }
}

bool Gem::updateX() {
  if (arduboy.everyXFrames(INITIAL_GAME_SPEED)) {
    if (!atEndOfRowX()) { 
      x_ -= 3;
    } else {
      stack();
      return false;
    }
  }

  return true;
}

void Gem::updateY() {
  if (y_ != Y_OFFSETS[row_]) {
    y_ += y_ < Y_OFFSETS[row_] ? 3 : -3;
  }  
}

bool Gem::updateClear() {
  if (arduboy.everyXFrames(5)) {
    if (y_ < SCREEN_HEIGHT) {
      y_ += yVel_;
      x_ += xVel_;
      yVel_ += GRAVITY_ACCELERATION;
    } else {
      hide();
      return false;
    }
  }

  return true;
}

void Gem::updatePop() {
  if (arduboy.everyXFrames(5)) {
    if (type_ < POPPING_ANIMATION_END_FRAME) {
      type_++;
    } else {
      hide();
    }
  }
}

Weapon& Gem::getWeapon() {
  return weaponManager->get(row_);
}

bool Gem::atEndOfRowX() {
  return x_ <= getWeapon().getEndOfRowX();
}

bool Gem::belowEndOfRowX() {
  return x_ < getWeapon().getEndOfRowX();
}

bool Gem::belowPreviewThreshold() {
  return x_ <= PREVIEW_THRESHOLD_X;
}

void Gem::changeRowIfObstructed(int row1, int row2) {
  if (belowEndOfRowX()) row_ = row_ == row1 ? row2 : row1;
}

void Gem::drop() {
  state_ = STATE_FALLING;
}

void Gem::clear() {
  xVel_ = random(0, 3) - 1;
  yVel_ = random(0, 3) - 2;
  state_ = STATE_CLEARING;
}

void Gem::pop() {
  type_ = POPPING_ANIMATION_START_FRAME;
  state_ = STATE_POPPING;
}

void Gem::stack() {
  state_ = STATE_STACKED;
  getWeapon().addGem(*this);
  player->addScore(10);
}

void Gem::hide() {
  state_ = STATE_HIDDEN;
}

bool Gem::isInactive() { return state_ == STATE_INACTIVE; }
bool Gem::isFalling() { return state_ == STATE_FALLING; }
bool Gem::isStacked() { return state_ == STATE_STACKED; }
bool Gem::isClearing() { return state_ == STATE_CLEARING; }
bool Gem::isPopping() { return state_ == STATE_POPPING; }
bool Gem::isHidden() { return state_ == STATE_HIDDEN; }

Gem* Gem::getNext() const { return next_; }
void Gem::setNext(Gem* next) { next_ = next; }
int Gem::getRow() const { return row_; }
void Gem::setRow(int row) { row_ = row; }
int Gem::getType() const { return type_; }
