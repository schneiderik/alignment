#include "global.h"
#include "Gem.h"
#include "Weapon.h"

//////////////////////////////
// GLOBAL VARIABLES
//////////////////////////////

int gameState = GAME_STATE_TITLE;
int titleState = TITLE_STATE_PLAY;
int questCursorOffset = 0;
int questCursorVelocity = -1;
unsigned long int score = 0;
int gameSpeed = INITIAL_GAME_SPEED;
int enemyType = ENEMY_TYPE_SKELETON;
int enemyHealth = ENEMY_DATA[enemyType][ENEMY_DATA_HEALTH];
int enemyHealthBarWidth = ENEMY_HEALTH_BAR_WIDTH_MAX;
int health = HEALTH_MAX;
int paused = false;
int battleCursorIndex = 0;
int previewGemCount = 0;
int fallingGemCount = 0;
int poppingGemCount = 0;
int clearingGemCount = 0;
int enemyTakeDamageAnimationFrame = ENEMY_TAKE_DAMAGE_ANIMATION_END_FRAME;
int enemyTakeDamageFlashCount = ENEMY_TAKE_DAMAGE_FLASH_COUNT_MAX;
int enemyPortraitOffset = 0;
int enemyPortraitVelocity = 1;
int enemyTakeDamageIndicatorFrame = ENEMY_TAKE_DAMAGE_INDICATOR_END_FRAME;
int enemyTakeDamageIndicatorY = ENEMY_TAKE_DAMAGE_INDICATOR_INITIAL_Y;
int enemyTakeDamageIndicatorNum = 0;



//////////////////////////////
// SETUP
//////////////////////////////

void setup() {
  arduboy.initRandomSeed();
  arduboy.begin();
  arduboy.setFrameRate(FPS);

  tmpGem = new Gem();
  tmpWeapon = new Weapon(9);
  for (int i = 0; i < WEAPON_COUNT; i++) weapons[i] = new Weapon(i);
  for (int i = 0; i < PREVIEW_GEMS_MAX; i++) previewGems[i] = new Gem();
  for (int i = 0; i < FALLING_GEMS_MAX; i++) fallingGems[i] = new Gem();
  for (int i = 0; i < POPPING_GEMS_MAX; i++) poppingGems[i] = new Gem();
  for (int i = 0; i < CLEARING_GEMS_MAX; i++) clearingGems[i] = new Gem();
    
  arduboy.clear();
}

//////////////////////////////
// SOUNDS
//////////////////////////////

void confirmSound() {
  sound.tone(NOTE_C5, 50);
}

void moveSound() {
  sound.tone(NOTE_E4, 50);
}

void swapSound() {
  sound.tone(NOTE_C5, 100);
}

void loseHeartSound() {
  sound.tone(NOTE_E3, 150);
}



//////////////////////////////
// HANDLE INPUT
//////////////////////////////

void resetGame() {
  titleState = TITLE_STATE_PLAY;
  enemyType = ENEMY_TYPE_SKELETON;
  score = 0;
  gameState = GAME_STATE_TITLE;
}

void startBattle() { 
  health = HEALTH_MAX;
  enemyHealth = ENEMY_DATA[enemyType][ENEMY_DATA_HEALTH];
  enemyHealthBarWidth = ENEMY_HEALTH_BAR_WIDTH_MAX;
  battleCursorIndex = BATTLE_CURSOR_MIN;
  fallingGemCount = 0;
  previewGemCount = 0;
  poppingGemCount = 0;
  clearingGemCount = 0;
  enemyTakeDamageAnimationFrame = ENEMY_TAKE_DAMAGE_ANIMATION_END_FRAME;
  enemyTakeDamageFlashCount = ENEMY_TAKE_DAMAGE_FLASH_COUNT_MAX;
  enemyPortraitOffset = 0;
  enemyPortraitVelocity = 1;
  enemyTakeDamageIndicatorFrame = ENEMY_TAKE_DAMAGE_INDICATOR_END_FRAME;

  for (int i = 0; i < WEAPON_COUNT; i++) weapons[i]->reset(i);
  
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

void decrementBattleCursorIndex() {
  if (battleCursorIndex > BATTLE_CURSOR_MIN) {
    battleCursorIndex--;  
    moveSound();
  }
}

void incrementBattleCursorIndex() {
  if (battleCursorIndex < BATTLE_CURSOR_MAX) {
    battleCursorIndex++;
    moveSound();
  }
}

void swapWeapons() {
  Weapon& weapon1 = *weapons[battleCursorIndex];
  Weapon& weapon2 = *weapons[battleCursorIndex + 1];
  
  for(int i = 0; i < fallingGemCount; i++) {
    Gem& fallingGem = *fallingGems[i];
    bool fallingGemInRow1 = battleCursorIndex == fallingGem.row;
    bool fallingGemInRow2 = battleCursorIndex + 1 == fallingGem.row;
    bool fallingGemMustMoveToRow2 = fallingGem.x < gemXOffsets[weapon2.gemCount];
    bool fallingGemMustMoveToRow1 = fallingGem.x < gemXOffsets[weapon1.gemCount];
  
    if (fallingGemInRow1 && fallingGemMustMoveToRow2) {
      fallingGem.row = battleCursorIndex + 1;
    } else if (fallingGemInRow2 && fallingGemMustMoveToRow1) {
      fallingGem.row = battleCursorIndex;
    }

    swapSound();
  }

  weapon1.swap(weapon2);
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
      if (paused || clearingGemCount > 0) return;
      if (arduboy.justPressed(UP_BUTTON)) decrementBattleCursorIndex();
      if (arduboy.justPressed(DOWN_BUTTON)) incrementBattleCursorIndex();
      if (arduboy.justPressed(A_BUTTON)) swapWeapons();
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
  if (enemyHealth <= 0) {
    if (enemyType == LAST_ENEMY) {
      gameState = GAME_STATE_WIN;
    } else { 
      enemyType++;
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

void adjustFallingGems() {  

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
  int limit = previewGemCount;
  for (int i = 0; i < limit; i++) {
    *fallingGems[i] = *previewGems[i];
    fallingGemCount++;
    previewGemCount--;
  }
}

void handleFullWeapon(Gem& fallingGem) {
  Weapon& weapon = fallingGem.getWeapon();
  
  for (int i = 0; i < weapon.gemCount; i++) {
    *clearingGems[clearingGemCount] = *weapon.gems[i];
    clearingGems[clearingGemCount]->clear();
    clearingGemCount++;
  }

  *clearingGems[clearingGemCount] = fallingGem;
  
  clearingGems[clearingGemCount]->clear();
  clearingGemCount++;
  
  weapon.gemCount = 0;
  health--;
  loseHeartSound();
}

bool isMatch(Gem& fallingGem) {
  Weapon& weapon = fallingGem.getWeapon();

  if (weapon.gemCount == 0) return false;

  return weapon.lastGem().type == fallingGem.type;
}

void setPoppingGem(Gem& gem) {
  Gem& poppingGem = *poppingGems[poppingGemCount];
  poppingGem = gem;
  poppingGem.type = GEM_POPPING_ANIMATION_START_FRAME;
  poppingGemCount++;  
}

void handleMatch(Gem& fallingGem) {
  Weapon& weapon = fallingGem.getWeapon();
  
  int damage = 5 + ENEMY_DATA[enemyType][ENEMY_DATA_MODIFIER + weapon.type];
  weapon.gemCount--;
  enemyHealth -= damage;
  score += 100;
  enemyHealthBarWidth = (int)ceil(((float)enemyHealth / (float)ENEMY_DATA[enemyType][ENEMY_DATA_HEALTH]) * (float)ENEMY_HEALTH_BAR_WIDTH_MAX);

  setPoppingGem(fallingGem);
  setPoppingGem(*weapon.gems[weapon.gemCount]);
  
  confirmSound();

  enemyTakeDamageFlashCount = 0;
  enemyPortraitOffset = 0;
  enemyTakeDamageAnimationFrame = ENEMY_TAKE_DAMAGE_ANIMATION_START_FRAME;
  enemyTakeDamageIndicatorFrame = ENEMY_TAKE_DAMAGE_INDICATOR_START_FRAME;
  enemyTakeDamageIndicatorY = ENEMY_TAKE_DAMAGE_INDICATOR_INITIAL_Y;
  enemyTakeDamageIndicatorNum = -damage;
}

void handleNoMatch(Gem& fallingGem) {
  Weapon& weapon = fallingGem.getWeapon();
          
  weapon.addGem(fallingGem);
  weapon.gemCount++;
  score += 10; 
}

void resolveFallingGems() {  
  for(int i = 0; i < fallingGemCount; i++) {
    Gem& fallingGem = *fallingGems[i];
    
    if (fallingGem.atEndOfRowX()) {
      Weapon& weapon = fallingGem.getWeapon();

      if (isMatch(fallingGem)) {
        handleMatch(fallingGem);
      } else {
        if (weapon.isFull()) {
          handleFullWeapon(fallingGem);
        } else {
          handleNoMatch(fallingGem);
        }        
      }

      for(int j = i; j < fallingGemCount; j++) fallingGem = *fallingGems[j];        
      
      fallingGemCount--;
      i--;
    }
  }  
}

void removeGemFromArray(Gem** gems, int i, int& size) {
  size--;
  
  for(int j = i; j < size; j++) *clearingGems[j] = *clearingGems[j + 1];
}

void popGems() {
  for (int i = 0; i < poppingGemCount; i++) {
    if (arduboy.everyXFrames(5)) {
      if (poppingGems[i]->type < GEM_POPPING_ANIMATION_END_FRAME) {
        poppingGems[i]->type++;
      } else {
        removeGemFromArray(poppingGems, i, poppingGemCount);
        i--;
      }
    }
  }
}

void clearGems() {
  for (int i = 0; i < clearingGemCount; i++) {
    Gem& gem = *clearingGems[i];

    gem.update();
    
    if (!gem.isClearing()) {
      removeGemFromArray(clearingGems, i, clearingGemCount);
      i--;
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
      for (int i = 0; i < WEAPON_COUNT; i++) weapons[i]->update();
      
      if (arduboy.everyXFrames(ENEMY_TAKE_DAMAGE_FLASH_LENGTH) && enemyTakeDamageFlashCount < ENEMY_TAKE_DAMAGE_FLASH_COUNT_MAX) enemyTakeDamageFlashCount++;

      if (arduboy.everyXFrames(ENEMY_TAKE_DAMAGE_ANIMATION_FRAME_LENGTH)) {
        if (enemyTakeDamageAnimationFrame < ENEMY_TAKE_DAMAGE_ANIMATION_END_FRAME) {
          if (enemyPortraitOffset > 1) enemyPortraitVelocity = -1;
          if (enemyPortraitOffset < -1) enemyPortraitVelocity = 1;
          enemyPortraitOffset += enemyPortraitVelocity;
          enemyTakeDamageAnimationFrame++;
        }
      }


      if (enemyTakeDamageIndicatorFrame < ENEMY_TAKE_DAMAGE_INDICATOR_END_FRAME) {
        if (arduboy.everyXFrames(ENEMY_TAKE_DAMAGE_INDICATOR_FRAME_LENGTH)) {
          enemyTakeDamageIndicatorY--;      
          enemyTakeDamageIndicatorFrame++;
        }
      }
      
      if (clearingGemCount > 0) {
        clearGems();
      } else {
        popGems();
        for(int i = 0; i < fallingGemCount; i++) fallingGems[i]->update();
        if (arduboy.everyXFrames(gameSpeed)) {
          if (shouldGeneratePreviewGems()) generatePreviewGems();        
          if (shouldDropPreviewGems()) dropPreviewGems();
          resolveFallingGems();
        } 
      }
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

void renderDigitBlack(int digit, int x, int y) {
  sprites.drawErase(x, y, numberSprite, digit);
}

void renderDigitWhite(int digit, int x, int y) {
  sprites.drawOverwrite(x, y, numberSprite, digit);   
}

void renderDigit(int digit, int x, int y, bool black) {
  black 
   ? renderDigitBlack(digit, x, y) 
   : renderDigitWhite(digit, x, y);
}

int digitCount(int num) {
  int digitCount = 1;
  
  while (num /= 10) digitCount++;  

  return digitCount;
}

int numberWidth(int num) {
  int count = digitCount(num);
  int digitWidth = numberSprite[0] + 2;
  
  return (count * digitWidth) - 2 + (num < 0 ? 5 : 0);  
}

void renderNumberAlignRight(int num, int x, int y, bool black) {
  if (num == 0) {
    renderDigit(0, x - numberSprite[0], y, black);
    return;
  }

  int index = 0;
  int offset = 0;
  int absNum = abs(num);

  while (absNum) {
    int digit = absNum % 10;
    offset = (index * (numberSprite[0] + 2));

    renderDigit(digit, x - offset - numberSprite[0], y, black);  

    absNum /= 10;
    index++;
  }

  if (num < 0) {
    arduboy.fillRect(x - offset - 5 - numberSprite[0], y + (numberSprite[1]/2) - 1, 3, 1, !black);  
  }
}

void renderNumberAlignCenter(int num, int x, int y, bool black) {
  int numWidth = numberWidth(num);
          
  renderNumberAlignRight(num, x + (numWidth / 2), y, black);
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
        ENEMY_DATA[enemyType][ENEMY_DATA_QUEST_X] + 8,
        ENEMY_DATA[enemyType][ENEMY_DATA_QUEST_Y] - 4 - questCursorOffset,
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
          enemyType == i
            ? i
            : i < enemyType
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

      // Render Weapons
      for (int i = 0; i < WEAPON_COUNT; i++) weapons[i]->render(i == battleCursorIndex || i == battleCursorIndex + 1);
      for (int i = 0; i < poppingGemCount; i++) poppingGems[i]->render();

      // Render Preview Gems
      for(int previewGemIndex = 0; previewGemIndex < PREVIEW_GEMS_MAX; previewGemIndex++) {
        Gem& previewGem = *previewGems[previewGemIndex];
        
        sprites.drawPlusMask(
          previewGem.x, 
          gemYOffsets[previewGem.row], 
          gemSpritePlusMask, 
          previewGem.type
        );
      }

      // Render Falling Gems
      for(int i = 0; i < fallingGemCount; i++) fallingGems[i]->render();

      // Render Enemy Portrait
      if (enemyTakeDamageFlashCount == ENEMY_TAKE_DAMAGE_FLASH_COUNT_MAX || enemyTakeDamageFlashCount % 2) {
        sprites.drawOverwrite(104 + enemyPortraitOffset, 12, enemySprite, enemyType);
      }

      //Render Enemy Damage
      if (enemyTakeDamageIndicatorFrame < ENEMY_TAKE_DAMAGE_INDICATOR_END_FRAME) {
        int height = numberSprite[1] + 2;
        int width = numberWidth(enemyTakeDamageIndicatorNum) + 4;
        
        arduboy.fillRect(SCREEN_WIDTH - 27 + (width/2), enemyTakeDamageIndicatorY - 1, width + 2, height + 2, 1);
        arduboy.fillRect(SCREEN_WIDTH - 26 + (width/2), enemyTakeDamageIndicatorY, width, height, 0);
        renderNumberAlignCenter(enemyTakeDamageIndicatorNum, 116, enemyTakeDamageIndicatorY + 2, false);
      }

      // Render Enemy Health
      arduboy.fillRect(106, 62, enemyHealthBarWidth, 1, 1);

      for (int i = 0; i < clearingGemCount; i++) clearingGems[i]->render(); 

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
