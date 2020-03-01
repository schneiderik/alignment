#include "Preview.h"
#include "../collections/GemManager.h"
#include "../../Game.h"

void Preview::clear() {
  head_ = NULL;
}

void Preview::populate(int num) {
  for (int i = 0; i < num; i++) {
    Gem* gem = game->gems.create();

    gem->init(randomEmptyRow_());
    if (!isEmpty()) gem->setNext(head_);
    head_ = gem;
  }
}

bool Preview::isEmpty() {
  return head_ == NULL;
}

int Preview::randomEmptyRow_() {
  int row = random(0, WEAPON_COUNT);

  return gemExistsInRow_(row) ? randomEmptyRow_() : row;
}

bool Preview::gemExistsInRow_(int row) {  
  Gem* gem = head_;

  while (gem != NULL) {
    if (gem->getRow() == row) return true;
    gem = gem->getNext();
  }

  return false;
}
