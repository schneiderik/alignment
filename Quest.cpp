#include "Quest.h"
#include "Enemy.h"

void Quest::handleInput(int& gameState) {
  if (arduboy.justPressed(A_BUTTON)) {
    gameState = GAME_STATE_BATTLE;
    confirmSound();
  }
}

void Quest::update() {
  if (arduboy.everyXFrames(INITIAL_GAME_SPEED)) {
    if (cursorOffset > 0) cursorVelocity = -1;
    if (cursorOffset < 0) cursorVelocity = 1;
    cursorOffset += cursorVelocity;
  }  
}

void Quest::render() {
  renderText();
  renderCursor();
  renderPaths();
  renderEnemies();
}

void Quest::renderText() {
  sprites.drawOverwrite(32, 2, questText, 0);     
}

void Quest::renderCursor() {
  sprites.drawOverwrite(
    ENEMY_DATA[enemy->type][ENEMY_DATA_QUEST_X] + 8,
    ENEMY_DATA[enemy->type][ENEMY_DATA_QUEST_Y] - 4 - cursorOffset,
    questCursorImage,
    0
  );  
}

void Quest::renderPaths() {
  sprites.drawOverwrite(16, 50, pathImage, 0);
  sprites.drawOverwrite(54, 50, pathReverseImage, 0);
  sprites.drawOverwrite(64, 50, pathImage, 0);
  sprites.drawOverwrite(102, 50, pathReverseImage, 0);  
}

void Quest::renderEnemies() {
  for (int i = 0; i < ENEMY_COUNT; i++) renderEnemy(i); 
}

void Quest::renderEnemy(int i) {
  sprites.drawOverwrite(
    ENEMY_DATA[i][ENEMY_DATA_QUEST_X],
    ENEMY_DATA[i][ENEMY_DATA_QUEST_Y],
    questSprite,
    enemy->type == i
      ? i
      : i < enemy->type
        ? QUEST_SPRITE_GRAVE_INDEX
        : QUEST_SPRITE_MYSTERY_INDEX
  );   
}
