#include "QuestView.h"
#include "../../Game.h"

const int QuestView::DATA[Enemy::COUNT][DATA_LENGTH] = {
  {5, 16},
  {29, 31},
  {53, 16},
  {77, 31},
  {101, 16}
};

QuestView::QuestView() {
  bounceAnimation_ = new Animation(
    BOUNCE_ANIMATION_INITIAL_VALUE,
    BOUNCE_ANIMATION_LOWER_LIMIT,
    BOUNCE_ANIMATION_UPPER_LIMIT,
    BOUNCE_ANIMATION_SPEED,
    BOUNCE_ANIMATION_LOOP
  );
}

void QuestView::handleInput() {
  if (arduboy.justPressed(A_BUTTON)) {
    game->goToBattleView();
    confirmSound();
  }
}

void QuestView::update() {
  bounceAnimation_->update();
}

void QuestView::render() {
  renderText_();
  renderCursor_();
  renderPaths_();
  renderEnemies_();
}

void QuestView::renderText_() {
  sprites.drawOverwrite(32, 2, questText, 0);     
}

void QuestView::renderCursor_() {
  sprites.drawOverwrite(
    getXData_(enemy->getType()) + 8,
    getYData_(enemy->getType()) - 4 + bounceAnimation_->getValue(),
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

void QuestView::renderEnemies_() {
  for (int i = 0; i < Enemy::COUNT; i++) renderEnemy_(i); 
}

void QuestView::renderEnemy_(int type) {
  sprites.drawOverwrite(
    getXData_(type),
    getYData_(type),
    questSprite,
    enemy->getType() == type
      ? type
      : type < enemy->getType()
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
