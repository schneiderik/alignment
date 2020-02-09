#include "WeaponManager.h"
#include "Weapon.h"
#include "Gem2.h"

WeaponManager::WeaponManager() {
  for (int i = 0; i < WEAPON_COUNT; i++) weapons[i] = new Weapon(i); 
}

void WeaponManager::update() {
  for (int i = 0; i < WEAPON_COUNT; i++) get(i).update();
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
  
  get(activeIndex).setGemRows(activeIndex);
  get(activeIndex + 1).setGemRows(activeIndex + 1);

  swapSound();
}
