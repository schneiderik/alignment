#include "global.h"
#include "Gem.h"
#include "Weapon.h"
#include "Enemy.h"
#include "WeaponManager.h"
#include "Title.h"
#include "Info.h"
#include "Quest.h"
#include "Win.h"
#include "Lose.h"

//////////////////////////////
// GLOBAL VARIABLES
//////////////////////////////

int gameSpeed = INITIAL_GAME_SPEED;
int health = HEALTH_MAX;
int paused = false;
int previewGemCount = 0;
int fallingGemCount = 0;

Title title;
Info info;
Quest quest;
Win win;
Lose lose;



//////////////////////////////
// SETUP
//////////////////////////////

void setup() {
  arduboy.initRandomSeed();
  arduboy.begin();
  arduboy.setFrameRate(FPS);

  enemy = new Enemy();
  weapons = new WeaponManager();
  for (int i = 0; i < PREVIEW_GEMS_MAX; i++) previewGems[i] = new Gem();
  for (int i = 0; i < FALLING_GEMS_MAX; i++) fallingGems[i] = new Gem();
    
  arduboy.clear();
}



//////////////////////////////
// HANDLE INPUT
//////////////////////////////

void resetBattle() { 
  health = HEALTH_MAX;
  fallingGemCount = 0;
  previewGemCount = 0;
  enemy->reset();
  weapons->reset();
}

void swapWeapons() {
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

void handleInput() {
  switch (gameState) {
    case GAME_STATE_TITLE:
      title.handleInput();   
      break;
    case GAME_STATE_INFO:
      info.handleInput();
      break;
    case GAME_STATE_QUEST:
      quest.handleInput();
      break;
    case GAME_STATE_BATTLE:
      if (arduboy.justPressed(RIGHT_BUTTON)) paused = !paused;
      if (paused || isClearing()) return;
      if (arduboy.justPressed(UP_BUTTON)) weapons->decrementActiveIndex();
      if (arduboy.justPressed(DOWN_BUTTON)) weapons->incrementActiveIndex();
      if (arduboy.justPressed(A_BUTTON)) swapWeapons();
      break;
    case GAME_STATE_WIN:
      win.handleInput();
    case GAME_STATE_LOSE:
      lose.handleInput();
      break;
  }  
}



//////////////////////////////
// UPDATE
//////////////////////////////

void handlePlayerDefeated() {
  if (health == 0) {
    gameState = GAME_STATE_LOSE; 
    resetBattle(); 
  }
}

void handleEnemyDefeated() {
  if (enemy->health <= 0) {
    if (enemy->type == LAST_ENEMY) {
      gameState = GAME_STATE_WIN;
    } else { 
      enemy->set(enemy->type + 1);
      gameState = GAME_STATE_QUEST;
    }
    resetBattle();
  }
}

int randomUniqueRow() {
  int num = random(0, WEAPON_COUNT);

  bool existing = false;
  
  for (int i = 0; i < previewGemCount; i++) {
    if (previewGems[i]->row == num) existing = true;
  }

  return existing ? randomUniqueRow() : num;
}

bool isClearing() {
  if (weapons->isClearing()) return true;
  for (int i = 0; i < fallingGemCount; i++) if (fallingGems[i]->isClearing()) return true;
  return false;  
}

bool shouldGeneratePreviewGems() {
  return previewGemCount == 0 && (fallingGemCount == 0 || fallingGemsBelowPreviewThreshold());
}

void generatePreviewGem() {
  Gem& previewGem = *previewGems[previewGemCount];

  previewGem.type = random(0, GEM_TYPE_COUNT);
  previewGem.row = randomUniqueRow();
  previewGem.x = PREVIEW_GEM_X;
  previewGem.y = gemYOffsets[previewGem.row];
  previewGemCount++;  
}

void generatePreviewGems() {
  for (int i = 0; i < PREVIEW_GEMS_MAX; i++) generatePreviewGem();
}

bool fallingGemsBelowPreviewThreshold() {
  for (int i = 0; i < fallingGemCount; i++) {
    if (fallingGems[i]->x > PREVIEW_THRESHOLD_X) return false;
  }

  return true;
}

bool shouldDropPreviewGems() {
  return fallingGemCount == 0 && previewGemCount > 0;
}

void dropPreviewGems() {
  for (int i = 0; i < previewGemCount; i++) {
    addGemToArray(fallingGems, *previewGems[i], fallingGemCount).drop();
  }
  
  previewGemCount = 0;
}

void handleFullWeapon(Gem& fallingGem) {
  Weapon& weapon = fallingGem.getWeapon();
  
  weapon.clearGems();
  fallingGem.clear();

  health--;
  loseHeartSound();
}

bool isMatch(Gem& gem) {
  Weapon& weapon = gem.getWeapon();

  if (weapon.isEmpty()) return false;

  return weapon.getLastGem().type == gem.type;
}

void handleMatch(Gem& gem) {
  Weapon& weapon = gem.getWeapon();
  
  score += 100;
  gem.pop();
  weapon.popLastGem();
  confirmSound();
  enemy->takeDamage(5, weapon.type);
}

void handleNoMatch(Gem& gem) {
  Weapon& weapon = gem.getWeapon();
          
  weapon.addGem(gem);
  score += 10; 
}

void handleGemStack(Gem& gem) {
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

void dropGems() {  
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

void update() {
  switch (gameState) {
    case GAME_STATE_QUEST:
      quest.update();
      break;
    case GAME_STATE_BATTLE:
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
      break;
  }  
}



//////////////////////////////
// RENDER
//////////////////////////////

void render() {
  switch (gameState) {
    case GAME_STATE_TITLE:
      title.render();
      break;
    case GAME_STATE_INFO:
      info.render();
      break;
    case GAME_STATE_QUEST:
      quest.render();
      break;
    case GAME_STATE_BATTLE:
      // Render Top Panel
      arduboy.fillRect(0, 0, 128, 10);
      
      // Render Health
      for (int i = 0; i < HEALTH_MAX; i++) {  
        sprites.drawErase(
          2 + (i * (heartSprite[0] + 1)),
          2,
          heartSprite,
          i < health ? 0 : 1
        );
      }

      renderNumberAlignRight(score, 126, 2, true);
      
      // Render Preview Divider
      arduboy.fillRect(89, 14, 1, 48);
      
      enemy->render();

      weapons->render();
      for (int i = 0; i < previewGemCount; i++) previewGems[i]->render();
      for (int i = 0; i < fallingGemCount; i++) fallingGems[i]->render();

      // Render Paused
      if (paused) sprites.drawOverwrite(50, 28, pausedTextImage, 0); 
      break;
    case GAME_STATE_WIN:
      win.render();
      break;
    case GAME_STATE_LOSE:
      lose.render();
      break;
  }
}



//////////////////////////////
// GAME LOOP
//////////////////////////////

void loop() {
  if ((!arduboy.nextFrame())) return;

  arduboy.pollButtons();
  arduboy.clear();

  handleInput();
  update();
  render();
  
  arduboy.display();
}
