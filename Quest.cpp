#include "Quest.h"
#include "Game.h"

const int QUEST_ENEMY_POSITIONS[ENEMY_COUNT][2] = {
  {5, 6},
  {29, 24},
  {53, 6},
  {77, 24},
  {101, 6}
};

void Quest::handleInput(Game& game) {
  if (arduboy.justPressed(A_BUTTON)) { game.goToBattleScreen(); }
}

void Quest::update() {
  if (cursorInterval_ == QUEST_CURSOR_ANIMATION_INTERVAL) {
    if (cursorOffset_ == QUEST_CURSOR_ANIMATION_MAX_OFFSET) {
      cursorVelocity_ = -1;
    }
  
    if (cursorOffset_ == QUEST_CURSOR_ANIMATION_MIN_OFFSET) {
      cursorVelocity_ = 1;
    }

    cursorOffset_ += cursorVelocity_;
    cursorInterval_ = 0;
  }

  cursorInterval_++; 
}

void Quest::renderCursor_(Game& game) {
  sprites.drawOverwrite(
    QUEST_ENEMY_POSITIONS[game.enemy.getType()][0] + QUEST_CURSOR_OFFSET_X,
    QUEST_ENEMY_POSITIONS[game.enemy.getType()][1] - QUEST_CURSOR_OFFSET_Y - cursorOffset_,
    questCursorImage,
    0
  );  
}

void Quest::renderEnemies_(Game& game) {
  for (int i = 0; i < ENEMY_COUNT; i++) {
    sprites.drawOverwrite(
      QUEST_ENEMY_POSITIONS[i][0],
      QUEST_ENEMY_POSITIONS[i][1],
      questSprite,
      game.enemy.getType() <= i ? i : QUEST_GRAVE_INDEX
    );  
  }  
}

void Quest::render(Game& game) {
  renderCursor_(game);
  renderEnemies_(game);
}
