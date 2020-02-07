#include "GemManager.h"
#include "Gem.h"

GemManager::GemManager() {
  for (int i = 0; i < GEM_MAX; i++) gems[i] = new Gem();
}

void GemManager::update() {
  for (int i = 0; i < count; i++) get(i).update();
}

void GemManager::render() {
  for (int i = 0; i < count; i++) get(i).render();
}

void GemManager::reset() {
  count = 0;
}

void GemManager::create() {
  Gem& gem = getNext();

  gem.type = random(0, GEM_TYPE_COUNT);
  gem.row = randomEmptyRow();
  gem.x = PREVIEW_GEM_X;
  gem.y = gemYOffsets[gem.row];
  count++;  
}

void GemManager::create(int num) {
  for (int i = 0; i < num; i++) create();
}

Gem& GemManager::add(Gem& gem) {
  return addGemToArray(gems, gem, count);
}

void GemManager::remove(int i) {
  removeGemFromArray(gems, i, count);
}

Gem& GemManager::get(int i) {
  return *gems[i];
}

Gem& GemManager::getNext() {
  return get(count);
}

bool GemManager::gemExistsInRow(int row) {  
  for (int i = 0; i < count; i++) if (get(i).row == row) return true;

  return false;
}

int GemManager::randomEmptyRow() {
  int row = random(0, WEAPON_COUNT);

  return gemExistsInRow(row) ? randomEmptyRow() : row;
}

bool GemManager::isEmpty() {
  return count == 0;
}

bool GemManager::gemsBelowPreviewThreshold() {
  for (int i = 0; i < count; i++) {
    if (!get(i).belowPreviewThreshold()) return false;
  }

  return true;
}

void GemManager::moveGemsInObstructedRows(int row1, int row2) {
  for(int i = 0; i < count; i++) get(i).changeRowIfObstructed(row1, row2);
}
