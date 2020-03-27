#include "GemManager.h"
#include "../entities/Gem.h"

GemManager::GemManager() {
  reset();
}

Gem* GemManager::create() {
  if (firstInactive_ == NULL) return;
  
  Gem* gem = firstInactive_;
  firstInactive_ = firstInactive_->getNext();

  return gem;
}

void GemManager::remove(Gem* gem) { 
  gem->setNext(firstInactive_);
  firstInactive_ = gem;
}

void GemManager::reset() {
  firstInactive_ = &gems_[0];

  for (int i = 0; i < GEM_MANAGER_SIZE - 2; i++) {
    gems_[i].setNext(&gems_[i + 1]);
  }

  gems_[GEM_MANAGER_SIZE - 1].setNext(NULL);
}

