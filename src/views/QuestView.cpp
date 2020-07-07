#include "QuestView.h"

const int QuestView::DATA[ENEMY_COUNT][DATA_LENGTH] = {
  {5, 16},
  {29, 31},
  {53, 16},
  {77, 31},
  {101, 16}
};

void QuestView::init(Game game) {
  bounceAnimation_.init(
    BOUNCE_ANIMATION_INITIAL_VALUE,
    BOUNCE_ANIMATION_LOWER_LIMIT,
    BOUNCE_ANIMATION_UPPER_LIMIT,
    BOUNCE_ANIMATION_SPEED,
    BOUNCE_ANIMATION_LOOP
  );
}

void QuestView::handleInput(Game game) {
  if (arduboy.justPressed(A_BUTTON)) {
    game.goToBattleView();
    game.getAudio().playConfirmSound();
  }
}

void QuestView::update(Game game) {
  bounceAnimation_.update();
}

void QuestView::render(Game game) {
  renderText_();
  renderCursor_(game);
  renderPaths_();
  renderEnemies_(game);
}

void QuestView::renderText_() {
  sprites.drawOverwrite(32, 2, questText, 0);     
}

void QuestView::renderCursor_(Game game) {
  sprites.drawOverwrite(
    getXData_(game.getCurrentEnemy().getType()) + 8,
    getYData_(game.getCurrentEnemy().getType()) - 4 + bounceAnimation_.getValue(),
    questCursorImage,
    0
  );  
}

void QuestView::renderPaths_() {
  sprites.drawOverwrite(16, 50, pathImage, 0);
  sprites.drawOverwrite(54, 50, pathReverseImage, 0);
  sprites.drawOverwrite(64, 50, pathImage, 0);
  sprites.drawOverwrite(102, 50, pathReverseImage, 0);  
}

void QuestView::renderEnemies_(Game game) {
  for (int i = 0; i < Enemy::COUNT; i++) renderEnemy_(i, game); 
}

void QuestView::renderEnemy_(int type, Game game) {
  sprites.drawOverwrite(
    getXData_(type),
    getYData_(type),
    questSprite,
    game.getCurrentEnemy().getType() == type
      ? type
      : type < game.getCurrentEnemy().getType()
        ? GRAVE_INDEX
        : MYSTERY_INDEX
  );   
}

int QuestView::getXData_(int enemyType) {
  return DATA[enemyType][DATA_X];
}

int QuestView::getYData_(int enemyType) {
  return DATA[enemyType][DATA_Y];
}
