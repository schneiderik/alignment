//GemManager::GemManager() {
//  gemOrder_ = new int[GEM_MANAGER_GEM_MAX];
//  gems_ = new Gem[GEM_MANAGER_GEM_MAX];
//}
//
//bool GemManager::previewIsEmpty_() {
//  for (int i = 0; i < gemCount_; i++) {
//    if (gems_[i].getXPlusWidth() > x_ + PUZZLE_GEM_PREVIEW_THRESHOLD_X_OFFSET) return false;
//  }
//
//  return true;
//}
//
//void GemManager::populatePreview_() {
//  int weaponType = random(0, PUZZLE_WEAPON_COUNT);
//  
//  gemOrder_[gemCount_] = weaponType;
//  
//  gems_[gemCount_].setType(random(0, GEM_COUNT));
//  gems_[gemCount_].setY(y_ + (gemOrder_[gemCount_] * PUZZLE_WEAPON_HEIGHT) + PUZZLE_GEM_Y_OFFSET);
//  gems_[gemCount_].setX(x_ + PUZZLE_GEM_PREVIEW_X_OFFSET);
//  gems_[gemCount_].setTargetX(x_ + PUZZLE_GEM_PREVIEW_X_OFFSET);
//  gems_[gemCount_].ready();
//
//  gemCount_ = gemCount_ + 1 == PUZZLE_GEM_MAX ? 0 : gemCount_ + 1;
//}
//
//bool GemManager::previewIsReadyToActivate_() {
//  if (gemCount_ == 0) return false;
//  
//  for (int i = 0; i < gemCount_; i++) {
//    if (gems_[i].isActive()) return false;
//  }
//      
//  return true;
//}
//
//void GemManager::activatePreview_() {
//  for (int i = 0; i < gemCount_; i++) {
//    if (gems_[i].isReady()) {
//      gems_[i].setTargetX(weapons_[gemOrder_[i]].getGemsMaxX());
//      gems_[i].activate();
//    }
//  }   
//}
//
//void GemManager::render() {
//  for (int i = 0; i < gemCount_; i++) {
//    gems_[i].render();
//  }
//}
