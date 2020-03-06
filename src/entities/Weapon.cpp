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
  empty();
}

void Weapon::update() {
  switch (state_) {
    case WEAPON_STATE_ACTIVE:
      updateY_();
      break;
    case WEAPON_STATE_CLEARING:
      updateClearing_();
      break;
  }
}

void Weapon::updateY_() {
  if (lastGem_ != NULL && lastGem_->getRow() != order_) setGemRows(order_);
  if (y_ != weaponYOffsets[order_]) y_ += y_ < weaponYOffsets[order_] ? 3 : -3;
}

void Weapon::updateClearing_() {
  Gem* gem = lastGem_;
  
  while (gem != NULL) {
    if (gem->isClearing()) return;
    
    gem = gem->getNext();
  }

  empty();
  activate();
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

  if (isOverflowed()) {
    clear();
    game->health--;
    loseHeartSound();
  }

  if (lastGemsMatch_()) {         
    popLastGems_();
    game->score += 100;
    game->enemy.takeDamage(5, type_);            
    confirmSound();
  }
}

void Weapon::setOrder(int order) { order_ = order; }

bool Weapon::lastGemsMatch_() {
  if (gemCount_ < 2) return false;

  return lastGem_->getType() == lastGem_->getNext()->getType();
}

void Weapon::popLastGems_() {
  lastGem_->pop();
  lastGem_->getNext()->pop();
  lastGem_ = lastGem_->getNext()->getNext();
  gemCount_ -= 2;
}

void Weapon::setGemRows(int row) {
  Gem* gem = lastGem_;

  while (gem != NULL) {
    gem->setRow(row);
    gem = gem->getNext();
  }
}

void Weapon::empty() {
  gemCount_ = 0;
  lastGem_ = NULL;
}

void Weapon::activate() {
  state_ = WEAPON_STATE_ACTIVE;
}

void Weapon::clear() {
  state_ = WEAPON_STATE_CLEARING;

  Gem* gem = lastGem_;
  
  while (gem != NULL) {
    gem->clear();
    
    gem = gem->getNext();
  }
}

int Weapon::getType() {
  return type_;
}

int Weapon::getEndOfRowX() {
  return gemXOffsets[gemCount_];
}

bool Weapon::isFull() { return gemCount_ == WEAPON_GEMS_MAX - 1; }
bool Weapon::isOverflowed() { return gemCount_ == WEAPON_GEMS_MAX; }
bool Weapon::isEmpty() { return gemCount_ == 0; }
bool Weapon::isClearing() { return state_ == WEAPON_STATE_CLEARING; }
bool Weapon::isActive() { return state_ == WEAPON_STATE_ACTIVE; }

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
