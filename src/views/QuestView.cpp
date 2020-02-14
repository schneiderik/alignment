#include "QuestView.h"
#include "../../Game.h"
#include "../entities/Enemy.h"

void QuestView::handleInput() {
  if (arduboy.justPressed(A_BUTTON)) {
    game->goToBattleView();
    confirmSound();
  }
}

void QuestView::update() {
  if (arduboy.everyXFrames(INITIAL_GAME_SPEED)) {
    if (cursorOffset > 0) cursorVelocity = -1;
    if (cursorOffset < 0) cursorVelocity = 1;
    cursorOffset += cursorVelocity;
  }  
}

void QuestView::render() {
  renderText();
  renderCursor();
  renderPaths();
  renderEnemies();
}

void QuestView::renderText() {
  sprites.drawOverwrite(32, 2, questText, 0);     
}

void QuestView::renderCursor() {
  sprites.drawOverwrite(
    ENEMY_DATA[game->enemy.type][ENEMY_DATA_QUEST_X] + 8,
    ENEMY_DATA[game->enemy.type][ENEMY_DATA_QUEST_Y] - 4 - cursorOffset,
    questCursorImage,
    0
  );  
}

void QuestView::renderPaths() {
  sprites.drawOverwrite(16, 50, pathImage, 0);
  sprites.drawOverwrite(54, 50, pathReverseImage, 0);
  sprites.drawOverwrite(64, 50, pathImage, 0);
  sprites.drawOverwrite(102, 50, pathReverseImage, 0);  
}

void QuestView::renderEnemies() {
  for (int i = 0; i < ENEMY_COUNT; i++) renderEnemy(i); 
}

void QuestView::renderEnemy(int i) {
  sprites.drawOverwrite(
    ENEMY_DATA[i][ENEMY_DATA_QUEST_X],
    ENEMY_DATA[i][ENEMY_DATA_QUEST_Y],
    questSprite,
    game->enemy.type == i
      ? i
      : i < game->enemy.type
        ? QUEST_SPRITE_GRAVE_INDEX
        : QUEST_SPRITE_MYSTERY_INDEX
  );   
}