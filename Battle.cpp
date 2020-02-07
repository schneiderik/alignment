#include "Battle.h"
#include "Gem.h"
#include "WeaponManager.h"
#include "Enemy.h"
#include "Weapon.h"

Battle::Battle() {
  for (int i = 0; i < PREVIEW_GEMS_MAX; i++) previewGems[i] = new Gem();
  for (int i = 0; i < FALLING_GEMS_MAX; i++) fallingGems[i] = new Gem();
}

void Battle::handleInput() {
  if (arduboy.justPressed(RIGHT_BUTTON)) paused = !paused;
  if (paused || isClearing()) return;
  if (arduboy.justPressed(UP_BUTTON)) weapons->decrementActiveIndex();
  if (arduboy.justPressed(DOWN_BUTTON)) weapons->incrementActiveIndex();
  if (arduboy.justPressed(A_BUTTON)) swapWeapons();
}

void Battle::reset() { 
  health = HEALTH_MAX;
  fallingGemCount = 0;
  previewGemCount = 0;
  enemy->reset();
  weapons->reset();
}

void Battle::swapWeapons() {
  Weapon& weapon1 = weapons->get(weapons->activeIndex);
  Weapon& weapon2 = weapons->get(weapons->activeIndex + 1);
  
  for(int i = 0; i < fallingGemCount; i++) {
    Gem& gem = *fallingGems[i];

    if (weapons->activeIndex == gem.row) {
      if (gem.x < gemXOffsets[weapon2.gemCount]) {
        gem.row = weapons->activeIndex + 1;
      }
    } else if (weapons->activeIndex + 1 == gem.row) {
      if (gem.x < gemXOffsets[weapon1.gemCount]) {
        gem.row = weapons->activeIndex;
      }
    }  
  }
  
  weapons->swap(); 
}

void Battle::update() {
  if (paused) return;
  handlePlayerDefeated();
  handleEnemyDefeated();
  weapons->update();
  enemy->update();

  if (!isClearing()) {              
    if (shouldGeneratePreviewGems()) generatePreviewGems();        
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

int Battle::randomUniqueRow() {
  int num = random(0, WEAPON_COUNT);

  bool existing = false;
  
  for (int i = 0; i < previewGemCount; i++) {
    if (previewGems[i]->row == num) existing = true;
  }

  return existing ? randomUniqueRow() : num;
}

bool Battle::isClearing() {
  if (weapons->isClearing()) return true;
  for (int i = 0; i < fallingGemCount; i++) if (fallingGems[i]->isClearing()) return true;
  return false;  
}

bool Battle::shouldGeneratePreviewGems() {
  return previewGemCount == 0 && (fallingGemCount == 0 || fallingGemsBelowPreviewThreshold());
}

void Battle::generatePreviewGem() {
  Gem& previewGem = *previewGems[previewGemCount];

  previewGem.type = random(0, GEM_TYPE_COUNT);
  previewGem.row = randomUniqueRow();
  previewGem.x = PREVIEW_GEM_X;
  previewGem.y = gemYOffsets[previewGem.row];
  previewGemCount++;  
}

void Battle::generatePreviewGems() {
  for (int i = 0; i < PREVIEW_GEMS_MAX; i++) generatePreviewGem();
}

bool Battle::fallingGemsBelowPreviewThreshold() {
  for (int i = 0; i < fallingGemCount; i++) {
    if (fallingGems[i]->x > PREVIEW_THRESHOLD_X) return false;
  }

  return true;
}

bool Battle::shouldDropPreviewGems() {
  return fallingGemCount == 0 && previewGemCount > 0;
}

void Battle::dropPreviewGems() {
  for (int i = 0; i < previewGemCount; i++) {
    addGemToArray(fallingGems, *previewGems[i], fallingGemCount).drop();
  }
  
  previewGemCount = 0;
}

void Battle::handleFullWeapon(Gem& fallingGem) {
  Weapon& weapon = fallingGem.getWeapon();
  
  weapon.clearGems();
  fallingGem.clear();

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
  for(int i = 0; i < fallingGemCount; i++) {
    Gem& gem = *fallingGems[i];

    if (isClearing()) {
      if (gem.isClearing()) gem.update();
    } else {
      gem.update(); 
  
      if (gem.isStacked()) {
        handleGemStack(gem);
        
        if (gem.isStacked()) {
          removeGemFromArray(fallingGems, i, fallingGemCount);
          i--;
        }
      }
  
      if (gem.isPopped() || gem.isCleared()) {
        removeGemFromArray(fallingGems, i, fallingGemCount);
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
  for (int i = 0; i < previewGemCount; i++) previewGems[i]->render();
  for (int i = 0; i < fallingGemCount; i++) fallingGems[i]->render();
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
