#include "Weapon.h"
#include "Gem.h"

Weapon::Weapon() {
  gems_ = new Gem[WEAPON_GEM_MAX];
}
  
void Weapon::update() {
  updateGems_();
  removeGems_();
  updateY_();
}

void Weapon::updateGems_() {
  for (int i = 0; i < gemCount_; i++) {     
    gems_[i].update();
  }   
}

void Weapon::removeGems_() {
  for (int i = gemCount_ - 1; i >= 0; i--) {
    if (gems_[i].isHidden()) removeGemAtIndex(i);
  }
}

void Weapon::updateY_() {
  if (moveInterval_ == WEAPON_MOVE_FRAME_LENGTH) {
    if (isSwapping()) {
      setY(y_ < targetY_ ? y_ + WEAPON_MOVE_INCREMENT : y_ - WEAPON_MOVE_INCREMENT);
    }

    moveInterval_ = 0;
  }

  moveInterval_++;
}

void Weapon::setType(int type) {
  type_ = type;
}

int Weapon::getType() {
  return type_;
}

void Weapon::setX(int x) {
  x_ = x;

  for (int i = 0; i < WEAPON_GEM_MAX; i++) {
    Gem& gem = gems_[i];
    
    gem.setX(getGemX(i));
    gem.setTargetX(getGemX(i));
  } 
}

int Weapon::getX() {
  return x_;
}

int Weapon::getGemX(int gemIndex) {
  return x_ + WEAPON_GEMS_X_OFFSET + (gemIndex * (gemSpritePlusMask[0] + WEAPON_GEM_SPACING));  
}

int Weapon::getGemsMaxX() {
  return getGemX(gemCount_);
}

void Weapon::setY(int y) {
  y_ = y;

  for (int i = 0; i < WEAPON_GEM_MAX; i++) {  
    Gem& gem = gems_[i];
    
    gem.setY(getGemsY());
    gem.setTargetY(getGemsY());
  } 
}

void Weapon::setTargetY(int y) {
  targetY_ = y;
}

int Weapon::getGemsY() {
  return y_ + WEAPON_GEMS_Y_OFFSET;
}

Gem* Weapon::getGems() {
  return gems_;
}

int Weapon::getGemCount() {
  return gemCount_;
}

void Weapon::addGem(int gemType) {
  Gem& gem = gems_[gemCount_];
  
  gem.setType(gemType);
  gem.setX(getGemsMaxX());
  gem.setTargetX(getGemsMaxX());
  gem.stop();
  
  gemCount_++;
}

void Weapon::clearGemAtIndex(int gemIndex) {
  gems_[gemIndex].clear();
}

void Weapon::removeGemAtIndex(int gemIndex) {
  gemCount_--;
  
  for (int i = gemIndex; i < gemCount_; i++) {
    Gem& gem = gems_[i];
    Gem& nextGem = gems_[i + 1];
    
    if (!nextGem.isHidden()) {
      gem.setType(nextGem.getType());
      gem.setX(nextGem.getX());
      gem.adjust();
      nextGem.hide();
    }
  }
}

void Weapon::emptyGems() {
  gemCount_ = 0;
}

bool Weapon::isStopped() {
  return !isClearing() || !isSwapping();
}

bool Weapon::isClearing() {
  for (int i = 0; i < gemCount_; i++) {
    if (gems_[i].isClearing() || gems_[i].isAdjusting()) return true;
  }

  return false;
}

bool Weapon::isSwapping() {
  return y_ != targetY_;
}

void Weapon::renderActiveIcon_() {
  arduboy.fillRect(
    x_,
    y_,
    WEAPON_ACTIVE_INDICATOR_WIDTH,
    WEAPON_ACTIVE_INDICATOR_HEIGHT
  );
  
  sprites.drawErase(
    x_ + WEAPON_ICON_X_OFFSET,
    y_ + WEAPON_ICON_Y_OFFSET,
    weaponSprite,
    type_
  );  
}

void Weapon::renderInactiveIcon_() {
  sprites.drawOverwrite(
    x_ + WEAPON_ICON_X_OFFSET,
    y_ + WEAPON_ICON_Y_OFFSET,
    weaponSprite,
    type_
  );  
}

void Weapon::renderDivider_() {
  arduboy.fillRect(
    x_ + WEAPON_DIVIDER_X_OFFSET,
    y_ + WEAPON_DIVIDER_Y_OFFSET,
    WEAPON_DIVIDER_WIDTH,
    WEAPON_DIVIDER_HEIGHT
  );
}

void Weapon::render(bool active) {
  active ? renderActiveIcon_() : renderInactiveIcon_();
  renderDivider_();

  for (int i = 0; i < gemCount_; i++) {    
    gems_[i].render();
  } 
}
