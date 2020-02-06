#include "WeaponManager.h"
#include "Weapon.h"

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
  get(activeIndex).swap(get(activeIndex + 1));
  swapSound();
}

bool WeaponManager::isClearing() {
  for (int i = 0; i < WEAPON_COUNT; i++) if (get(i).isClearing()) return true;

  return false;
}
