#include "Weapon.h"
#include "Game.h"
#include "Gem.h"
#include "WeaponManager.h"

Weapon::Weapon(int i) {
  type = i;
  y = weaponYOffsets[i];
  empty();
}

bool Weapon::isFull() {
  return gemCount == WEAPON_GEMS_MAX;
}

bool Weapon::isEmpty() {
  return gemCount == 0;
}

void Weapon::addGem(Gem& gem) {
  gem.setNext(lastGem);
  lastGem = &gem;
  gemCount++;
}

void Weapon::popLastGem() {
  lastGem->pop();
  lastGem = lastGem->getNext();
  gemCount--;
}

void Weapon::clearGems() {
  Gem* gem = lastGem;
  
  while (gem != NULL) {
    gem->clear();
    
    gem = gem->getNext();
  }
  
  empty();
}

void Weapon::empty() {
  gemCount = 0;
}

void Weapon::render(bool active) {
  renderIcon(active);
  renderDivider();
}

void Weapon::renderIcon(bool active) {
  if (active) {
    arduboy.fillRect(0, y, 12, 12); 
    sprites.drawErase(2, y + 2, weaponSprite, type);  
  } else {
    sprites.drawOverwrite(2, y + 2, weaponSprite, type);    
  }  
}

void Weapon::renderDivider() {
  arduboy.fillRect(14, y + 1, 1, 10);
}

int Weapon::getOrder() {
  for (int i = 0; i < WEAPON_COUNT; i++) {
    if (type == game->weapons.get(i).type) return i;
  }
}

int Weapon::endOfRowX() {
  return gemXOffsets[gemCount];
}

void Weapon::reset(int order) {
  type = order;
  y = weaponYOffsets[order];
  empty();
}

void Weapon::update() {
  updateY();
}

void Weapon::updateY() {
  int order = getOrder();
  
  if (y != weaponYOffsets[order]) y += y < weaponYOffsets[order] ? 3 : -3;
}

void Weapon::setGemRows(int row) {
  Gem* gem = lastGem;

  while (gem != NULL) {
    gem->setRow(row);
    gem = gem->getNext();
  }
}
