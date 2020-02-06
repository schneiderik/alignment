#include "global.h"
#include "Gem.h"
#include "Weapon.h"
#include "Enemy.h"
#include "WeaponManager.h"

//////////////////////////////
// GLOBAL VARIABLES
//////////////////////////////

int gameState = GAME_STATE_TITLE;
int titleState = TITLE_STATE_PLAY;
int questCursorOffset = 0;
int questCursorVelocity = -1;
unsigned long int score = 0;
Enemy enemy;
int gameSpeed = INITIAL_GAME_SPEED;
int health = HEALTH_MAX;
int paused = false;
int previewGemCount = 0;
int fallingGemCount = 0;



//////////////////////////////
// SETUP
//////////////////////////////

void setup() {
  arduboy.initRandomSeed();
  arduboy.begin();
  arduboy.setFrameRate(FPS);

  tmpGem = new Gem();
  tmpWeapon = new Weapon(9);
  weapons = new WeaponManager();
  for (int i = 0; i < PREVIEW_GEMS_MAX; i++) previewGems[i] = new Gem();
  for (int i = 0; i < FALLING_GEMS_MAX; i++) fallingGems[i] = new Gem();
    
  arduboy.clear();
}



//////////////////////////////
// HANDLE INPUT
//////////////////////////////

void resetGame() {
  titleState = TITLE_STATE_PLAY;
  enemy.set(ENEMY_TYPE_SKELETON);
  score = 0;
  gameState = GAME_STATE_TITLE;
}

void startBattle() { 
  health = HEALTH_MAX;
  fallingGemCount = 0;
  previewGemCount = 0;
  enemy.reset();
  weapons->reset();
  confirmSound();
  gameState = GAME_STATE_BATTLE;
}

void decrementTitleState() {
  if (titleState > 0) {
    titleState--;  
    moveSound();
  }
}

void incrementTitleState() {
  if (titleState < LAST_TITLE_STATE) {
    titleState++;
    moveSound();
  }
}

void selectTitleOption() {
  switch(titleState) {
    case TITLE_STATE_PLAY:
      gameState = GAME_STATE_QUEST;
      break;
    case TITLE_STATE_INFO:
      gameState = GAME_STATE_INFO;
      break;
    case TITLE_STATE_SFX:
      if (arduboy.audio.enabled()) {
        arduboy.audio.off();
      } else {
        arduboy.audio.on();
      }
    
      arduboy.audio.saveOnOff();
      break;
  };
  confirmSound();
}

void swapWeapons() {
  Weapon& weapon1 = weapons->get(weapons->activeIndex);
  Weapon& weapon2 = weapons->get(weapons->activeIndex + 1);
  
  for(int i = 0; i < fallingGemCount; i++) {
    Gem& fallingGem = *fallingGems[i];
    bool fallingGemInRow1 = weapons->activeIndex == fallingGem.row;
    bool fallingGemInRow2 = weapons->activeIndex + 1 == fallingGem.row;
    bool fallingGemMustMoveToRow2 = fallingGem.x < gemXOffsets[weapon2.gemCount];
    bool fallingGemMustMoveToRow1 = fallingGem.x < gemXOffsets[weapon1.gemCount];
  
    if (fallingGemInRow1 && fallingGemMustMoveToRow2) {
      fallingGem.row = weapons->activeIndex + 1;
    } else if (fallingGemInRow2 && fallingGemMustMoveToRow1) {
      fallingGem.row = weapons->activeIndex;
    }  
  }
  
  weapons->swap(); 
}

void handleInput() {
  switch (gameState) {
    case GAME_STATE_TITLE:
      if (arduboy.justPressed(UP_BUTTON)) decrementTitleState();   
      if (arduboy.justPressed(DOWN_BUTTON)) incrementTitleState();
      if (arduboy.justPressed(A_BUTTON)) selectTitleOption();     
      break;
    case GAME_STATE_INFO:
      if (arduboy.justPressed(A_BUTTON)) {
        gameState = GAME_STATE_TITLE;
        confirmSound();
      }
      break;
    case GAME_STATE_QUEST:
      if (arduboy.justPressed(A_BUTTON)) startBattle();
      break;
    case GAME_STATE_BATTLE:
      if (arduboy.justPressed(RIGHT_BUTTON)) paused = !paused;
      if (paused || isClearing()) return;
      if (arduboy.justPressed(UP_BUTTON)) weapons->decrementActiveIndex();
      if (arduboy.justPressed(DOWN_BUTTON)) weapons->incrementActiveIndex();
      if (arduboy.justPressed(A_BUTTON)) weapons->swap();
      break;
    case GAME_STATE_WIN:
    case GAME_STATE_LOSE:
      if (arduboy.justPressed(A_BUTTON)) resetGame();
      break;
  }  
}



//////////////////////////////
// UPDATE
//////////////////////////////

void animateQuestCursor() {
  if (arduboy.everyXFrames(gameSpeed)) {
    if (questCursorOffset > 0) questCursorVelocity = -1;
    if (questCursorOffset < 0) questCursorVelocity = 1;
    questCursorOffset += questCursorVelocity;
  }  
}

void handlePlayerDefeated() {
  if (health == 0) gameState = GAME_STATE_LOSE;  
}

void handleEnemyDefeated() {
  if (enemy.health <= 0) {
    if (enemy.type == LAST_ENEMY) {
      gameState = GAME_STATE_WIN;
    } else { 
      enemy.set(enemy.type + 1);
      gameState = GAME_STATE_QUEST;
    }
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

bool isMatch(Gem& fallingGem) {
  Weapon& weapon = fallingGem.getWeapon();

  if (weapon.gemCount == 0) return false;

  return weapon.getLastGem().type == fallingGem.type;
}

void handleMatch(Gem& fallingGem) {
  Weapon& weapon = fallingGem.getWeapon();
  
  score += 100;
  fallingGem.pop();
  weapon.popLastGem();
  confirmSound();
  enemy.takeDamage(5, weapon.type);
}

void handleNoMatch(Gem& fallingGem) {
  Weapon& weapon = fallingGem.getWeapon();
          
  weapon.addGem(fallingGem);
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
      animateQuestCursor();
      break;
    case GAME_STATE_BATTLE:
      if (paused) return;
      handlePlayerDefeated();
      handleEnemyDefeated();
      weapons->update();
      enemy.update();
    
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

void renderTitleCursor(int x, int y, int textWidth) {
  arduboy.fillRect(x - 5, y + 1, 2, 2);
  arduboy.fillRect(x + textWidth + 3, y + 1, 2, 2);
}

void render() {
  switch (gameState) {
    case GAME_STATE_TITLE:
      sprites.drawOverwrite(0, 5, titleImage, 0);
      sprites.drawOverwrite(56, 38, playTextImage, 0);   
      sprites.drawOverwrite(56, 45, infoTextImage, 0); 
    
      if (arduboy.audio.enabled()) {
        sprites.drawOverwrite(52, 52, sfxOnTextImage, 0); 
      } else {
        sprites.drawOverwrite(50, 52, sfxOffTextImage, 0); 
      }

      switch(titleState) {
        case TITLE_STATE_PLAY:
          renderTitleCursor(56, 38, playTextImage[0]);
          break;
        case TITLE_STATE_INFO:
          renderTitleCursor(56, 45, infoTextImage[0]);
          break;
        case TITLE_STATE_SFX:
          if (arduboy.audio.enabled()) {
            renderTitleCursor(52, 52, sfxOnTextImage[0]);
          } else {
            renderTitleCursor(50, 52, sfxOffTextImage[0]);  
          }
          break;
      };
      break;
    case GAME_STATE_INFO:
      sprites.drawOverwrite(11, 4, infoImage, 0);
      break;
    case GAME_STATE_QUEST:
      sprites.drawOverwrite(32, 2, questText, 0);   

      // Render Quest Cursor
      sprites.drawOverwrite(
        ENEMY_DATA[enemy.type][ENEMY_DATA_QUEST_X] + 8,
        ENEMY_DATA[enemy.type][ENEMY_DATA_QUEST_Y] - 4 - questCursorOffset,
        questCursorImage,
        0
      );

      sprites.drawOverwrite(16, 50, pathImage, 0);
      sprites.drawOverwrite(54, 50, pathReverseImage, 0);
      sprites.drawOverwrite(64, 50, pathImage, 0);
      sprites.drawOverwrite(102, 50, pathReverseImage, 0);  

      // Render Quest Enemies
      for (int i = 0; i < ENEMY_COUNT; i++) {
        sprites.drawOverwrite(
          ENEMY_DATA[i][ENEMY_DATA_QUEST_X],
          ENEMY_DATA[i][ENEMY_DATA_QUEST_Y],
          questSprite,
          enemy.type == i
            ? i
            : i < enemy.type
              ? QUEST_SPRITE_GRAVE_INDEX
              : QUEST_SPRITE_MYSTERY_INDEX
        );  
      } 
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
      
      enemy.render();

      weapons->render();
      for (int i = 0; i < previewGemCount; i++) previewGems[i]->render();
      for (int i = 0; i < fallingGemCount; i++) fallingGems[i]->render();

      // Render Paused
      if (paused) sprites.drawOverwrite(50, 28, pausedTextImage, 0); 
      break;
    case GAME_STATE_WIN:
      sprites.drawOverwrite(21, 3, victoryImage, 0);
      sprites.drawOverwrite(6, 33, winTextImage, 0);    
      sprites.drawOverwrite(53, 46, dividerImage, 0);
      renderNumberAlignCenter(score, 64, 54, false);
      break;
    case GAME_STATE_LOSE:
      sprites.drawOverwrite(23, 9, youDiedImage, 0);
      sprites.drawOverwrite(48, 35, tryAgainImage, 0);   
      sprites.drawOverwrite(53, 42, dividerImage, 0);
      renderNumberAlignCenter(score, 64, 50, false);
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
