#include "GemManager.h"
#include "../../Game.h"
#include "../entities/Gem.h"
#include "../entities/Weapon.h"
#include "../battle/Preview.h"

GemManager::GemManager() {
  reset();
}

Gem* GemManager::create() {
  if (firstInactive_ == NULL) return;
  
  Gem* gem = getFirstInactive();
  setFirstActive(gem);

  return gem;
}

void GemManager::setFirstActive(Gem* gem) {
  gem->setNextInCollection(firstActive_);
  gem->setNextInContext(NULL);

  firstActive_ = gem;
}

Gem* GemManager::getFirstInactive() {
  Gem* gem = firstInactive_;

  firstInactive_ = firstInactive_->getNextInCollection();

  return gem;
}

void GemManager::remove(Gem* gem) { 
  Gem* previousGem = NULL;
  Gem* currentGem = firstActive_;

  while (currentGem != NULL) {
    if (currentGem == gem) {
      if (previousGem != NULL) {
        previousGem->setNextInCollection(currentGem->getNextInCollection());
      } else {
        firstActive_ = currentGem->getNextInCollection();
      }

      currentGem->setNextInCollection(firstInactive_);
      firstInactive_ = currentGem;
      return;
    }

    previousGem = currentGem;
    currentGem = currentGem->getNextInCollection();
  }
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

  firstInactive_ = &gems_[0];
  firstActive_ = NULL;

  for (int i = 0; i < GEM_MANAGER_SIZE - 2; i++) {
    gems_[i].setNextInCollection(&gems_[i + 1]);
    gems_[i].setNextInContext(NULL);
  }

  gems_[GEM_MANAGER_SIZE - 1].setNextInCollection(NULL);
  gems_[GEM_MANAGER_SIZE - 1].setNextInContext(NULL);
}

void GemManager::render() {
  Gem* currentGem = firstActive_;

  while (currentGem != NULL) {
    currentGem->render();

    currentGem = currentGem->getNextInCollection();
  }
}

void GemManager::moveGemsInObstructedRows(int row1, int row2) {
  Gem* currentGem = firstActive_;

  while (currentGem != NULL) {
    if (currentGem->isFalling()) currentGem->changeRowIfObstructed(row1, row2);

    currentGem = currentGem->getNextInCollection();
  }
}

void GemManager::update() {
  hasClearingGems() ? updateClearing() : updateFalling();
}

void GemManager::updateClearing() {
  int newClearingGemCount = 0;
    
  Gem* currentGem = firstActive_;
  Gem* nextGem = NULL;

  while (currentGem != NULL) {
    if (currentGem->isClearing()) {
      currentGem->update();
      newClearingGemCount++;
    }

    nextGem = currentGem->getNextInCollection();

    if (currentGem->isHidden()) remove(currentGem);
    
    currentGem = nextGem;
  }
  
  clearingGemCount_ = newClearingGemCount;
}

void GemManager::updateFalling() {
  int newClearingGemCount = 0;
  int newFallingGemCount = 0;
  int newBelowPreviewThresholdCount = 0;
  
  if (shouldCreateGems()) preview_.populate(2);
  
  Gem* currentGem = firstActive_;
  Gem* nextGem = NULL;

  while (currentGem != NULL) {
    currentGem->update();

    if (currentGem->isInactive()) {
      if (!hasFallingGems()) {
        currentGem->drop();
        newFallingGemCount++;
        preview_.clear();
      }
    } else if (currentGem->isFalling()) {
      newFallingGemCount++;
      
      if (currentGem->belowPreviewThreshold()) {
        newBelowPreviewThresholdCount++;
      }
    } else if (currentGem->isClearing()) {
      newClearingGemCount++;
    }

    nextGem = currentGem->getNextInCollection();

    if (currentGem->isHidden()) remove(currentGem);
    
    currentGem = nextGem;
  }
  
  clearingGemCount_ = newClearingGemCount;
  fallingGemCount_ = newFallingGemCount;
  belowPreviewThresholdCount_ = newBelowPreviewThresholdCount;
}
