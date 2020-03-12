#include "Preview.h"
#include "../collections/GemManager.h"

void Preview::clear() {
  head_ = NULL;
}

Gem* Preview::getHead() {
  return head_;
}

void Preview::populate(int num) {
  for (int i = 0; i < num; i++) populate_();
}

bool Preview::isEmpty() {
  return head_ == NULL;
}

void Preview::populate_() {
  Gem* gem = gemManager->create();

  gem->init(randomEmptyRow_());
  gem->setNextInContext(head_);

  head_ = gem;
}

int Preview::randomEmptyRow_() {
  int row = random(0, Weapon::COUNT);

  return gemExistsInRow_(row) ? randomEmptyRow_() : row;
}

bool Preview::gemExistsInRow_(int row) {  
  Gem* gem = head_;

  while (gem != NULL) {
    if (gem->getRow() == row) return true;
    gem = gem->getNextInContext();
  }

  return false;
}
