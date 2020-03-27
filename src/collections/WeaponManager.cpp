#include "WeaponManager.h"
#include "../entities/Weapon.h"

WeaponManager::WeaponManager() {
  for (int i = 0; i < Weapon::COUNT; i++) weapons_[i] = new Weapon(i); 
}

void WeaponManager::update() {
  if (isClearing_()) {
    updateClearingWeapons_();
  } else {
    updateWeapons_();
    if (isReadyToPopulatePreview_()) populatePreviewGems_();
    if (isReadyToDropPreview_()) dropPreviewGems_();
  }
}

void WeaponManager::updateWeapons_() {
  for (int i = 0; i < Weapon::COUNT; i++) weapons_[i]->update();
}

void WeaponManager::updateClearingWeapons_() {
  for (int i = 0; i < Weapon::COUNT; i++) {
    if (weapons_[i]->isClearing()) weapons_[i]->update();
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
  if (isClearing_()) return;
  if (cursor_ == CURSOR_MAX) return;

  cursor_++;
  moveSound();
}

void WeaponManager::decrementCursor() {
  if (isClearing_()) return;
  if (cursor_ == CURSOR_MIN) return;

  cursor_--;  
  moveSound();
}

void WeaponManager::swap() { 
  if (isClearing_()) return;

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

void WeaponManager::slashRandomWeapon() {
  Weapon* weapon = getRandomWeapon_();

  if (weapon->getLastGemInStack() == NULL) {
    slashRandomWeapon();
  } else {
    weapon->slashLastGem();
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

bool WeaponManager::isReadyToPopulatePreview_() { 
  for (int i = 0; i < Weapon::COUNT; i++) {
    if (!weapons_[i]->previewIsEmpty()) return false;
  }

  return true;
}

bool WeaponManager::isReadyToDropPreview_() { 
  for (int i = 0; i < Weapon::COUNT; i++) {
    if (weapons_[i]->hasFallingGem()) return false;
  }

  return true;
}

bool WeaponManager::isClearing_() { 
  for (int i = 0; i < Weapon::COUNT; i++) {
    if (weapons_[i]->isClearing()) return true;
  }

  return false;
}

bool WeaponManager::isActiveWeapon_(int i) {
  int order = weapons_[i]->getOrder();
  return order == cursor_ || order == cursor_ + 1;
}
