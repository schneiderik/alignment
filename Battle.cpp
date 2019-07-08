#include "Battle.h"
#include "Game.h"

void Battle::handleInput(Game& game) {
  if (arduboy.justPressed(RIGHT_BUTTON)) { handleRightButtonPress_(); }
  if (paused_) return;
  if (arduboy.justPressed(UP_BUTTON)) { handleUpButtonPress_(); }
  if (arduboy.justPressed(DOWN_BUTTON)) { handleDownButtonPress_(); } 
  if (puzzle_.isWaitingForAnimation()) return;
  if (arduboy.justPressed(A_BUTTON)) { handleAButtonPress_(); }
 
}

void Battle::handleRightButtonPress_() {
  paused_ = !paused_;
}

void Battle::handleAButtonPress_() {
  puzzle_.swapWeapons();
}

void Battle::handleUpButtonPress_() {
  puzzle_.moveCursorUp();
}

void Battle::handleDownButtonPress_() {
  puzzle_.moveCursorDown();
}

void Battle::update(Game& game) {
  if (paused_) return;
  
  puzzle_.update();
  
  if (puzzle_.isWaitingForAnimation()) return;
  
  if (game.player.isDead()) game.goToLoseScreen();
  if (game.enemy.isDead()) game.defeatEnemy(); 
};

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

void Battle::renderEnemyPanel_() {
  arduboy.fillRect(
    BATTLE_ENEMY_PANEL_X,
    BATTLE_ENEMY_PANEL_Y,
    BATTLE_ENEMY_PANEL_WIDTH,
    BATTLE_ENEMY_PANEL_HEIGHT
  ); 
}

void Battle::renderEnemyPortrait_(int type) {
  sprites.drawOverwrite(
    BATTLE_ENEMY_PORTRAIT_X,
    BATTLE_ENEMY_PORTRAIT_Y,
    enemySprite,
    type
  );  
}

void Battle::renderEnemyHealth_() {
  arduboy.fillRect(
    BATTLE_ENEMY_HEALTH_X,
    BATTLE_ENEMY_HEALTH_Y,
    BATTLE_ENEMY_HEALTH_WIDTH,
    BATTLE_ENEMY_HEALTH_HEIGHT,
    0
  );   
}

void Battle::renderEnemy_(int type) {
  renderEnemyPanel_();
  renderEnemyPortrait_(type);
  renderEnemyHealth_();
}

void Battle::render(Game& game) {    
  game.player.hearts.render(BATTLE_HEARTS_X, BATTLE_HEARTS_Y);
  game.player.score.render(BATTLE_SCORE_X, BATTLE_SCORE_Y);
  puzzle_.render();
  renderEnemy_(game.enemy.getType());
  renderPaused_();
};
