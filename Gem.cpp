#include "Gem.h"

void Gem::updateX() {
  if (arduboy.everyXFrames(INITIAL_GAME_SPEED) && topOfCurrentRow() < x) { 
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

int* Gem::weapon() {
  return weapons[row];
}

int Gem::topOfCurrentRow() {
  return gemXOffsets[weapon()[WEAPON_DATA_GEM_COUNT]];
}
