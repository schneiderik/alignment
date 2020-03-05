#include "Gem.h"
#include "../../Game.h"
#include "Weapon.h"
#include "../collections/WeaponManager.h"

void Gem::init(int row) {
  type_ = random(0, GEM_TYPE_COUNT);
  row_ = row;
  x_ = PREVIEW_GEM_X;
  y_ = gemYOffsets[row];
  state_ = GEM_STATE_INACTIVE;
  next_ = NULL;
  previous_ = NULL;
}

void Gem::render() {
  sprites.drawPlusMask(x_, y_, gemSpritePlusMask, type_);
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
  if (y_ != gemYOffsets[row_]) {
    y_ += y_ < gemYOffsets[row_] ? 3 : -3;
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
    if (type_ < GEM_POPPING_ANIMATION_END_FRAME) {
      type_++;
    } else {
      hide();
    }
  }
}

Weapon& Gem::getWeapon() {
  return game->weapons.get(row_);
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
  if (isInactive()) state_ = GEM_STATE_FALLING;
}

void Gem::clear() {
  xVel_ = random(0, 3) - 1;
  yVel_ = random(0, 3) - 2;
  state_ = GEM_STATE_CLEARING;
}

void Gem::pop() {
  type_ = GEM_POPPING_ANIMATION_START_FRAME;
  state_ = GEM_STATE_POPPING;
}

void Gem::stack() {
  state_ = GEM_STATE_STACKED;
}

void Gem::hide() {
  state_ = GEM_STATE_HIDDEN;
}

bool Gem::isInactive() { return state_ == GEM_STATE_INACTIVE; }
bool Gem::isFalling() { return state_ == GEM_STATE_FALLING; }
bool Gem::isStacked() { return state_ == GEM_STATE_STACKED; }
bool Gem::isClearing() { return state_ == GEM_STATE_CLEARING; }
bool Gem::isPopping() { return state_ == GEM_STATE_POPPING; }
bool Gem::isHidden() { return state_ == GEM_STATE_HIDDEN; }

Gem* Gem::getNext() const { return next_; }
void Gem::setNext(Gem* next) { next_ = next; }
Gem* Gem::getPrevious() const { return previous_; }
void Gem::setPrevious(Gem* previous) { previous_ = previous; }
int Gem::getRow() const { return row_; }
void Gem::setRow(int row) { row_ = row; }
int Gem::getType() const { return type_; }
