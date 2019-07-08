#include "Puzzle.h"

Puzzle::Puzzle() {
  weaponOrder_ = new int[PUZZLE_WEAPON_COUNT] {0, 1, 2, 3};
  weapons_ = new Weapon[PUZZLE_WEAPON_COUNT];

  matches = new int[PUZZLE_WEAPON_COUNT * WEAPON_GEM_MAX];
  resetMatches();

  for (int i = 0; i < PUZZLE_WEAPON_COUNT; i++) {
    weapons_[i].setType(i);
  }
}

void Puzzle::resetMatches() {
  for (int i = 0; i < PUZZLE_WEAPON_COUNT * WEAPON_GEM_MAX; i++) {
    matches[i] = 0;
  }
}

void Puzzle::checkForMatches() {
  int gem1, gem2;

  resetMatches();
  
  for (int i = 0; i < PUZZLE_WEAPON_COUNT; i++) {
    for (int g = 0; g < weapons_[weaponOrder_[i]].getGemCount(); g++) {
      gem1 = weapons_[weaponOrder_[i]].getGems()[g].getType();
      
      if (i < PUZZLE_WEAPON_COUNT - 1 && g < weapons_[weaponOrder_[i + 1]].getGemCount()) {
        gem2 = weapons_[weaponOrder_[i + 1]].getGems()[g].getType();
  
        if (gem1 == gem2) {
          matches[(i * WEAPON_GEM_MAX) + g] = 1;
          matches[((i + 1) * WEAPON_GEM_MAX) + g] = 1;
        }      
      }
    
      if (g < weapons_[weaponOrder_[i]].getGemCount() - 1) {
        gem2 = weapons_[weaponOrder_[i]].getGems()[g + 1].getType();
  
        if (gem1 == gem2) {
          matches[(i * WEAPON_GEM_MAX) + g] = 1;
          matches[(i * WEAPON_GEM_MAX) + g + 1] = 1;
        }
      }
    }
  }
}

void Puzzle::clearMatches() {
  for (int i = 0; i < PUZZLE_WEAPON_COUNT; i++) {
    for (int g = 0; g < weapons_[weaponOrder_[i]].getGemCount(); g++) {
      if (matches[(i * WEAPON_GEM_MAX) + g] == 1) {
        weapons_[weaponOrder_[i]].getGems()[g].animateOut();
      }
    }
  }
}

void Puzzle::update() {
  for (int i = 0; i < PUZZLE_WEAPON_COUNT; i++) {
    weapons_[i].update();
  }
    
  if (previewIsEmpty_()) populatePreview_();
  if (activeGemCount_ == 0) activatePreviewGems_();
}

void Puzzle::moveCursorDown() {
  if (cursorIndex_ < PUZZLE_CURSOR_MAX) cursorIndex_++; 
}

void Puzzle::moveCursorUp() {
  if (cursorIndex_ > PUZZLE_CURSOR_MIN) cursorIndex_--;
}

void Puzzle::swapWeapons() {
  int tmp, weaponType1, weaponType2;

  for (int i = 0; i < PUZZLE_WEAPON_COUNT; i++) {
    if (weaponOrder_[i] == cursorIndex_) weaponType1 = i;
    if (weaponOrder_[i] == cursorIndex_ + 1) weaponType2 = i;
  }

  tmp = weaponOrder_[weaponType1];
  weaponOrder_[weaponType1] = weaponOrder_[weaponType2];
  weaponOrder_[weaponType2] = tmp;

  checkForMatches();
  clearMatches();
  
}

bool Puzzle::isWaitingForAnimation() {
  for (int i = 0; i < PUZZLE_WEAPON_COUNT; i++) {
    if (weapons_[i].isWaitingForAnimation()) return true;
  }

  return false;
}

bool Puzzle::previewIsEmpty_() {
  return true;
}

void Puzzle::populatePreview_() {}

void Puzzle::activatePreviewGems_() {}

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
      x_,
      y_ + (weaponOrder_[i] * PUZZLE_WEAPON_HEIGHT),
      weaponOrder_[i] == cursorIndex_ || weaponOrder_[i] == cursorIndex_ + 1
    );
  }

//  gemManager_.render();
}
