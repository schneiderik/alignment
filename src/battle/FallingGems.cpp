#include "FallingGems.h"
#include "../entities/Gem.h"

void FallingGems::add(Gem* head) {
  head_ = head;
  Gem* currentGem = head_;

  while (currentGem != NULL) {
    currentGem->drop();
    currentGem = currentGem->getNextInContext();
  }
}

void FallingGems::clear() {
  head_ = NULL;
}

bool FallingGems::isEmpty() { return head_ == NULL; }

bool FallingGems::belowPreviewThreshold() {
  Gem* currentGem = head_;

  while (currentGem != NULL) {
    if (!currentGem->belowPreviewThreshold()) return false;

    currentGem = currentGem->getNextInContext();
  }

  return true;
}

void FallingGems::moveGemsInObstructedRows(int row1, int row2) {
  Gem* currentGem = head_;

  while (currentGem != NULL) {
    currentGem->changeRowIfObstructed(row1, row2);

    currentGem = currentGem->getNextInContext();
  }
}
