//#include "GemManager.h"
//
//GemManager::GemManager() {
////  gems_ = new Gem[BATTLE_GEM_MAX];
////  match_ = new int[MATCH_MAX][MATCH_DATA_LENGTH];
////  
////  for (int i = 0; i < BATTLE_GEM_MAX; i++) {
////    gems_[i].set(GEM_EMPTY, WEAPON_TYPE_SWORD);
////  }
//}
//
//void GemManager::render() {  
////  for (int i = 0; i < BATTLE_GEM_MAX; i++) {
////    gems_[i].render(weaponPositions_[gems_[i].getWeaponType()]);
////  }
//}
//
//void GemManager::reset() {
////  for (int i = 0; i < BATTLE_GEM_MAX; i++) {
////    gems_[i].set(WEAPON_TYPE_SWORD, GEM_EMPTY);
////  }
//}
//
//
//void GemManager::swap() {
////  for (int i = 0; i < BATTLE_GEM_MAX; i++) {
////    gemWeaponType = gems_[i].getWeaponType();
////
////    if (gemWeaponType == weapon1 && gems_[i].getXPos() > weapon2MaxX) {
////      gems_[i].setWeaponType(weapon2);
////    }
////    
////    if (gemWeaponType == weapon2 && gems_[i].getXPos() > weapon1MaxX) {
////      gems_[i].setWeaponType(weapon1);
////    }
////  }
//}
//
//bool GemManager::readyForNewGems_() {
////  for (int i = 0; i < BATTLE_GEM_MAX; i++) {
////    if (gems_[i].isEmpty()) continue;
////    if (gems_[i].isInactive()) return false;
////    if (gems_[i].getXPos() >= 77) return false;
////  }
////  
////  return true;
//}
//
//bool GemManager::readyToDropGems_() {
////  for (int i = 0; i < BATTLE_GEM_MAX; i++) {
////    if (gems_[i].isEmpty()) continue;
////    if (gems_[i].isActive()) return false;
////  }
////
////  return true;
//}
//
//bool GemManager::gemShouldStack_(Gem& gem) {
////  if (gem.isEmpty()) return false;
////  if (gem.isInactive()) return false;
////  if (gem.getXPos() > weapons_[gem.getWeaponType()].getMaxX()) return false;
////
////  return true;
//}
//
//void GemManager::generateNewGems_() {
////  int weaponType = random(0, WEAPON_COUNT);
////  int gemType = random(0, GEM_COUNT);
////
////  for (int i = 0; i < BATTLE_GEM_MAX; i++) {
////    if (gems_[i].isEmpty()) {
////      gems_[i].set(gemType, weaponType);
////      return;
////    }
////  }
//}
//
//void GemManager::dropGems_() {
////  for (int i = 0; i < BATTLE_GEM_MAX; i++) {
////    if (gems_[i].isEmpty()) continue;
////    if (gems_[i].isInactive()) gems_[i].activate();
////  }
//}
//
//void GemManager::stackGem_(Game& game, Gem& gem) {
////  int weaponType = gem.getWeaponType();
////  int gemType = gem.getType();
////  
////  Weapon* weapon = weapons_[weaponType];
////  
////  weapon.addGem(gemType);
////  gem.unset();
////  
////  if (weapon.getGemCount() > WEAPON_GEM_MAX)
////    handleWeaponOverflow_(game, weapon);
////
////  matchManager_.check(weapons_);
////  
////  if (matchManager_.) {
//////    game.player.increaseScore(match);
//////    game.enemy.takeDamage(match);
//////    battle.removeMatch(match);
////  }    
//}
//
//void GemManager::handleWeaponOverflow_(Game& game, Weapon& weapon) {
////  game.player.hearts.lose();
////  weapon.clearGems();
//}
