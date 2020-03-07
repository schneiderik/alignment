#include "Weapon.h"
#include "../../Game.h"
#include "Gem.h"
#include "../collections/WeaponManager.h"

Weapon::Weapon(int i) {
  reset(i);
}

void Weapon::reset(int order) {
  type_ = order;
  order_ = order;
  y_ = weaponYOffsets[order];
  empty_();
}

void Weapon::update() {
  switch (state_) {
    case WEAPON_STATE_ACTIVE:
      if (lastGemsMatch_()) popLastGems_();
      if (isOverflowed_()) clear_();
      if (gemsOutOfOrder_()) setGemRows_(order_);
      if (isMisaligned_()) adjustY_();
      break;
    case WEAPON_STATE_CLEARING:
      if (isCleared_()) {
        empty_();
        activate_();
      }
      break;
  }
}

void Weapon::render(bool active) {
  renderIcon_(active);
  renderDivider_();
}

void Weapon::addGem(Gem& gem) {
  lastGem_->setPrevious(&gem);
  gem.setPrevious(NULL);
  gem.setNext(lastGem_);
  lastGem_ = &gem;
  gemCount_++;
}

void Weapon::popLastGem_() {
  lastGem_->pop();
  lastGem_ = lastGem_->getNext();
  gemCount_--;
}

void Weapon::popLastGems_() {
  for (int i = 0; i < 2; i++) popLastGem_();

  game->score += 100;
  game->enemy.takeDamage(5, type_);            
  confirmSound();
}

void Weapon::setGemRows_(int row) {
  Gem* gem = lastGem_;

  while (gem != NULL) {
    gem->setRow(row);
    gem = gem->getNext();
  }
}

void Weapon::clearGems_() {
  Gem* gem = lastGem_;
  
  while (gem != NULL) {
    gem->clear();
    gem = gem->getNext();
  }
}

void Weapon::setOrder(int order) { order_ = order; }
void Weapon::activate_() { state_ = WEAPON_STATE_ACTIVE; }
void Weapon::empty_() { gemCount_ = 0; lastGem_ = NULL; }
void Weapon::adjustY_() { y_ += y_ < weaponYOffsets[order_] ? 3 : -3; }
void Weapon::clear_() {
  state_ = WEAPON_STATE_CLEARING;
  clearGems_();
  game->health--;
  loseHeartSound();
}

int Weapon::getEndOfRowX() { return gemXOffsets[gemCount_]; }

bool Weapon::isMisaligned_() { return y_ != weaponYOffsets[order_]; }
bool Weapon::isFull_() { return gemCount_ == WEAPON_GEMS_MAX - 1; }
bool Weapon::isOverflowed_() { return gemCount_ == WEAPON_GEMS_MAX; }
bool Weapon::isEmpty_() { return gemCount_ == 0; }
bool Weapon::isMatchable_() { return gemCount_ >= 2; }
bool Weapon::isClearing() { return state_ == WEAPON_STATE_CLEARING; }
bool Weapon::isActive_() { return state_ == WEAPON_STATE_ACTIVE; }
bool Weapon::lastGemsMatch_() { return isMatchable_() && lastGem_->getType() == lastGem_->getNext()->getType(); }
bool Weapon::gemsOutOfOrder_() { return !isEmpty_() && lastGem_->getRow() != order_; }
bool Weapon::isCleared_() { 
  Gem* gem = lastGem_;
  
  while (gem != NULL) {
    if (gem->isClearing()) return false;
    gem = gem->getNext();
  }

  return true;
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
