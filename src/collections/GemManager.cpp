#include "GemManager.h"
#include "WeaponManager.h"
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

void GemManager::reset() {
  fallingGems_.clear();
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
  fallingGems_.moveGemsInObstructedRows(row1, row2);
}

void GemManager::update() {
  if(!weaponManager->isClearing()) {
    if (preview_.isEmpty() && fallingGems_.belowPreviewThreshold()) {
      preview_.populate(2);
    }

    if (!preview_.isEmpty() && fallingGems_.isEmpty()) {
      fallingGems_.add(preview_.getHead());
      preview_.clear();
    }
  }
  
  Gem* currentGem = firstActive_;
  Gem* nextGem = NULL;

  while (currentGem != NULL) {
    if (!weaponManager->isClearing() || currentGem->isClearing()) {
      currentGem->update();
    }

    nextGem = currentGem->getNextInCollection();

    if (currentGem->isHidden()) remove(currentGem);
    
    currentGem = nextGem;
  }
}
