//MatchManager::MatchManager() {
//  matches = new int[PUZZLE_WEAPON_COUNT * WEAPON_GEM_MAX];
//  
//  reset();
//}
//
//void MatchManager::reset() {
//  for (int i = 0; i < PUZZLE_WEAPON_COUNT * WEAPON_GEM_MAX; i++) {
//    matches[i] = 0;
//  }
//}
//
//void MatchManager::check(int* gems) {
//  int gem1, gem2;
//
//  resetMatches();
//  
//  for (int i = 0; i < PUZZLE_WEAPON_COUNT; i++) {
//    for (int g = 0; g < weapons_[weaponOrder_[i]].getGemCount(); g++) {
//      gem1 = weapons_[weaponOrder_[i]].getGems()[g].getType();
//      
//      if (i < PUZZLE_WEAPON_COUNT - 1 && g < weapons_[weaponOrder_[i + 1]].getGemCount()) {
//        gem2 = weapons_[weaponOrder_[i + 1]].getGems()[g].getType();
//  
//        if (gem1 == gem2) {
//          matches[(i * WEAPON_GEM_MAX) + g] = 1;
//          matches[((i + 1) * WEAPON_GEM_MAX) + g] = 1;
//        }      
//      }
//    
//      if (g < weapons_[weaponOrder_[i]].getGemCount() - 1) {
//        gem2 = weapons_[weaponOrder_[i]].getGems()[g + 1].getType();
//  
//        if (gem1 == gem2) {
//          matches[(i * WEAPON_GEM_MAX) + g] = 1;
//          matches[(i * WEAPON_GEM_MAX) + g + 1] = 1;
//        }
//      }
//    }
//  }
//}
//

