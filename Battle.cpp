#include "Battle.h"
#include "Game.h"

Battle::Battle() {
  weaponPositions_ = new int[WEAPON_COUNT] {0, 1, 2, 3};
  weapons_ = new Weapon[WEAPON_COUNT];

  for (int i = 0; i < WEAPON_COUNT; i++) {
    weapons_[i].setType(i);
  }
}

void Battle::handleInput(Game& game) {
  if (arduboy.justPressed(RIGHT_BUTTON)) { handlePause_(); }
  if (paused_) return;
  if (arduboy.justPressed(A_BUTTON)) { handleSwapWeapons_(); }
  if (arduboy.justPressed(UP_BUTTON)) { handleMoveCursorUp_(); }
  if (arduboy.justPressed(DOWN_BUTTON)) { handleMoveCursorDown_(); }  
}

void Battle::update(Game& game) {
//      if (hearts_ == 0) {
//        pGame_->lose();
//        reset();
//      }
//      
//      // Check if you killed the enemy
//      if (enemy_[ENEMY_DATA_HEALTH] <= 0) {
//        if (enemy_[ENEMY_DATA_TYPE] == LAST_ENEMY) {
//          pGame_->win();
//          reset();
//        } else {
//          pGame_->continueQuest();
//          reset();
//        }
//      }
//
//      // HERE!
//      // Check for gem matches
//      int match[MATCH_LENGTH] = getMatch();
//      
//      if (match[MATCH_TYPE] != MATCH_TYPES::NONE) {
//        battle.increaseScore(match);
//        battle.attackEnemy(match);
//        battle.removeMatch(match);
//      }
//      
//      // Check for overflowed weapons
//      for (int i = 0; i < WEAPONS_MAX; i++) {
//        if (weapons_[i][WEAPON_GEM_COUNT] > WEAPON_GEM_MAX) {
//          hearts_--;
//          weapons_[i][WEAPON_GEM_COUNT] = 0;
//        }
//      } 
//      
//      // Each Interval
//      if (currentInterval >= game.getIntervalLength()) {
//        currentInterval = 0;
//  
//        // Check for descending gems
//        if (descendingGemCount_ == 0) {
//          if (currentGemDelay < GEM_DELAY) {
//            currentGemDelay++;
//          } else {
//            currentGemDelay = 0;
//            battle.descendGems(preview_);
//          }
//        } else {  
//          // Generate new preview if the preview area is clear of descending gems.
//            if (descendingGems_[0][DESCENDING_GEM_POSITION] <= GEM_SIZE * WEAPON_GEM_MAX) {
//            battle.generatePreview();
//          }
//        
//          for (int i = 0; i < descendingGemCount_; i++) {
//            // Check if a descending gem has reached a gem in play
//            if (descendingGems_[i][DESCENDING_GEM_POSITION] <= (weapons_[descendingGems_[i][DESCENDING_GEM_WEAPON]][WEAPON_GEM_COUNT] + 1) * GEM_SIZE) {
//              // If a descending gem has reached a gem in play, add it the weapon.
//              addDescendingGemToWeapon(descendingGems_[i]);
//              // remove gem from descendingGems_
//            } else {
//              // If a descending gem has not reached a gem in play, increment it further down the weapon.
//              descendingGems_[i][DESCENDING_GEM_POSITION] -= DESCENT_INCREMENT;
//            }
//          }
//        } 
//      } else {
//        currentInterval += timeElapsed;
//      }  
};

void Battle::reset() {
  for (int i = 0; i < WEAPON_COUNT; i++) {
    weaponPositions_[i] = i;
    weapons_[i].reset();
  }  
}

void Battle::handlePause_() {
  paused_ = !paused_;
}

void Battle::handleSwapWeapons_() {
  int weapon1, weapon2;

  for (int i = 0; i < WEAPON_COUNT; i++) {
    if (weaponPositions_[i] == cursorIndex_) weapon1 = i;
    if (weaponPositions_[i] == cursorIndex_ + 1) weapon2 = i;
  }
  
  weaponPositions_[weapon1] = cursorIndex_ + 1;
  weaponPositions_[weapon2] = cursorIndex_;
}

void Battle::handleMoveCursorUp_() {
  if (cursorIndex_ > 0) cursorIndex_--;
}

void Battle::handleMoveCursorDown_() {
  if (cursorIndex_ < BATTLE_CURSOR_MAX) cursorIndex_++;
}

void Battle::renderPaused_() {
  if (paused_) {
    sprites.drawOverwrite(
      BATTLE_PAUSED_TEXT_X,
      BATTLE_PAUSED_TEXT_Y,
      pausedTextImage,
      0
    ); 
  }  
}

void Battle::render(Game& game) {
  bool active;
  int position;
  
  game.player.hearts.render(BATTLE_HEARTS_X, BATTLE_HEARTS_Y);
  game.player.score.render(BATTLE_SCORE_X, BATTLE_SCORE_Y);
  game.enemy.render();
  
  for (int i = 0; i < WEAPON_COUNT; i++) {
    active = weaponPositions_[i] == cursorIndex_ || weaponPositions_[i] == cursorIndex_ + 1;
    
    weapons_[i].render(weaponPositions_[i], active);
  }

  renderPaused_();
};
