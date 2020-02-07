#include "Battle.h"
#include "Gem.h"
#include "WeaponManager.h"
#include "Enemy.h"
#include "Weapon.h"

void Battle::handleInput() {
  if (arduboy.justPressed(RIGHT_BUTTON)) paused = !paused;
  if (paused || isClearing()) return;
  if (arduboy.justPressed(UP_BUTTON)) weapons->decrementActiveIndex();
  if (arduboy.justPressed(DOWN_BUTTON)) weapons->incrementActiveIndex();
  if (arduboy.justPressed(A_BUTTON)) swapWeapons();
}

void Battle::reset() { 
  health = HEALTH_MAX;
  fallingGems.reset();
  previewGems.reset();
  enemy->reset();
  weapons->reset();
}

void Battle::swapWeapons() {
  weapons->swap();
  fallingGems.moveGemsInObstructedRows(weapons->activeIndex, weapons->activeIndex + 1);
}

void Battle::update() {
  if (paused) return;
  handlePlayerDefeated();
  handleEnemyDefeated();
  weapons->update();
  enemy->update();

  if (!isClearing()) {              
    if (shouldGeneratePreviewGems()) previewGems.create(2);        
    if (shouldDropPreviewGems()) dropPreviewGems();       
  }

  dropGems();
}

void Battle::handlePlayerDefeated() {
  if (health == 0) {
    gameState = GAME_STATE_LOSE; 
    reset(); 
  }
}

void Battle::handleEnemyDefeated() {
  if (enemy->health <= 0) {
    if (enemy->type == LAST_ENEMY) {
      gameState = GAME_STATE_WIN;
    } else { 
      enemy->set(enemy->type + 1);
      gameState = GAME_STATE_QUEST;
    }
    reset();
  }
}

bool Battle::isClearing() {
  if (weapons->isClearing() || fallingGems.isClearing()) return true;
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
  
  score += 100;
  gem.pop();
  weapon.popLastGem();
  confirmSound();
  enemy->takeDamage(5, weapon.type);
}

void Battle::handleNoMatch(Gem& gem) {
  Weapon& weapon = gem.getWeapon();
          
  weapon.addGem(gem);
  score += 10; 
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
  renderNumberAlignRight(score, 126, 2, true);
  renderHealth();
  renderPreviewDivider();
  enemy->render();
  weapons->render();
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
