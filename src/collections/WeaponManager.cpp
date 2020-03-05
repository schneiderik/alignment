#include "WeaponManager.h"
#include "../entities/Weapon.h"

WeaponManager::WeaponManager() {
  for (int i = 0; i < WEAPON_COUNT; i++) weapons[i] = new Weapon(i); 
}

void WeaponManager::update() {
  state_ = STATE_ACTIVE;

  for (int i = 0; i < WEAPON_COUNT; i++) {
    Weapon& weapon = get(i);

    weapon.update();

    if (weapon.isClearing()) state_ = STATE_CLEARING;
  }
}

void WeaponManager::render() {
  for (int i = 0; i < WEAPON_COUNT; i++) get(i).render(i == activeIndex || i == activeIndex + 1);
}

void WeaponManager::reset() {
  activeIndex = ACTIVE_INDEX_MIN;
  for (int i = 0; i < WEAPON_COUNT; i++) get(i).reset(i);
}

Weapon& WeaponManager::get(int i) {
  return *weapons[i]; 
}

void WeaponManager::incrementActiveIndex() {
  if (activeIndex < ACTIVE_INDEX_MAX) {
    activeIndex++;
    moveSound();
  }
}

void WeaponManager::decrementActiveIndex() {
  if (activeIndex > ACTIVE_INDEX_MIN) {
    activeIndex--;  
    moveSound();
  }  
}

void WeaponManager::swap() { 
  Weapon* weaponPtr = weapons[activeIndex + 1];
  weapons[activeIndex + 1] = weapons[activeIndex];
  weapons[activeIndex] = weaponPtr;
  swapSound();
}

bool WeaponManager::isClearing() { return state_ == STATE_CLEARING; }
bool WeaponManager::isActive() { return state_ == STATE_ACTIVE; }
