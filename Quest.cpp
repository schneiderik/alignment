#include "Quest.h"
#include "Game.h"

const int QUEST_ENEMY_POSITIONS[ENEMY_COUNT][2] = {
  {5, 6},
  {29, 24},
  {53, 6},
  {77, 24},
  {101, 6}
};

void Quest::update(Game& game) {
  if (arduboy.justPressed(A_BUTTON)) { game.setState(GAME_STATES::GAME_STATE_BATTLE); }
  
  if (cursorInterval_ == QUEST_CURSOR_INTERVAL_MAX) {
    if (cursorOffset_ == MAX_CURSOR_ANIMATION_OFFSET) {
      cursorVelocity_ = -1;
    }
  
    if (cursorOffset_ == MIN_CURSOR_ANIMATION_OFFSET) {
      cursorVelocity_ = 1;
    }

    cursorOffset_ += cursorVelocity_;
    cursorInterval_ = 0;
  }

  cursorInterval_++; 
}

void Quest::renderCursor_(Game& game) {
  sprites.drawOverwrite(
    QUEST_ENEMY_POSITIONS[game.enemy.type][0] + QUEST_CURSOR_OFFSET_X,
    QUEST_ENEMY_POSITIONS[game.enemy.type][1] - QUEST_CURSOR_OFFSET_Y - cursorOffset_,
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
      game.enemy.type <= i ? i : QUEST_GRAVE_INDEX
    );  
  }  
}

void Quest::render(Game& game) {
  renderCursor_(game);
  renderEnemies_(game);
}
