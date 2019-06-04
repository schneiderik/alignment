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
  
  if (cursorInterval_ == QUEST_CURSOR_INTERVAL_MAX) { cursorInterval_ = 0; }

  switch (cursorInterval_ / QUEST_CURSOR_INTERVAL_LENGTH) {
    case 1:
      cursorOffset_ = -1;
      break;
    case 3:
      cursorOffset_ = 1;
      break;
    default:
      cursorOffset_ = 0;
      break;
  };

  cursorInterval_++; 
}

void Quest::render(int currentEnemyType) {
  sprites.drawOverwrite(
    QUEST_ENEMY_POSITIONS[currentEnemyType][0] + QUEST_CURSOR_OFFSET_X,
    QUEST_ENEMY_POSITIONS[currentEnemyType][1] - QUEST_CURSOR_OFFSET_Y - cursorOffset_,
    questCursorImage,
    0
  );
  
  for (int i = 0; i < ENEMY_COUNT; i++) {
    sprites.drawOverwrite(
      QUEST_ENEMY_POSITIONS[i][0],
      QUEST_ENEMY_POSITIONS[i][1],
      questSprite,
      currentEnemyType <= i ? i : QUEST_GRAVE_INDEX
    );  
  }
}
