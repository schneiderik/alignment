#include "Weapon.h";
#include "Gem.h";

Weapon::Weapon(int i) {
  type = i;
  y = weaponYOffsets[i];
  empty();

  for (int i = 0; i < WEAPON_GEMS_MAX; i++) {
    gems[i] = new Gem();
  }
}

Weapon& Weapon::operator=(const Weapon& weapon) {
  if (this != &weapon) {
    type = weapon.type;
    y = weapon.y;
    gemCount = weapon.gemCount;
    stackCount = weapon.stackCount;
  }
  return *this;
}

bool Weapon::isFull() {
  return stackCount == WEAPON_GEMS_MAX;
}

void Weapon::addGem(Gem& gem) {
  getNextGem() = gem;
  gemCount++;
  stackCount++;
}

Gem& Weapon::getGem(int i) {
  return *gems[i];
}

Gem& Weapon::getLastGem() {
  return getGem(stackCount - 1);
}

Gem& Weapon::getNextGem() {
  return getGem(stackCount);
}

void Weapon::popLastGem() {
  getLastGem().pop();
  stackCount--;
}

void Weapon::clearGems() {
  for (int i = 0; i < gemCount; i++) getGem(i).clear(); 
  stackCount = 0;
}

bool Weapon::isClearing() {
  for (int i = 0; i < gemCount; i++) if (getGem(i).isClearing()) return true;

  return false;
}

void Weapon::empty() {
  gemCount = 0;
  stackCount = 0;
}

void Weapon::render(bool active) {
  renderIcon(active);
  renderDivider();
  renderGems();
}

void Weapon::renderIcon(bool active) {
  if (active) {
    arduboy.fillRect(0, y, 12, 12); 
    sprites.drawErase(2, y + 2, weaponSprite, type);  
  } else {
    sprites.drawOverwrite(2, y + 2, weaponSprite, type);    
  }  
}

void Weapon::renderDivider() {
  arduboy.fillRect(14, y + 1, 1, 10);
}

void Weapon::renderGems() {
  for (int i = 0; i < gemCount; i++) getGem(i).render(); 
}

void Weapon::swap(Weapon& otherWeapon) {  
  int order1 = getOrder();
  int order2 = otherWeapon.getOrder(); 

  *tmpWeapon = otherWeapon;
  otherWeapon = *this;
  *this = *tmpWeapon;

  for (int i = 0; i < WEAPON_GEMS_MAX; i++) {
    *tmpGem = *otherWeapon.gems[i];
    *otherWeapon.gems[i] = *gems[i];
    *gems[i] = *tmpGem;

    gems[i]->row = order1;
    otherWeapon.gems[i]->row = order2;
  }
}

int Weapon::getOrder() {
  for (int i = 0; i < WEAPON_COUNT; i++) {
    if (type == weapons[i]->type) return i;
  }
}

int Weapon::endOfRowX() {
  return gemXOffsets[gemCount];
}

void Weapon::reset(int order) {
  type = order;
  y = weaponYOffsets[order];
  empty();
}

void Weapon::update() {
  updateY();
  updateGems();
}

void Weapon::updateY() {
  int order = getOrder();
  
  if (y != weaponYOffsets[order]) y += y < weaponYOffsets[order] ? 3 : -3;
}

void Weapon::updateGems() {
  for (int i = 0; i < gemCount; i++) {
    Gem& gem = getGem(i);
    
    gem.update();

    if (gem.isPopped() || gem.isCleared()) {
      removeGemFromArray(gems, i, gemCount);
      i--;
    }
  }
}
