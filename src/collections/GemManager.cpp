#include "GemManager.h"
#include "../../Game.h"
#include "../entities/Gem.h"
#include "../entities/Weapon.h"
#include "../entities/Preview.h"

GemManager::GemManager() {
  firstAvailable_ = &gems_[0];

  gems_[0].setNext(&gems_[1]);

  for (int i = 1; i < GEM_MANAGER_SIZE - 2; i++) {
    gems_[i].setNext(&gems_[i + 1]);
    gems_[i].setPrevious(&gems_[i - 1]);
  }

  gems_[GEM_MANAGER_SIZE - 1].setPrevious(&gems_[GEM_MANAGER_SIZE - 2]);
}

Gem* GemManager::create() {
  if (firstAvailable_ == NULL) return;
  
  Gem* newGem = firstAvailable_;

  firstAvailable_ = newGem->getNext();
  firstAvailable_->setPrevious(NULL);

  newGem->setNext(NULL);
  newGem->setPrevious(NULL);

  return newGem;
}

void GemManager::remove(Gem& gem) {
  firstAvailable_->setPrevious(&gem);

  gem.setPrevious(NULL);
  gem.setNext(firstAvailable_);

  firstAvailable_ = &gem; 
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

    if (gem.isHidden()) continue;

    if (gem.isClearing()) {
      gem.update();
      newClearingGemCount++;
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

    if (gem.isHidden()) continue;
    
    gem.update();
    
    if (gem.isInactive()) {
      if (!hasFallingGems()) {
        gem.drop();
        newFallingGemCount++;
        preview_.clear();
      }
    } else if (gem.isFalling()) {
      newFallingGemCount++;
      
      if (gem.belowPreviewThreshold()) {
        newBelowPreviewThresholdCount++;
      }
    } else if (gem.isClearing()) {
      newClearingGemCount++;
    }

    if (gem.isHidden()) remove(gem);
  }
  
  clearingGemCount_ = newClearingGemCount;
  fallingGemCount_ = newFallingGemCount;
  belowPreviewThresholdCount_ = newBelowPreviewThresholdCount;
}
