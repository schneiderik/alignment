#include "Gem.h"
#include "Game.h"
#include "Weapon.h"
#include "WeaponManager.h"

void Gem::updateX() {
  if (arduboy.everyXFrames(INITIAL_GAME_SPEED)) {
    if (!atEndOfRowX()) { 
      x -= 3;
    } else {
      state = GEM_STATE_STACKED;
    }
  }    
}

void Gem::updateY() {
  if (y != gemYOffsets[row]) {
    y += y < gemYOffsets[row] ? 3 : -3;
  }  
}

void Gem::updateClear() {
  if (arduboy.everyXFrames(5)) {
    if (y < SCREEN_HEIGHT) {
      y += velocityY;
      x += velocityX;
      velocityY += GRAVITY_ACCELERATION;
    } else {
      game->clearingGemCount--;
      state = GEM_STATE_CLEARED;
    }
  }
}

void Gem::updatePop() {
  if (arduboy.everyXFrames(5)) {
    if (type < GEM_POPPING_ANIMATION_END_FRAME) {
      type++;
    } else {
      state = GEM_STATE_POPPED;
    }
  }
}

void Gem::update() {
  switch(state) {
    case GEM_STATE_CLEARING:
      updateClear();
      break;
    case GEM_STATE_POPPING:
      updatePop();
      break;
    case GEM_STATE_FALLING:
      updateY();
      updateX();
    case GEM_STATE_STACKED:
      updateY();   
      break;
  }
}

void Gem::render() {
  sprites.drawPlusMask(x, y, gemSpritePlusMask, type);
}

bool Gem::isInactive() {
  return state == GEM_STATE_INACTIVE;
}

bool Gem::isFalling() {
  return state == GEM_STATE_FALLING;
}

bool Gem::isStacked() {
  return state == GEM_STATE_STACKED;
}

bool Gem::isClearing() {
  return state == GEM_STATE_CLEARING;
}

bool Gem::isCleared() {
  return state == GEM_STATE_CLEARED;
}

bool Gem::isPopping() {
  return state == GEM_STATE_POPPING;
}

bool Gem::isPopped() {
  return state == GEM_STATE_POPPED;
}

Weapon& Gem::getWeapon() {
  return game->weapons.get(row);
}

bool Gem::atEndOfRowX() {
  return x <= getWeapon().endOfRowX();
}

bool Gem::belowEndOfRowX() {
  return x < getWeapon().endOfRowX();
}

bool Gem::belowPreviewThreshold() {
  return x <= PREVIEW_THRESHOLD_X;
}

void Gem::drop() {
  state = GEM_STATE_FALLING;
}

void Gem::changeRowIfObstructed(int row1, int row2) {
  if (belowEndOfRowX()) row = row == row1 ? row2 : row1;
}

void Gem::clear() {
  velocityX = random(0, 3) - 1;
  velocityY = random(0, 3) - 2;
  state = GEM_STATE_CLEARING;
  game->clearingGemCount++;
}

void Gem::pop() {
  type = GEM_POPPING_ANIMATION_START_FRAME;
  state = GEM_STATE_POPPING;
}
