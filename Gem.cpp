#include "Gem.h"
#include "Weapon.h"

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

void Gem::update() {
  updateX();
  updateY(); 
}

void Gem::render() {
  sprites.drawPlusMask(x, y, gemSpritePlusMask, type);
}

Weapon& Gem::getWeapon() {
  return *weapons[row];
}

bool Gem::atEndOfRowX() {
  return getWeapon().endOfRowX() >= x;
}
