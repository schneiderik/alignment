#include "GemManager.h"
#include "../../Game.h"
#include "../entities/Gem.h"
#include "../entities/Weapon.h"
#include "../entities/Preview.h"

GemManager::GemManager() {
  firstAvailable_ = &gems_[0];

  for (int i = 0; i < GEM_MANAGER_SIZE - 1; i++) {
    gems_[i].setNext(&gems_[i + 1]);
  }

  gems_[GEM_MANAGER_SIZE - 1].setNext(NULL);
}

Gem* GemManager::create() {
  if (firstAvailable_ == NULL) return;
  
  Gem* newGem = firstAvailable_;
  firstAvailable_ = newGem->getNext();
  newGem->setNext(NULL);

  return newGem;
}

bool GemManager::hasClearingGems() {
  return clearingGemCount_ > 0;
}

bool GemManager::hasFallingGems() {
  return fallingGemCount_ > 0;
}

bool GemManager::fallingGemsAreBelowPreviewThreshold() {
  return fallingGemCount_ == belowPreviewThresholdCount_;
}

bool GemManager::shouldCreateGems() {
  return !hasClearingGems()
    && preview_.isEmpty()
    && fallingGemsAreBelowPreviewThreshold();
}

void GemManager::reset() {
  clearingGemCount_ = 0;
  fallingGemCount_ = 0;
  belowPreviewThresholdCount_ = 0;
  preview_.clear();

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
  
  if (shouldCreateGems()) preview_.populate(2);
  
  for (int i = 0; i < GEM_MANAGER_SIZE; i++) {
    Gem& gem = gems_[i];
    Weapon& weapon = gem.getWeapon();

    if (gem.isHidden()) continue;
    
    gem.updateY();
    
    if (gem.isInactive()) {
      if (!hasFallingGems()) {
        gem.drop();
        newFallingGemCount++;
        preview_.clear();
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
}

void GemManager::remove(Gem& gem) {
  gem.setNext(firstAvailable_);
  firstAvailable_ = &gem; 
}
