//MatchManager::MatchManager() {
//  matches_ = new Match[MATCH_MAX];
//}
//
//int MatchManager::get(Weapon* weapons) {
//  int gemType1, gemType2;
//  
//  for (int gemIndex = 0; gemIndex < WEAPON_GEM_MAX; gemIndex++) {
//    for (int weaponType = 0; weaponType < WEAPON_COUNT; weaponType++) {
//      clearMatches();
//      
//      matches_[matchesLength_][0] = weaponType;
//      matches_[matchesLegnth_][1] = gemIndex;
//      matchesLength_++:
//      
//      checkNeighborsForMatches(weaponType, gemIndex);
//
//      if (matchesLength_ > 0) {
//        for (int matchIndex = 0; matchIndex < MATCHES_MAX; matchIndex++) {
//          int* match = matches_[matchIndex];
//          
//          if (match[MATCH_DATA_WEAPON_TYPE] != MATCH_EMPTY) {
//            int weaponType = match[MATCH_DATA_WEAPON_TYPE];
//            int gemIndex = match[MATCH_DATA_GEM_INDEX];
//            
//            weapons_[weaponType].removeGem(gemIndex);
//          }
//        }
//      }
//    }
//  }
//}
//
//int Battle::checkNeighborsForMatches(int weaponType, int gemIndex) {
//  int gemType1 = weapons_[x].getGems()[y];
//
//  if (x > 0) checkNeighborForMatch(gemType1, x - 1, y);
//  if (x < WEAPON_COUNT - 1) checkNeighborForMatch(gemType1, x + 1, y);
//  if (y > 0) checkNeighborForMatch(gemType1, x, y - 1);
//  if (x < weapons_[x].getGemCount() - 1) checkNeighborForMatch(gemType1, x, y + 1);
//}
//
//void Battle::checkNeighborForMatch(int gemType1, int x, int y) {
//  gemType2 = weapons_[x].getGems()[y];
//  
//  if (gemType1 == gemType2) {
//    matches_[matchesLength_][MATCHES_DATA_X] = x;
//    matches_[matchesLength_][MATCHES_DATA_Y] = y;
//    matchesLength_++;
//  }
//}
//
//void Battle::clearMatches() {
//  matchesLength_ = 0;
//}
