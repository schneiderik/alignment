#include "GemManager.h"
#include "Game.h"
#include "Gem.h"
#include "Weapon.h"

GemManager::GemManager() {
  firstAvailable_ = &gems_[0];

  for (int i = 0; i < GEM_MANAGER_SIZE - 1; i++) {
    gems_[i].setNext(&gems_[i + 1]);
  }

  gems_[GEM_MANAGER_SIZE - 1].setNext(NULL);
}

void GemManager::create() {
  if (firstAvailable_ == NULL) return;
  
  Gem* newGem = firstAvailable_;
  firstAvailable_ = newGem->getNext();

  newGem->init(randomEmptyRow());
}

void GemManager::create(int count) {
  for (int i = 0; i < count; i++) create();
}

bool GemManager::gemExistsInRow(int row) {  
  for (int i = 0; i < GEM_MANAGER_SIZE; i++) {
    Gem& gem = gems_[i];
    if (gem.isInactive() && gem.getRow() == row) return true;
  }

  return false;
}

bool GemManager::hasClearingGems() {
  return clearingGemCount_ > 0;
}

bool GemManager::hasInactiveGems() {
  return inactiveGemCount_ > 0;
}

bool GemManager::hasFallingGems() {
  return fallingGemCount_ > 0;
}

bool GemManager::fallingGemsAreBelowPreviewThreshold() {
  return fallingGemCount_ == belowPreviewThresholdCount_;
}

bool GemManager::shouldCreateGems() {
  return !hasClearingGems()
    && !hasInactiveGems()
    && fallingGemsAreBelowPreviewThreshold();
}

void GemManager::reset() {
  clearingGemCount_ = 0;
  fallingGemCount_ = 0;
  belowPreviewThresholdCount_ = 0;
  inactiveGemCount_ = 0;  

  for (int i = 0; i < GEM_MANAGER_SIZE; i++) {
    Gem& gem = gems_[i];
    gem.hide();
  }
}

void GemManager::render() {
  for (int i = 0; i < GEM_MANAGER_SIZE; i++) {
    Gem& gem = gems_[i];
    if (!gem.isHidden()) gem.render();
  }
}

int GemManager::randomEmptyRow() {
  int row = random(0, WEAPON_COUNT);

  return gemExistsInRow(row) ? randomEmptyRow() : row;
}

void GemManager::moveGemsInObstructedRows(int row1, int row2) {
  for(int i = 0; i < GEM_MANAGER_SIZE; i++) {
    Gem& gem = gems_[i];
    if (gem.isFalling()) gem.changeRowIfObstructed(row1, row2);
  }
}

void GemManager::update() {
  hasClearingGems() ? updateClearing() : updateFalling();
}

void GemManager::updateClearing() {
  int newClearingGemCount = 0;
    
  for (int i = 0; i < GEM_MANAGER_SIZE; i++) {
    Gem& gem = gems_[i];
    Weapon& weapon = gem.getWeapon();

    if (gem.isHidden()) continue;

    if (gem.isClearing()) {
      if (gem.updateClear()) newClearingGemCount++;
    }

    if (gem.isHidden()) remove(gem);
  }
  
  clearingGemCount_ = newClearingGemCount;
}

void GemManager::updateFalling() {
  int newClearingGemCount = 0;
  int newFallingGemCount = 0;
  int newBelowPreviewThresholdCount = 0;
  int newInactiveGemCount = 0;
  
  if (shouldCreateGems()) create(2);
  
  for (int i = 0; i < GEM_MANAGER_SIZE; i++) {
    Gem& gem = gems_[i];
    Weapon& weapon = gem.getWeapon();

    if (gem.isHidden()) continue;
    
    gem.updateY();
    
    if (gem.isInactive()) {
      if (!hasFallingGems()) {
        gem.drop();
        newFallingGemCount++;
      } else {
        newInactiveGemCount++;
      }
    } else if (gem.isFalling()) {
      if (gem.updateX()) {
        newFallingGemCount++;
        
        if (gem.belowPreviewThreshold()) {
          newBelowPreviewThresholdCount++;
        }
      } else {
        if (gem.matchesLastGemInRow()) {         
          game->score += 100;
          gem.pop();
          weapon.popLastGem();
          confirmSound();
          game->enemy.takeDamage(5, weapon.type);            
        } else {
          if (weapon.isFull()) {
            weapon.clearGems();
            gem.clear();
            newClearingGemCount = 7;
            game->health--;
            loseHeartSound();
          } else {
            weapon.addGem(gem);
            game->score += 10; 
          }            
        }
      }
    } else if (gem.isPopping()) {
      gem.updatePop();
    }

    if (gem.isHidden()) remove(gem);
  }
  
  clearingGemCount_ = newClearingGemCount;
  fallingGemCount_ = newFallingGemCount;
  belowPreviewThresholdCount_ = newBelowPreviewThresholdCount;
  inactiveGemCount_ = newInactiveGemCount;  
}

void GemManager::remove(Gem& gem) {
  gem.setNext(firstAvailable_);
  firstAvailable_ = &gem; 
}
