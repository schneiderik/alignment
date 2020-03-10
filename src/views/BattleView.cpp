#include "BattleView.h"
#include "../../Game.h"
#include "../../Player.h"
#include "../../Enemy.h"
#include "../collections/WeaponManager.h"
#include "../entities/Weapon.h"

void BattleView::handleInput() {
  if (arduboy.justPressed(RIGHT_BUTTON)) paused = !paused;
  if (paused || weaponManager->isClearing()) return;
  if (arduboy.justPressed(UP_BUTTON)) weaponManager->decrementActiveIndex();
  if (arduboy.justPressed(DOWN_BUTTON)) weaponManager->incrementActiveIndex();
  if (arduboy.justPressed(A_BUTTON)) {
    weaponManager->swap();
    gemManager->moveGemsInObstructedRows(weaponManager->activeIndex, weaponManager->activeIndex + 1);
  }
}

void BattleView::update() {
  if (paused) return;
  player->update();
  enemy->update();
  weaponManager->update();
  gemManager->update();
}

void BattleView::render() {
  renderTopBar();
  renderNumberAlignRight(player->getScore(), 126, 2, BLACK);
  renderHealth();
  renderPreviewDivider();
  enemy->render();
  weaponManager->render();
  gemManager->render();
  renderPaused();
}

void BattleView::reset() {
  player->resetHealth();
  gemManager->reset();
  weaponManager->reset();
}

void BattleView::renderTopBar() {
  arduboy.fillRect(0, 0, 128, 10);
}

void BattleView::renderHealth() {
  for (int i = 0; i < Player::HEALTH_MAX; i++) {  
    sprites.drawErase(
      2 + (i * (heartSprite[0] + 1)),
      2,
      heartSprite,
      i < player->getHealth() ? 0 : 1
    );
  }  
}

void BattleView::renderPreviewDivider() {
  arduboy.fillRect(89, 14, 1, 48);
}

void BattleView::renderPaused() {
  if (paused) sprites.drawOverwrite(50, 28, pausedTextImage, 0);
}
