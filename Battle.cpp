#include "Battle.h"
#include "Game.h"
#include "WeaponManager.h"
#include "Enemy.h"
#include "Weapon.h"

void Battle::handleInput() {
  if (arduboy.justPressed(RIGHT_BUTTON)) paused = !paused;
  if (paused || game->gems.hasClearingGems()) return;
  if (arduboy.justPressed(UP_BUTTON)) game->weapons.decrementActiveIndex();
  if (arduboy.justPressed(DOWN_BUTTON)) game->weapons.incrementActiveIndex();
  if (arduboy.justPressed(A_BUTTON)) swapWeapons();
}

void Battle::reset() { 
  game->health = HEALTH_MAX;
  game->gems.reset();
  game->enemy.reset();
  game->weapons.reset();
}

void Battle::swapWeapons() {
  game->weapons.swap();
  game->gems.moveGemsInObstructedRows(game->weapons.activeIndex, game->weapons.activeIndex + 1);
}

void Battle::update() {
  if (paused) return;
  handlePlayerDefeated();
  handleEnemyDefeated();
  game->weapons.update();
  game->enemy.update();
  game->gems.update();
}

void Battle::handlePlayerDefeated() {
  if (game->health == 0) {
    game->goToLose(); 
    reset(); 
  }
}

void Battle::handleEnemyDefeated() {
  if (game->enemy.health <= 0) {
    if (game->enemy.type == LAST_ENEMY) {
      game->goToWin();
    } else { 
      game->enemy.set(game->enemy.type + 1);
      game->goToQuest();
    }
    reset();
  }
}

void Battle::render() {
  renderTopBar();
  renderNumberAlignRight(game->score, 126, 2, true);
  renderHealth();
  renderPreviewDivider();
  game->enemy.render();
  game->weapons.render();
  game->gems.render();
  renderPaused();
}

void Battle::renderTopBar() {
  arduboy.fillRect(0, 0, 128, 10);
}

void Battle::renderHealth() {
  for (int i = 0; i < HEALTH_MAX; i++) {  
    sprites.drawErase(
      2 + (i * (heartSprite[0] + 1)),
      2,
      heartSprite,
      i < game->health ? 0 : 1
    );
  }  
}

void Battle::renderPreviewDivider() {
  arduboy.fillRect(89, 14, 1, 48);
}

void Battle::renderPaused() {
  if (paused) sprites.drawOverwrite(50, 28, pausedTextImage, 0);
}
