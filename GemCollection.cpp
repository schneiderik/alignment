#include "GemCollection.h"
#include "Gem2.h"

GemCollection::GemCollection() {
  firstAvailable_ = &gems_[0];

  for (int i = 0; i < GEM_COLLECTION_SIZE - 1; i++) {
    gems_[i].setNext(&gems_[i + 1]);
  }

  gems_[GEM_COLLECTION_SIZE - 1].setNext(NULL);
}

Gem2& GemCollection::create() {
  if (firstAvailable_ == NULL) return;
  
  Gem2* newGem = firstAvailable_;
  firstAvailable_ = newGem->getNext();

  newGem->init(randomEmptyRow());

  return *newGem;
}

bool GemCollection::gemExistsInRow(int row) {  
  for (int i = 0; i < GEM_COLLECTION_SIZE; i++) {
    Gem2& gem = gems_[i];
    if (gem.isInactive() && gem.getRow() == row) return true;
  }

  return false;
}

int GemCollection::randomEmptyRow() {
  int row = random(0, WEAPON_COUNT);

  return gemExistsInRow(row) ? randomEmptyRow() : row;
}

void GemCollection::update() {
  clearingGemCount_ = 0;
  fallingGemCount_ = 0;
  inactiveGemCount_ = 0;
  
  for (int i = 0; i < GEM_COLLECTION_SIZE; i++) {
    Gem2& gem = gems_[i];
    
    if (gem.update()) {
      if (gem.isInactive()) {
        inactiveGemCount_++;
      } else if (gem.isFalling()) {
        fallingGemCount_++;
      } else if (gem.isClearing()) {
        clearingGemCount_++;
      }
    } else {
      gem.setNext(firstAvailable_);
      firstAvailable_ = &gem;      
    }
  }
}
