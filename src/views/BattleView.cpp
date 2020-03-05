#include "BattleView.h"
#include "../../Game.h"
#include "../collections/WeaponManager.h"
#include "../entities/Enemy.h"
#include "../entities/Weapon.h"

void BattleView::handleInput() {
  if (arduboy.justPressed(RIGHT_BUTTON)) paused = !paused;
  if (paused || game->weapons.isClearing()) return;
  if (arduboy.justPressed(UP_BUTTON)) game->weapons.decrementActiveIndex();
  if (arduboy.justPressed(DOWN_BUTTON)) game->weapons.incrementActiveIndex();
  if (arduboy.justPressed(A_BUTTON)) {
    game->weapons.swap();
    game->gems.moveGemsInObstructedRows(game->weapons.activeIndex, game->weapons.activeIndex + 1);
  }
}

void BattleView::update() {
  if (paused) return;
  game->handlePlayerDefeated();
  game->handleEnemyDefeated();
  game->weapons.update();
  game->enemy.update();
  game->gems.update();
}

void BattleView::render() {
  renderTopBar();
  renderNumberAlignRight(game->score, 126, 2, BLACK);
  renderHealth();
  renderPreviewDivider();
  game->enemy.render();
  game->weapons.render();
  game->gems.render();
  renderPaused();
}

void BattleView::renderTopBar() {
  arduboy.fillRect(0, 0, 128, 10);
}

void BattleView::renderHealth() {
  for (int i = 0; i < HEALTH_MAX; i++) {  
    sprites.drawErase(
      2 + (i * (heartSprite[0] + 1)),
      2,
      heartSprite,
      i < game->health ? 0 : 1
    );
  }  
}

void BattleView::renderPreviewDivider() {
  arduboy.fillRect(89, 14, 1, 48);
}

void BattleView::renderPaused() {
  if (paused) sprites.drawOverwrite(50, 28, pausedTextImage, 0);
}
