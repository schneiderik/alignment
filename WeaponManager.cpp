#include "WeaponManager.h"
#include "Weapon.h"

WeaponManager::WeaponManager() {
  for (int i = 0; i < WEAPON_COUNT; i++) weapons[i] = new Weapon(i); 
}

void WeaponManager::update() {
  for (int i = 0; i < WEAPON_COUNT; i++) get(i).update();
}

void WeaponManager::render(int activeIndex) {
  for (int i = 0; i < WEAPON_COUNT; i++) get(i).render(i == activeIndex || i == activeIndex + 1);
}

Weapon& WeaponManager::get(int i) {
  return *weapons[i]; 
}

bool WeaponManager::isClearing() {
  for (int i = 0; i < WEAPON_COUNT; i++) if (get(i).isClearing()) return true;

  return false;
}
