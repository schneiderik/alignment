#include "WinView.h"
#include "../../Game.h"
#include "../../Player.h"

void WinView::handleInput() {
  if (arduboy.justPressed(A_BUTTON)) game->goToTitleView();
}

void WinView::handleNavigateFrom() {
  enemy->init(Enemy::SKELETON);
  player->reset();
}

void WinView::render() {
  sprites.drawOverwrite(21, 3, victoryImage, 0);
  sprites.drawOverwrite(6, 33, winTextImage, 0);    
  sprites.drawOverwrite(53, 46, dividerImage, 0);
  renderNumberAlignCenter(player->getScore(), 64, 54, WHITE);
}
