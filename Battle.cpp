#include "Battle.h"
#include "Game.h"

Battle::Battle() {
  
}

void Battle::update(Game& game) {
  
};



void Battle::renderScore_(unsigned long int score) {

}

void Battle::render(Game& game) {
  renderHearts_();
  renderScore_(game.getScore());
  enemy_.render();
};

void Battle::setEnemy(int enemyType) {
  enemy_ = new Enemy(enemyType);
};

//    void update() {
//      if (paused_) {
//        if (arduboy.justPressed(RIGHT_BUTTON)) { paused_ = false; }
//      } else {
//        if (arduboy.justPressed(RIGHT_BUTTON)) { paused_ = true; }
//        if (arduboy.justPressed(A_BUTTON)) { swapWeapons_(); }
//        if (arduboy.justPressed(UP_BUTTON)) { moveCursorUp_(); }
//        if (arduboy.justPressed(DOWN_BUTTON)) { moveCursorDown_(); }
//      }
//
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
//    };
