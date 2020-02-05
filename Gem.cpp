#include "Gem.h"
#include "Weapon.h"

Gem::Gem() {
  velocityX = random(0, 3) - 1;
  initialVelocityY = random(0, 3) - 2;
  velocityY = initialVelocityY;
}

void Gem::updateX() {
  if (arduboy.everyXFrames(INITIAL_GAME_SPEED) && getWeapon().endOfRowX() < x) { 
    x -= 3;
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
      velocityY = initialVelocityY;
      state = GEM_STATE_INACTIVE;
    }
  }
}

void Gem::update() {
  switch(state) {
    case GEM_STATE_CLEARING:
      updateClear();
      break;
    case GEM_STATE_ACTIVE:
      updateX();
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

bool Gem::isActive() {
  return state == GEM_STATE_ACTIVE;
}

bool Gem::isClearing() {
  return state == GEM_STATE_CLEARING;
}

Weapon& Gem::getWeapon() {
  return *weapons[row];
}

bool Gem::atEndOfRowX() {
  return getWeapon().endOfRowX() >= x;
}

void Gem::clear() {
  state = GEM_STATE_CLEARING;
}
