#include "Battle.h"

void Battle::update(Game& game) {
  
};

void Battle::render(Game& game) {
  for (int i = 0; i < HEARTS_MAX; i++) {  
    sprites.drawOverwrite(
      HEARTS_X + (i * (heartSprite[0] + HEART_OFFSET)),
      HEARTS_Y,
      heartSprite,
      i <= hearts_ ? 0 : 1
    );
  }

  arduboy.fillRect(104, 0, 24, 64);
};

//#include "Game.h"
//
//class Battle {
//  public:
//    Battle(Game* pGame)
//    : pGame_(pGame) {
//      setEnemy(pGame_->getCurrentEnemyType());
//    };
//    
//    setEnemy(int enemyType) {
//      for (int i = 0; i < ENEMY_DATA_LENGTH; i++) {
//        enemy_[i] = ENEMIES[enemyType][i];
//      }
//    }
//
//    reset() {
//      setEnemy(pGame_->getCurrentEnemyType());
//      hearts_ = 3;        
//    }
//    
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
//
//    void render() {      
//    };
//
//  private:
//    Game* pGame_;
//    bool paused_ = false;
//    int currentInterval = 0;
//    int intervalLength = 500;
//    int hearts_ = 3;
//    int enemy_[ENEMY_DATA_LENGTH];
//    int weapons_[WEAPONS_MAX][WEAPON_LENGTH]
//    int preview_[WEAPONS_MAX];
//    int descendingGemCount_ = 0;
//    int descendingGems_[DESCENDING_GEM_MAX][DESCENDING_GEM_LENGTH];
//    void swapWeapons_() {};
//    void moveCursorUp_() {};
//    void moveCursorDown_() {};
//};
