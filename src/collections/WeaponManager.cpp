#include "WeaponManager.h"
#include "../entities/Weapon.h"

WeaponManager::WeaponManager() {
  for (int i = 0; i < Weapon::COUNT; i++) weapons_[i] = new Weapon(i); 
}

void WeaponManager::update() {
  initNextState_();

  if (!state_.isClearing) {
    if (state_.isReadyToPopulatePreview) populatePreviewGems_();
    if (state_.isReadyToDropPreview) dropPreviewGems_();
  }

  updateWeapons_();

  applyNextState_();
}

void WeaponManager::initNextState_() {
  nextState_.isReadyToPopulatePreview = true;  
  nextState_.isReadyToDropPreview = true;  
  nextState_.hasStackedGems = false;
  nextState_.isClearing = false;
}

void WeaponManager::applyNextState_() {
  state_.isReadyToPopulatePreview = nextState_.isReadyToPopulatePreview;  
  state_.isReadyToDropPreview = nextState_.isReadyToDropPreview;  
  state_.hasStackedGems = nextState_.hasStackedGems;
  state_.isClearing = nextState_.isClearing;
}

void WeaponManager::updateWeapons_() {
  for (int i = 0; i < Weapon::COUNT; i++) {
    if (!state_.isClearing || (state_.isClearing && weapons_[i]->isClearing())) {
      weapons_[i]->update();
    }

    if (!weapons_[i]->previewIsEmpty()) nextState_.isReadyToPopulatePreview = false;  
    if (weapons_[i]->hasFallingGem()) nextState_.isReadyToDropPreview = false;  
    if (!weapons_[i]->isEmpty()) nextState_.hasStackedGems = true;
    if (weapons_[i]->isClearing()) nextState_.isClearing = true;
  }
}

void WeaponManager::render() {
  for (int i = 0; i < Weapon::COUNT; i++) weapons_[i]->render(isActiveWeapon_(i));
}

void WeaponManager::reset() {
  cursor_ = CURSOR_MIN;
  for (int i = 0; i < Weapon::COUNT; i++) weapons_[i]->reset(i);
}

void WeaponManager::incrementCursor() {
  if (state_.isClearing) return;
  if (cursor_ == CURSOR_MAX) return;

  cursor_++;
  moveSound();
}

void WeaponManager::decrementCursor() {
  if (state_.isClearing) return;
  if (cursor_ == CURSOR_MIN) return;

  cursor_--;  
  moveSound();
}

void WeaponManager::swap() { 
  if (state_.isClearing) return;

  Weapon* weapon1 = getWeaponAtIndex_(cursor_);
  Weapon* weapon2 = getWeaponAtIndex_(cursor_ + 1);

  int tmpOrder = weapon1->getOrder();
  weapon1->setOrder(weapon2->getOrder());
  weapon2->setOrder(tmpOrder);

  Gem* tmpPreviewGem = weapon1->getPreviewGem();
  weapon1->setPreviewGem(weapon2->getPreviewGem());
  weapon2->setPreviewGem(tmpPreviewGem);

  bool weapon1Unobstructed = weapon1->fallingGemAboveX(weapon2->getEndOfRowX());
  bool weapon2Unobstructed = weapon2->fallingGemAboveX(weapon1->getEndOfRowX());

  if (weapon1Unobstructed && weapon2Unobstructed) {
    Gem* tmpFallingGem = weapon1->getFallingGem();
    weapon1->setFallingGem(weapon2->getFallingGem());
    weapon2->setFallingGem(tmpFallingGem);
  }

  swapSound();
}

Weapon* WeaponManager::getWeaponAtIndex_(int order) {
  for (int i = 0; i < Weapon::COUNT; i++) {
    if (weapons_[i]->getOrder() == order) return weapons_[i];
  }
}

Weapon* WeaponManager::getRandomWeapon_() {
  return weapons_[random(0, Weapon::COUNT)];
}

Gem* WeaponManager::popLastGemOfRandomWeapon() {
  if (!state_.hasStackedGems) return NULL;

  Weapon* weapon = getRandomWeapon_();

  if (weapon->getLastGemInStack() == NULL) {
    return popLastGemOfRandomWeapon();
  } else {
    return weapon->popLastGem();
  }
}

void WeaponManager::dropPreviewGems_() {
  for (int i = 0; i < Weapon::COUNT; i++) weapons_[i]->dropPreviewGem();
}

void WeaponManager::populatePreviewGems_() {
  for (int i = 0; i < 2; i++) populatePreviewGemForRandomWeapon_();
}

void WeaponManager::populatePreviewGemForRandomWeapon_() {
  Weapon* weapon = getRandomWeapon_();

  if (weapon->hasPreviewGem()) {
    populatePreviewGemForRandomWeapon_();
  } else {
    weapon->createPreviewGem();
  }
}

bool WeaponManager::isActiveWeapon_(int i) {
  int order = weapons_[i]->getOrder();
  return order == cursor_ || order == cursor_ + 1;
}
