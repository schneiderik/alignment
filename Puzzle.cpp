#include "Puzzle.h"

Puzzle::Puzzle() {
  int y;

  // GemManager
  gemWeaponTypes_ = new int[PUZZLE_GEM_MAX];
  gems_ = new Gem[PUZZLE_GEM_MAX];

  // Weapons
  weaponOrder_ = new int[PUZZLE_WEAPON_COUNT] {0, 1, 2, 3};
  weapons_ = new Weapon[PUZZLE_WEAPON_COUNT];

  // Matches
  matches = new int[PUZZLE_WEAPON_COUNT * WEAPON_GEM_MAX];
  resetMatches();

  for (int i = 0; i < PUZZLE_WEAPON_COUNT; i++) {
    y = y_ + (weaponOrder_[i] * PUZZLE_WEAPON_HEIGHT);
    
    weapons_[i].setType(i);
    weapons_[i].setX(x_);
    weapons_[i].setY(y);
    weapons_[i].setTargetY(y);
  }
}

void Puzzle::resetMatches() {
  for (int i = 0; i < PUZZLE_WEAPON_COUNT * WEAPON_GEM_MAX; i++) {
    matches[i] = 0;
  }
}

void Puzzle::checkForMatches() {  
  resetMatches();
  
  for (int i = 0; i < PUZZLE_WEAPON_COUNT; i++) {
    Weapon& weapon1 = weaponAtIndex_(i);
    Weapon& weapon2 = weaponAtIndex_(i+1);
    
    for (int g = 0; g < weapon1.getGemCount(); g++) {
      Gem& gem1 = weapon1.getGems()[g];
      
      if (i < PUZZLE_WEAPON_COUNT - 1 && g < weapon2.getGemCount()) {
        Gem& gem2 = weapon2.getGems()[g];
  
        if (gem1.getType() == gem2.getType()) {
          matches[(indexOfWeapon_(weapon1) * WEAPON_GEM_MAX) + g] = 1;
          matches[(indexOfWeapon_(weapon2) * WEAPON_GEM_MAX) + g] = 1;
        }      
      }
    
      if (g < weapon1.getGemCount() - 1) {
        Gem& gem2 = weapon1.getGems()[g + 1];
  
        if (gem1.getType() == gem2.getType()) {
          matches[(indexOfWeapon_(weapon1) * WEAPON_GEM_MAX) + g] = 1;
          matches[(indexOfWeapon_(weapon1) * WEAPON_GEM_MAX) + g + 1] = 1;
        }
      }
    }
  }
}

Weapon& Puzzle::weaponAtIndex_(int index) {
   for (int i = 0; i < PUZZLE_WEAPON_COUNT; i++) {
     if (weaponOrder_[i] == index) return weapons_[i];
   }
}

int Puzzle::indexOfWeapon_(Weapon& weapon) {
  return weaponOrder_[weapon.getType()];
}

void Puzzle::clearMatches() {
  bool isMatch;
    
  for (int i = 0; i < PUZZLE_WEAPON_COUNT; i++) {
    Weapon& weapon = weaponAtIndex_(i);
    
    for (int g = 0; g < weapon.getGemCount(); g++) {
      isMatch = matches[(i * WEAPON_GEM_MAX) + g] == 1;
      
      if (isMatch) weapon.clearGemAtIndex(g);
    }
  }
}

void Puzzle::update() {  
  updateWeapons_();
  updateGems_();
  
  for (int i = 0; i < PUZZLE_GEM_MAX; i++) {
    Gem& gem = gems_[i];
    int weaponType = gemWeaponTypes_[i];
    Weapon& weapon = weapons_[weaponType];
        
    if (gem.isFalling()) {
      gem.setTargetX(weapon.getGemsMaxX());
      gem.setTargetY(weapon.getGemsY());
    }
    
    if (gem.isStopped()) {
      weapon.addGem(gem.getType());
      gem.hide();
    }
  }

  if (previewIsEmpty_()) populatePreview_();
  if (previewIsReadyToActivate_()) activatePreview_();
  
  checkForMatches();
  clearMatches();
}

void Puzzle::updateWeapons_() {
  for (int i = 0; i < PUZZLE_WEAPON_COUNT; i++) {
    weapons_[i].update();
  }  
}

void Puzzle::updateGems_() {
  for (int i = 0; i < PUZZLE_GEM_MAX; i++) {
    if (!isClearingGems_()) gems_[i].update();
  }  
}

void Puzzle::moveCursorDown() {
  if (cursorIndex_ < PUZZLE_CURSOR_MAX) cursorIndex_++; 
}

void Puzzle::moveCursorUp() {
  if (cursorIndex_ > PUZZLE_CURSOR_MIN) cursorIndex_--;
}

void Puzzle::swapWeapons() {
  if (isClearingGems_()) return;
  
  int tmp, weaponType1, weaponType2;

  for (int i = 0; i < PUZZLE_WEAPON_COUNT; i++) {
    if (weaponOrder_[i] == cursorIndex_) weaponType1 = i;
    if (weaponOrder_[i] == cursorIndex_ + 1) weaponType2 = i;
  }

  int& weapon1Order = weaponOrder_[weaponType1];
  int& weapon2Order = weaponOrder_[weaponType2];
  int tmpWeaponOrder = weapon1Order;
  
  weapon1Order = weapon2Order;
  weapon2Order = tmpWeaponOrder;

  Weapon& weapon1 = weapons_[weaponType1];
  Weapon& weapon2 = weapons_[weaponType2];

  for (int i = 0; i < PUZZLE_GEM_MAX; i++) {
    Gem& gem = gems_[i];
    int& gemWeaponType = gemWeaponTypes_[i];
    
    if (gem.isReady() || gem.isFalling()) {
      if (gemWeaponType == weaponType1 && weapon2.getGemsMaxX() < gem.getX()) {
        gemWeaponType = weaponType2;
      } else if (gemWeaponType == weaponType2 && weapon1.getGemsMaxX() < gem.getX()) { 
        gemWeaponType = weaponType1;
      }      
    }
  }

  weapon1.setTargetY(y_ + (weapon1Order * PUZZLE_WEAPON_HEIGHT));
  weapon2.setTargetY(y_ + (weapon2Order * PUZZLE_WEAPON_HEIGHT));
}

bool Puzzle::isClearingGems_() {
  for (int i = 0; i < PUZZLE_WEAPON_COUNT; i++) {
    if (weapons_[i].isClearing()) return true;
  }

  return false;
}

bool Puzzle::previewIsEmpty_() {
  for (int i = 0; i < PUZZLE_GEM_MAX; i++) {
    Gem& gem = gems_[i];
    
    if (gem.isReady()) return false;
    if (gem.isFalling() && gem.getXPlusWidth() > x_ + PUZZLE_GEM_PREVIEW_THRESHOLD_X_OFFSET) return false;
  }

  return true;
}

void Puzzle::populatePreview_() {
  int weaponType = random(0, PUZZLE_WEAPON_COUNT);
  int gemType = random(0, GEM_COUNT);
  
  Gem& gem = gems_[gemIndex_];
  Weapon& weapon = weapons_[weaponType];
  
  gemWeaponTypes_[gemIndex_] = weaponType;
  
  gem.setType(gemType);
  gem.setY(weapon.getGemsY());
  gem.setTargetY(weapon.getGemsY());
  gem.setX(x_ + PUZZLE_GEM_PREVIEW_X_OFFSET);
  gem.setTargetX(weapon.getGemsMaxX());
  gem.ready();

  gemIndex_ == PUZZLE_LAST_GEM_INDEX ? gemIndex_ = 0 : gemIndex_++;
}

bool Puzzle::previewIsReadyToActivate_() {
  for (int i = 0; i < PUZZLE_GEM_MAX; i++) {
    if (gems_[i].isFalling()) return false;
  }
      
  return true;
}

void Puzzle::activatePreview_() {
  for (int i = 0; i < PUZZLE_GEM_MAX; i++) {
    if (gems_[i].isReady()) gems_[i].drop();
  }   
}

void Puzzle::renderPreviewDivider_() {
  arduboy.fillRect(
    x_ + PUZZLE_PREVIEW_DIVIDER_X_OFFSET,
    y_ + PUZZLE_PREVIEW_DIVIDER_Y_OFFSET,
    PUZZLE_PREVIEW_DIVIDER_WIDTH,
    PUZZLE_PREVIEW_DIVIDER_HEIGHT
  ); 
}

void Puzzle::render() {
  renderPreviewDivider_();
  
  for (int i = 0; i < PUZZLE_WEAPON_COUNT; i++) {
    weapons_[i].render(
      weaponOrder_[i] == cursorIndex_ || weaponOrder_[i] == cursorIndex_ + 1
    );
  }

  // GemManager
  for (int i = 0; i < PUZZLE_GEM_MAX; i++) {
    gems_[i].render();
  }
}
