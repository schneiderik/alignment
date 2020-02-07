#include "Battle.h"
#include "Game.h"
#include "Gem.h"
#include "WeaponManager.h"
#include "Enemy.h"
#include "Weapon.h"

void Battle::handleInput() {
  if (arduboy.justPressed(RIGHT_BUTTON)) paused = !paused;
  if (paused || isClearing()) return;
  if (arduboy.justPressed(UP_BUTTON)) game->weapons.decrementActiveIndex();
  if (arduboy.justPressed(DOWN_BUTTON)) game->weapons.incrementActiveIndex();
  if (arduboy.justPressed(A_BUTTON)) swapWeapons();
}

void Battle::reset() { 
  health = HEALTH_MAX;
  fallingGems.reset();
  previewGems.reset();
  game->enemy.reset();
  game->weapons.reset();
}

void Battle::swapWeapons() {
  game->weapons.swap();
  fallingGems.moveGemsInObstructedRows(game->weapons.activeIndex, game->weapons.activeIndex + 1);
}

void Battle::update() {
  if (paused) return;
  handlePlayerDefeated();
  handleEnemyDefeated();
  game->weapons.update();
  game->enemy.update();

  if (!isClearing()) {              
    if (shouldGeneratePreviewGems()) previewGems.create(2);        
    if (shouldDropPreviewGems()) dropPreviewGems();       
  }

  dropGems();
}

void Battle::handlePlayerDefeated() {
  if (health == 0) {
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

bool Battle::isClearing() {
  if (game->weapons.isClearing() || fallingGems.isClearing()) return true;
  return false;  
}

bool Battle::shouldGeneratePreviewGems() {
  return previewGems.isEmpty() && (fallingGems.isEmpty() || fallingGems.gemsBelowPreviewThreshold());
}

bool Battle::shouldDropPreviewGems() {
  return fallingGems.isEmpty() && !previewGems.isEmpty();
}

void Battle::dropPreviewGems() {
  for (int i = 0; i < previewGems.count; i++) {
    fallingGems.add(previewGems.get(i)).drop();
  }
  
  previewGems.reset();
}

void Battle::handleFullWeapon(Gem& gem) {
  Weapon& weapon = gem.getWeapon();
  
  weapon.clearGems();
  gem.clear();

  health--;
  loseHeartSound();
}

bool Battle::isMatch(Gem& gem) {
  Weapon& weapon = gem.getWeapon();

  if (weapon.isEmpty()) return false;

  return weapon.getLastGem().type == gem.type;
}

void Battle::handleMatch(Gem& gem) {
  Weapon& weapon = gem.getWeapon();
  
  game->score += 100;
  gem.pop();
  weapon.popLastGem();
  confirmSound();
  game->enemy.takeDamage(5, weapon.type);
}

void Battle::handleNoMatch(Gem& gem) {
  Weapon& weapon = gem.getWeapon();
          
  weapon.addGem(gem);
  game->score += 10; 
}

void Battle::handleGemStack(Gem& gem) {
  Weapon& weapon = gem.getWeapon();

  if (isMatch(gem)) {
    handleMatch(gem);
  } else {
    if (weapon.isFull()) {
      handleFullWeapon(gem);
    } else {
      handleNoMatch(gem);
    }        
  }  
}

void Battle::dropGems() {  
  for(int i = 0; i < fallingGems.count; i++) {
    Gem& gem = fallingGems.get(i);

    if (isClearing()) {
      if (gem.isClearing()) gem.update();
    } else {
      gem.update(); 
  
      if (gem.isStacked()) {
        handleGemStack(gem);
        
        if (gem.isStacked()) {
          fallingGems.remove(i);
          i--;
        }
      }
  
      if (gem.isPopped() || gem.isCleared()) {
        fallingGems.remove(i);
        i--;
      }
    }
  }  
}

void Battle::render() {
  renderTopBar();
  renderNumberAlignRight(game->score, 126, 2, true);
  renderHealth();
  renderPreviewDivider();
  game->enemy.render();
  game->weapons.render();
  previewGems.render();
  fallingGems.render();
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
      i < health ? 0 : 1
    );
  }  
}

void Battle::renderPreviewDivider() {
  arduboy.fillRect(89, 14, 1, 48);
}

void Battle::renderPaused() {
  if (paused) sprites.drawOverwrite(50, 28, pausedTextImage, 0);
}
