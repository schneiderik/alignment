#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "images.h"

#define FPS 60
#define INTERVAL_LENGTH 30
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define GAME_STATE_TITLE 0
#define GAME_STATE_INFO 1
#define GAME_STATE_QUEST 2
#define GAME_STATE_BATTLE 3
#define GAME_STATE_WIN 4
#define GAME_STATE_LOSE 5

#define TITLE_STATE_PLAY 0
#define TITLE_STATE_INFO 1
#define TITLE_STATE_SFX 2

#define TITLE_STATE_COUNT 3
#define LAST_TITLE_STATE TITLE_STATE_COUNT - 1

#define QUEST_SPRITE_GRAVE_INDEX 6
#define QUEST_SPRITE_MYSTERY_INDEX 5

#define HEALTH_MAX 3

#define ENEMY_COUNT 5
#define LAST_ENEMY ENEMY_COUNT - 1

#define ENEMY_HEALTH_BAR_WIDTH_MAX 20

#define ENEMY_TYPE_SKELETON 0
#define ENEMY_TYPE_ORC 1
#define ENEMY_TYPE_GOLEM 2
#define ENEMY_TYPE_DEMON 3
#define ENEMY_TYPE_SORCERER 4

#define ENEMY_DATA_LENGTH 7
#define ENEMY_DATA_HEALTH 0
#define ENEMY_DATA_MODIFIER 1
#define ENEMY_DATA_QUEST_X 5
#define ENEMY_DATA_QUEST_Y 6

#define BATTLE_CURSOR_MIN 0
#define BATTLE_CURSOR_MAX 2

#define WEAPON_COUNT 4

#define WEAPON_TYPE_SWORD 0
#define WEAPON_TYPE_HAMMER 1
#define WEAPON_TYPE_ARROW 2
#define WEAPON_TYPE_STAFF 3

#define WEAPON_DATA_LENGTH 3
#define WEAPON_DATA_TYPE 0
#define WEAPON_DATA_Y 1
#define WEAPON_DATA_GEM_COUNT 2

#define WEAPON_GEMS_MAX 6

#define GEM_TYPE_COUNT 5

#define GEM_DATA_LENGTH 4
#define GEM_DATA_TYPE 0
#define GEM_DATA_ROW 1
#define GEM_DATA_X 2
#define GEM_DATA_Y 3

#define FALLING_GEMS_MAX 2
#define PREVIEW_GEMS_MAX 2
#define POPPING_GEMS_MAX 4
#define CLEARING_GEMS_MAX 14

#define PREVIEW_GEM_X 92
#define PREVIEW_THRESHOLD_X 89

#define INITIAL_GAME_SPEED 8

#define GEM_POPPING_ANIMATION_START_FRAME 5
#define GEM_POPPING_ANIMATION_END_FRAME 7

#define GRAVITY_ACCELERATION 1

#define CLEARING_GEM_ANIMATION_DATA_LENGTH 2
#define CLEARING_GEM_ANIMATION_DATA_VELOCITY_X 0
#define CLEARING_GEM_ANIMATION_DATA_VELOCITY_Y 1

#define ENEMY_TAKE_DAMAGE_ANIMATION_FRAME_LENGTH 3
#define ENEMY_TAKE_DAMAGE_ANIMATION_START_FRAME 0
#define ENEMY_TAKE_DAMAGE_ANIMATION_END_FRAME 10
#define ENEMY_TAKE_DAMAGE_FLASH_LENGTH 5
#define ENEMY_TAKE_DAMAGE_FLASH_COUNT_MAX 5


Arduboy2 arduboy;
Sprites sprites;
ArduboyTones sound(arduboy.audio.enabled);



//////////////////////////////
// CONSTANTS
//////////////////////////////

const int ENEMY_DATA[ENEMY_COUNT][ENEMY_DATA_LENGTH] = {
  {100, 0, 0, 0, 0, 5, 16},
  {200, 0, 0, 0, 0, 29, 31},
  {200, 0, 1, -1, 1, 53, 16},
  {150, -1, -1, 1, 0, 77, 31},
  {250, 1, -1, -1, -1, 101, 16}
};
const int weaponYOffsets[WEAPON_COUNT] = {13, 25, 37, 49};
const int gemYOffsets[WEAPON_COUNT] = {14, 26, 38, 50};
const int gemXOffsets[WEAPON_GEMS_MAX + 1] = {17, 29, 41, 53, 65, 77, 89};
const int defaultWeapons[WEAPON_COUNT][WEAPON_DATA_LENGTH] = {
  {0, weaponYOffsets[0], 0},
  {1, weaponYOffsets[1], 0},
  {2, weaponYOffsets[2], 0},
  {3, weaponYOffsets[3], 0}
};



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
int weaponGems[WEAPON_COUNT][WEAPON_GEMS_MAX][GEM_DATA_LENGTH];
int weapons[WEAPON_COUNT][WEAPON_DATA_LENGTH];
int previewGemCount = 0;
int fallingGemCount = 0;
int poppingGemCount = 0;
int clearingGemCount = 0;
int previewGems[PREVIEW_GEMS_MAX][GEM_DATA_LENGTH];
int fallingGems[FALLING_GEMS_MAX][GEM_DATA_LENGTH];
int poppingGems[POPPING_GEMS_MAX][GEM_DATA_LENGTH];
int clearingGems[CLEARING_GEMS_MAX][GEM_DATA_LENGTH];
int clearingGemAnimationData[CLEARING_GEMS_MAX][CLEARING_GEM_ANIMATION_DATA_LENGTH];
int enemyTakeDamageAnimationFrame = ENEMY_TAKE_DAMAGE_ANIMATION_END_FRAME;
int enemyTakeDamageFlashCount = ENEMY_TAKE_DAMAGE_FLASH_COUNT_MAX;
int enemyPortraitOffset = 0;
int enemyPortraitVelocity = 1;



//////////////////////////////
// SETUP
//////////////////////////////

void setup() {
  arduboy.initRandomSeed();
  arduboy.begin();
  arduboy.setFrameRate(FPS);
    
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
// HELPERS
//////////////////////////////

void copyArray(int *ptr1, int *ptr2, int arrLength) {
  for (int i = 0; i < arrLength; i++) {
    ptr1[i] = ptr2[i];
  }
}

void swapArrays(int *ptr1, int *ptr2, int arrLength) {
  int tmp[arrLength];
  copyArray(tmp, ptr1, arrLength);
  copyArray(ptr1, ptr2, arrLength);
  copyArray(ptr2, tmp, arrLength);  
}

int* weaponForGem(int* gem) {
  return weapons[gem[GEM_DATA_ROW]];
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

  for (int i = 0; i < WEAPON_COUNT; i++) {
    copyArray(weapons[i], defaultWeapons[i], WEAPON_DATA_LENGTH);
  }
  
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
  int* weapon1 = weapons[battleCursorIndex];
  int* weapon2 = weapons[battleCursorIndex + 1];
  int weapon1GemCount = weapon1[WEAPON_DATA_GEM_COUNT];
  int weapon2GemCount = weapon2[WEAPON_DATA_GEM_COUNT];
  int weapon1Type = weapon1[WEAPON_DATA_TYPE];
  int weapon2Type = weapon2[WEAPON_DATA_TYPE];
  
  for(int i = 0; i < fallingGemCount; i++) {
    int* fallingGem = fallingGems[i];
    bool fallingGemInRow1 = battleCursorIndex == fallingGem[GEM_DATA_ROW];
    bool fallingGemInRow2 = battleCursorIndex + 1 == fallingGem[GEM_DATA_ROW];
    bool fallingGemMustMoveToRow2 = fallingGem[GEM_DATA_X] < gemXOffsets[weapon2GemCount];
    bool fallingGemMustMoveToRow1 = fallingGem[GEM_DATA_X] < gemXOffsets[weapon1GemCount];
  
    if (fallingGemInRow1 && fallingGemMustMoveToRow2) {
      fallingGem[GEM_DATA_ROW] = battleCursorIndex + 1;
    } else if (fallingGemInRow2 && fallingGemMustMoveToRow1) {
      fallingGem[GEM_DATA_ROW] = battleCursorIndex;
    }

    swapSound();
  }

  swapArrays(weapon1, weapon2, WEAPON_DATA_LENGTH);

  for (int i = 0; i < weapon1GemCount; i++) {
    weaponGems[weapon1Type][i][GEM_DATA_ROW] = battleCursorIndex + 1;
  }

  for (int i = 0; i < weapon2GemCount; i++) {
    weaponGems[weapon2Type][i][GEM_DATA_ROW] = battleCursorIndex;
  }
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
    if (previewGems[i][GEM_DATA_ROW] == num) existing = true;
  }

  return existing ? randomUniqueRow() : num;
}

void adjustGemX(int* gem) {
  if (arduboy.everyXFrames(gameSpeed) && gemXOffsets[weapons[gem[GEM_DATA_ROW]][WEAPON_DATA_GEM_COUNT]] < gem[GEM_DATA_X]) { 
    gem[GEM_DATA_X] -= 3;
  }    
}

void adjustGemY(int* gem) {
  if (gem[GEM_DATA_Y] != gemYOffsets[gem[GEM_DATA_ROW]]) {
    gem[GEM_DATA_Y] += gem[GEM_DATA_Y] < gemYOffsets[gem[GEM_DATA_ROW]] ? 3 : -3;
  }  
}

void adjustGem(int* gem) {  
  adjustGemY(gem);
  adjustGemX(gem);
}

void adjustWeaponY(int* weapon, int row) {
  if (weapon[WEAPON_DATA_Y] != weaponYOffsets[row]) {
    weapon[WEAPON_DATA_Y] += weapon[WEAPON_DATA_Y] < weaponYOffsets[row] ? 3 : -3;
  }  
}

void adjustWeapons() {
  for (int weaponIndex = 0; weaponIndex < WEAPON_COUNT; weaponIndex++) {
    int* weapon = weapons[weaponIndex];
    
    adjustWeaponY(weapon, weaponIndex);
    
    for (int gemIndex = 0; gemIndex < weapon[WEAPON_DATA_GEM_COUNT]; gemIndex++) {
      adjustGemY(weaponGems[weapon[WEAPON_DATA_TYPE]][gemIndex]);
    }
  }  
}

void adjustFallingGems() {  
  for(int i = 0; i < fallingGemCount; i++) adjustGem(fallingGems[i]);
}

bool shouldGeneratePreviewGems() {
  return previewGemCount == 0 && (fallingGemCount == 0 || fallingGemsBelowPreviewThreshold());
}

void generatePreviewGem() {
  int* previewGem = previewGems[previewGemCount];

  previewGem[GEM_DATA_TYPE] = random(0, GEM_TYPE_COUNT);
  previewGem[GEM_DATA_ROW] = randomUniqueRow();
  previewGem[GEM_DATA_X] = PREVIEW_GEM_X;
  previewGem[GEM_DATA_Y] = gemYOffsets[previewGem[GEM_DATA_ROW]];
  previewGemCount++;  
}

void generatePreviewGems() {
  for (int i = 0; i < PREVIEW_GEMS_MAX; i++) generatePreviewGem();
}

bool fallingGemsBelowPreviewThreshold() {
  for (int i = 0; i < fallingGemCount; i++) {
    if (fallingGems[i][GEM_DATA_X] > PREVIEW_THRESHOLD_X) return false;
  }

  return true;
}

bool shouldDropPreviewGems() {
  return fallingGemCount == 0 && previewGemCount > 0;
}

void dropPreviewGems() {
  int limit = previewGemCount;
  for (int i = 0; i < limit; i++) {
    copyArray(fallingGems[i], previewGems[i], GEM_DATA_LENGTH);
    fallingGemCount++;
    previewGemCount--;
  }
}

bool shouldResolveFallingGem(int* fallingGem) {
  int* weapon = weaponForGem(fallingGem);
  int weaponGemCount = weapon[WEAPON_DATA_GEM_COUNT];
  
  return gemXOffsets[weaponGemCount] >= fallingGem[GEM_DATA_X];
}

void handleFullWeapon(int* weapon, int* fallingGem) {
  int weaponGemCount = weapon[WEAPON_DATA_GEM_COUNT];
  int weaponType = weapon[WEAPON_DATA_TYPE];
  
  for (int i = 0; i < weaponGemCount; i++) {
    copyArray(clearingGems[clearingGemCount], weaponGems[weaponType][i], GEM_DATA_LENGTH);
    clearingGemAnimationData[clearingGemCount][CLEARING_GEM_ANIMATION_DATA_VELOCITY_X] = random(0, 3) - 1;
    clearingGemAnimationData[clearingGemCount][CLEARING_GEM_ANIMATION_DATA_VELOCITY_Y] = random(0, 3) - 2;
    clearingGemCount++;
  }

  copyArray(clearingGems[clearingGemCount], fallingGem, GEM_DATA_LENGTH);
  clearingGemAnimationData[clearingGemCount][CLEARING_GEM_ANIMATION_DATA_VELOCITY_X] = random(0, 3) - 1;
  clearingGemAnimationData[clearingGemCount][CLEARING_GEM_ANIMATION_DATA_VELOCITY_Y] = random(0, 3) - 2;
  clearingGemCount++;
  
  weapon[WEAPON_DATA_GEM_COUNT] = 0;
  health--;
  loseHeartSound();
}

bool isMatch(int* weapon, int* fallingGem) {
  int weaponGemCount = weapon[WEAPON_DATA_GEM_COUNT];

  if (weaponGemCount == 0) return false;
  
  int weaponType = weapon[WEAPON_DATA_TYPE];
  int* weaponTopGem = weaponGems[weaponType][weaponGemCount - 1];

  return weaponTopGem[GEM_DATA_TYPE] == fallingGem[GEM_DATA_TYPE];
}

void handleMatch(int* weapon, int* fallingGem) {
  weapon[WEAPON_DATA_GEM_COUNT]--;
  enemyHealth -= 5;
  score += 100;
  enemyHealthBarWidth = (int)ceil(((float)enemyHealth / (float)ENEMY_DATA[enemyType][ENEMY_DATA_HEALTH]) * (float)ENEMY_HEALTH_BAR_WIDTH_MAX);

  copyArray(poppingGems[poppingGemCount], fallingGem, GEM_DATA_LENGTH);
  poppingGems[poppingGemCount][GEM_DATA_TYPE] = GEM_POPPING_ANIMATION_START_FRAME;
  poppingGemCount++;
  
  copyArray(poppingGems[poppingGemCount], weaponGems[weapon[WEAPON_DATA_TYPE]][weapon[WEAPON_DATA_GEM_COUNT]], GEM_DATA_LENGTH);
  poppingGems[poppingGemCount][GEM_DATA_TYPE] = GEM_POPPING_ANIMATION_START_FRAME;
  poppingGemCount++;
  
  confirmSound();

  enemyTakeDamageFlashCount = 0;
  enemyTakeDamageAnimationFrame = ENEMY_TAKE_DAMAGE_ANIMATION_START_FRAME;
}

void handleNoMatch(int* weapon, int* fallingGem) {
  int weaponGemCount = weapon[WEAPON_DATA_GEM_COUNT];
  int weaponType = weapon[WEAPON_DATA_TYPE];
  int* weaponNextGem = weaponGems[weaponType][weaponGemCount];
  
  score += 10;            
  copyArray(weaponNextGem, fallingGem, GEM_DATA_LENGTH);
  weapon[WEAPON_DATA_GEM_COUNT]++;  
}

bool weaponIsFull(int* weapon) {
  return weapon[WEAPON_DATA_GEM_COUNT] == WEAPON_GEMS_MAX;
}

void resolveFallingGems() {
  for(int i = 0; i < fallingGemCount; i++) {
    int* fallingGem = fallingGems[i];
    
    if (shouldResolveFallingGem(fallingGem)) {
      int* weapon = weaponForGem(fallingGem);


      if (isMatch(weapon, fallingGem)) {
        handleMatch(weapon, fallingGem);
      } else {
        if (weaponIsFull(weapon)) {
          handleFullWeapon(weapon, fallingGem);
        } else {
          handleNoMatch(weapon, fallingGem);
        }        
      }

      for(int j = i; j < fallingGemCount; j++) {
        copyArray(fallingGem, fallingGems[j], GEM_DATA_LENGTH);
      }
      
      fallingGemCount--;
      i--;
    }
  }  
}

void popGems() {
  if (arduboy.everyXFrames(5)) {
    for (int i = 0; i < poppingGemCount; i++) {
      if (poppingGems[i][GEM_DATA_TYPE] == GEM_POPPING_ANIMATION_END_FRAME) {
        for(int j = i + 1; j < poppingGemCount; j++) {
          copyArray(poppingGems[i], poppingGems[j], GEM_DATA_LENGTH);
        }
        
        poppingGemCount--;
        i--;
      } else {
        poppingGems[i][GEM_DATA_TYPE]++;
      }
    }
  }
}

void clearGems() {
  if (arduboy.everyXFrames(5)) {  
    for (int i = 0; i < clearingGemCount; i++) {
      if (clearingGems[i][GEM_DATA_Y] < SCREEN_HEIGHT) {
        clearingGems[i][GEM_DATA_Y] += clearingGemAnimationData[i][CLEARING_GEM_ANIMATION_DATA_VELOCITY_Y];
        clearingGems[i][GEM_DATA_X] += clearingGemAnimationData[i][CLEARING_GEM_ANIMATION_DATA_VELOCITY_X];
        clearingGemAnimationData[i][CLEARING_GEM_ANIMATION_DATA_VELOCITY_Y] += GRAVITY_ACCELERATION;
      } else {
        for(int j = i + 1; j < clearingGemCount; j++) {
          copyArray(clearingGems[i], clearingGems[j], GEM_DATA_LENGTH);
        }
        
        clearingGemCount--;
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
      adjustWeapons();
      
      if (arduboy.everyXFrames(ENEMY_TAKE_DAMAGE_FLASH_LENGTH) && enemyTakeDamageFlashCount < ENEMY_TAKE_DAMAGE_FLASH_COUNT_MAX) enemyTakeDamageFlashCount++;

      if (arduboy.everyXFrames(ENEMY_TAKE_DAMAGE_ANIMATION_FRAME_LENGTH)) {
        if (enemyTakeDamageAnimationFrame < ENEMY_TAKE_DAMAGE_ANIMATION_END_FRAME) {
          if (enemyPortraitOffset > 1) enemyPortraitVelocity = -1;
          if (enemyPortraitOffset < -1) enemyPortraitVelocity = 1;
          enemyPortraitOffset += enemyPortraitVelocity;
          enemyTakeDamageAnimationFrame++;
        } else {
          enemyPortraitOffset = 0;
        }
      }
      
      if (clearingGemCount > 0) {
        clearGems();
      } else {
        popGems();
        adjustFallingGems();
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

void renderScoreRight(int x, int y, bool black) {
  unsigned long int score_ = score;

  if (score_ == 0) {
    if (black) {
      sprites.drawErase(x, y, numberSprite, 0);
    } else {
      sprites.drawOverwrite(x, y, numberSprite, 0);
    }
    return;
  }

  int index = 0;

  while (score_) {
    int digit = score_ % 10;

    if (black) {
     sprites.drawErase(
        x - (index * (numberSprite[0] + 2)),
        y,
        numberSprite,
        digit
      );     
    } else {
      sprites.drawOverwrite(
        x - (index * (numberSprite[0] + 2)),
        y,
        numberSprite,
        digit
      );
    }

    score_ /= 10;
    index++;
  }
}

void renderScoreCenter(int x, int y, bool black) {
  unsigned long int score_ = score;
  int digitCount = 0;
  
  while (score_ /= 10) digitCount++;
  
  int digitWidth = numberSprite[0] + 2;
  int scoreWidth = (digitCount * digitWidth) - 2;
  
  renderScoreRight(x + (scoreWidth / 2), y, black);
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

      renderScoreRight(121, 2, true);
      
      // Render Preview Divider
      arduboy.fillRect(89, 14, 1, 48);

      // Render Weapons
      for (int weaponIndex = 0; weaponIndex < WEAPON_COUNT; weaponIndex++) {
        int* weapon = weapons[weaponIndex];
                
        // Render Weapon Icon
        if (weaponIndex == battleCursorIndex || weaponIndex == battleCursorIndex + 1) {
          arduboy.fillRect(0, weapon[WEAPON_DATA_Y], 12, 12); 
          sprites.drawErase(2, weapon[WEAPON_DATA_Y] + 2, weaponSprite, weapon[WEAPON_DATA_TYPE]);  
        } else {
          sprites.drawOverwrite(2, weapon[WEAPON_DATA_Y] + 2, weaponSprite, weapon[WEAPON_DATA_TYPE]);    
        }

        // Render Weapon Icon Divider
        arduboy.fillRect(14, weapon[WEAPON_DATA_Y] + 1, 1, 10);

        for (int gemIndex = 0; gemIndex < weapon[WEAPON_DATA_GEM_COUNT]; gemIndex++) {
          int* gem = weaponGems[weapon[WEAPON_DATA_TYPE]][gemIndex];
          
          sprites.drawPlusMask(
            gem[GEM_DATA_X], 
            gem[GEM_DATA_Y], 
            gemSpritePlusMask, 
            gem[GEM_DATA_TYPE]
          );          
        }
      }

      for (int i = 0; i < poppingGemCount; i++) {      
        sprites.drawPlusMask(
          poppingGems[i][GEM_DATA_X], 
          poppingGems[i][GEM_DATA_Y], 
          gemSpritePlusMask, 
          poppingGems[i][GEM_DATA_TYPE]
        );     
      }

      // Render Preview Gems
      for(int previewGemIndex = 0; previewGemIndex < PREVIEW_GEMS_MAX; previewGemIndex++) {
        int* previewGem = previewGems[previewGemIndex];
        
        sprites.drawPlusMask(
          previewGem[GEM_DATA_X], 
          gemYOffsets[previewGem[GEM_DATA_ROW]], 
          gemSpritePlusMask, 
          previewGem[GEM_DATA_TYPE]
        );
      }

      // Render Falling Gems
      for(int fallingGemIndex = 0; fallingGemIndex < fallingGemCount; fallingGemIndex++) {
        int* fallingGem = fallingGems[fallingGemIndex];

        sprites.drawPlusMask(
          fallingGem[GEM_DATA_X], 
          fallingGem[GEM_DATA_Y], 
          gemSpritePlusMask, 
          fallingGem[GEM_DATA_TYPE]
        );
      }

      // Render Enemy Portrait
      if (enemyTakeDamageFlashCount == ENEMY_TAKE_DAMAGE_FLASH_COUNT_MAX || enemyTakeDamageFlashCount % 2) {
        sprites.drawOverwrite(104 + enemyPortraitOffset, 12, enemySprite, enemyType);
      }

      // Render Enemy Health
      arduboy.fillRect(106, 62, enemyHealthBarWidth, 1, 1);

      for (int i = 0; i < clearingGemCount; i++) {      
        sprites.drawPlusMask(
          clearingGems[i][GEM_DATA_X], 
          clearingGems[i][GEM_DATA_Y], 
          gemSpritePlusMask, 
          clearingGems[i][GEM_DATA_TYPE]
        );     
      }

      // Render Paused
      if (paused) sprites.drawOverwrite(50, 28, pausedTextImage, 0); 
      break;
    case GAME_STATE_WIN:
      sprites.drawOverwrite(21, 3, victoryImage, 0);
      sprites.drawOverwrite(6, 33, winTextImage, 0);    
      sprites.drawOverwrite(53, 46, dividerImage, 0);
      renderScoreCenter(64, 54, false);
      break;
    case GAME_STATE_LOSE:
      sprites.drawOverwrite(23, 9, youDiedImage, 0);
      sprites.drawOverwrite(48, 35, tryAgainImage, 0);   
      sprites.drawOverwrite(53, 42, dividerImage, 0);
      renderScoreCenter(64, 50, false);
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
