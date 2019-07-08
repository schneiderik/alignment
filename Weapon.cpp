#include "Weapon.h"

Weapon::Weapon() {
  gems_ = new Gem[WEAPON_GEM_MAX];
  
  int num = random(0, 4);
  int gemType;

  gemCount_ = num;

  for (int i = 0; i < gemCount_; i++) {
    gemType = random(0, GEM_COUNT);
    
    gems_[i].setType(gemType);
    gems_[i].stop();
  }
}

void Weapon::update() {  
  for (int i = 0; i < gemCount_; i++) {
    gems_[i].update();
  }  
}

bool Weapon::isWaitingForAnimation() {
  for (int i = 0; i < gemCount_; i++) {
    if (gems_[i].isAnimatingOut()) return true;
  }

  return false;
}

void Weapon::setType(int type) {
  type_ = type;
}

Gem* Weapon::getGems() {
  return gems_;
}

int Weapon::getGemCount() {
  return gemCount_;
}

void Weapon::addGem(Gem& gem) {
  gems_[gemCount_] = gem;
  gems_[gemCount_].stop();
  gemCount_++;
}

void Weapon::clearGem(int i) {
  gems_[i].animateOut();
}

void Weapon::emptyGems() {
  gemCount_ = 0;
}

void Weapon::renderActiveIcon_(int x, int y) {
  arduboy.fillRect(
    x,
    y,
    WEAPON_ACTIVE_INDICATOR_WIDTH,
    WEAPON_ACTIVE_INDICATOR_HEIGHT
  );
  
  sprites.drawErase(
    x + WEAPON_ICON_X_OFFSET,
    y + WEAPON_ICON_Y_OFFSET,
    weaponSprite,
    type_
  );  
}

void Weapon::renderInactiveIcon_(int x, int y) {
  sprites.drawOverwrite(
    x + WEAPON_ICON_X_OFFSET,
    y + WEAPON_ICON_Y_OFFSET,
    weaponSprite,
    type_
  );  
}

void Weapon::renderDivider_(int x, int y) {
  arduboy.fillRect(
    x + WEAPON_DIVIDER_X_OFFSET,
    y + WEAPON_DIVIDER_Y_OFFSET,
    WEAPON_DIVIDER_WIDTH,
    WEAPON_DIVIDER_HEIGHT
  );
}

void Weapon::render(int x, int y, bool active) {
  active ? renderActiveIcon_(x, y) : renderInactiveIcon_(x, y);
  renderDivider_(x, y);

  for (int i = 0; i < gemCount_; i++) {
    gems_[i].render(
      x + WEAPON_GEMS_X_OFFSET + (i * (gemSpritePlusMask[0] + WEAPON_GEM_SPACING)),
      y + WEAPON_GEMS_Y_OFFSET  
    );
  } 
}
