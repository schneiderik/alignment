#include "Gem2.h"
#include "Game.h"
#include "Weapon.h"
#include "WeaponManager.h"

void Gem2::init(int row) {
  type_ = random(0, GEM_TYPE_COUNT);
  row_ = row;
  x_ = PREVIEW_GEM_X;
  y_ = gemYOffsets[row];
  state_ = GEM_STATE_INACTIVE;
  next_ = NULL;
}

void Gem2::render() {
  sprites.drawPlusMask(x_, y_, gemSpritePlusMask, type_);
}

bool Gem2::updateX() {
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

void Gem2::updateY() {
  if (y_ != gemYOffsets[row_]) {
    y_ += y_ < gemYOffsets[row_] ? 3 : -3;
  }  
}

bool Gem2::updateClear() {
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

void Gem2::updatePop() {
  if (arduboy.everyXFrames(5)) {
    if (type_ < GEM_POPPING_ANIMATION_END_FRAME) {
      type_++;
    } else {
      hide();
    }
  }
}

Weapon& Gem2::getWeapon() {
  return game->weapons.get(row_);
}

bool Gem2::atEndOfRowX() {
  return x_ <= getWeapon().endOfRowX();
}

bool Gem2::belowEndOfRowX() {
  return x_ < getWeapon().endOfRowX();
}

bool Gem2::belowPreviewThreshold() {
  return x_ <= PREVIEW_THRESHOLD_X;
}

bool Gem2::matchesLastGemInRow() {
  Weapon& weapon = getWeapon();

  if (weapon.isEmpty()) return false;

  return weapon.lastGem->getType() == type_;
}

void Gem2::changeRowIfObstructed(int row1, int row2) {
  if (belowEndOfRowX()) row_ = row_ == row1 ? row2 : row1;
}

void Gem2::drop() {
  if (isInactive()) state_ = GEM_STATE_FALLING;
}

void Gem2::clear() {
  xVel_ = random(0, 3) - 1;
  yVel_ = random(0, 3) - 2;
  state_ = GEM_STATE_CLEARING;
}

void Gem2::pop() {
  type_ = GEM_POPPING_ANIMATION_START_FRAME;
  state_ = GEM_STATE_POPPING;
}

void Gem2::stack() {
  state_ = GEM_STATE_STACKED;
}

void Gem2::hide() {
  state_ = GEM_STATE_HIDDEN;
}

bool Gem2::isInactive() { return state_ == GEM_STATE_INACTIVE; }
bool Gem2::isFalling() { return state_ == GEM_STATE_FALLING; }
bool Gem2::isStacked() { return state_ == GEM_STATE_STACKED; }
bool Gem2::isClearing() { return state_ == GEM_STATE_CLEARING; }
bool Gem2::isPopping() { return state_ == GEM_STATE_POPPING; }
bool Gem2::isHidden() { return state_ == GEM_STATE_HIDDEN; }

Gem2* Gem2::getNext() const { return next_; }
void Gem2::setNext(Gem2* next) { next_ = next; }
int Gem2::getRow() const { return row_; }
void Gem2::setRow(int row) { row_ = row; }
int Gem2::getType() const { return type_; }
