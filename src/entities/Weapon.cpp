#include "Weapon.h"
#include "../../Game.h"
#include "Gem.h"
#include "../collections/WeaponManager.h"

Weapon::Weapon(int i) {
  reset(i);
}

void Weapon::reset(int order) {
  type_ = order;
  y_ = weaponYOffsets[order];
  empty();
}

void Weapon::update() {
  int order = getOrder();
  
  if (y_ != weaponYOffsets[order]) y_ += y_ < weaponYOffsets[order] ? 3 : -3;
}

void Weapon::render(bool active) {
  renderIcon_(active);
  renderDivider_();
}

void Weapon::addGem(Gem& gem) {
  gem.setNext(lastGem_);
  lastGem_ = &gem;
  gemCount_++;
}

void Weapon::popLastGem() {
  lastGem_->pop();
  lastGem_ = lastGem_->getNext();
  gemCount_--;
}

void Weapon::clearGems() {
  Gem* gem = lastGem_;
  
  while (gem != NULL) {
    gem->clear();
    
    gem = gem->getNext();
  }
  
  empty();
}

void Weapon::setGemRows(int row) {
  Gem* gem = lastGem_;

  while (gem != NULL) {
    gem->setRow(row);
    gem = gem->getNext();
  }
}

bool Weapon::isFull() {
  return gemCount_ == WEAPON_GEMS_MAX;
}

bool Weapon::isEmpty() {
  return gemCount_ == 0;
}

void Weapon::empty() {
  gemCount_ = 0;
}

int Weapon::getType() {
  return type_;
}

Gem& Weapon::getLastGem() {
  return *lastGem_;
}

int Weapon::getOrder() {
  for (int i = 0; i < WEAPON_COUNT; i++) {
    if (type_ == game->weapons.get(i).getType()) return i;
  }
}

int Weapon::getEndOfRowX() {
  return gemXOffsets[gemCount_];
}

void Weapon::renderIcon_(bool active) {
  if (active) {
    arduboy.fillRect(0, y_, 12, 12); 
    sprites.drawErase(2, y_ + 2, weaponSprite, type_);  
  } else {
    sprites.drawOverwrite(2, y_ + 2, weaponSprite, type_);    
  }  
}

void Weapon::renderDivider_() {
  arduboy.fillRect(14, y_ + 1, 1, 10);
}
