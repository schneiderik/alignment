//void resetEnemy(int enemyType) {
////  gameState.enemy.type = enemyType;
////  gameState.enemy.health = enemyData[enemyType][ENEMY_DATA_HEALTH];
////  gameState.enemy.percentHealth = 1;
////  gameState.enemy.healthBarWidth = ENEMY_HEALTH_BAR_WIDTH_MAX;
////  gameState.enemy.attackInterval;
////  gameState.enemy.flashInterval;
////  gameState.enemy.shakeInterval;
////  gameState.enemy.idleInterval;
////  gameState.enemy.frame = 0;
////  gameState.enemy.hidden = false;
////  gameState.enemy.offsetX = 0;
//}
//
//void resetPlayer() {
////  gameState.player.score = 0;
////  gameState.player.health = PLAYER_HEALTH_MAX;
//}
//
//void takeDamage() {
//  // health_ -= DAMAGE_BASE + getWeaponModifierData_(type_, weapon.getType());
//  // notify(*this, Event::ENEMY_DAMAGED);
//
//  // if (isDead()) notify(*this, Event::ENEMY_DEFEATED);
//}
//
//void reset() {
////  resetEnemy(ENEMY_TYPE_SKELETON);
////  resetPlayer();
//}
//
//void initEnemyAnimations() {
////  attackInterval_.init(ATTACK_INTERVAL_MIN, ATTACK_INTERVAL_MAX);
////
////  flashAnimation_.init(
////    FLASH_ANIMATION_INITIAL_VALUE,
////    FLASH_ANIMATION_LOWER_LIMIT,
////    FLASH_ANIMATION_UPPER_LIMIT,
////    FLASH_ANIMATION_COUNT,
////    FLASH_ANIMATION_DURATION,
////    FLASH_ANIMATION_LOOP
////  );
////
////  idleAnimation_.init(
////    IDLE_ANIMATION_INITIAL_VALUE,
////    IDLE_ANIMATION_LOWER_LIMIT,
////    IDLE_ANIMATION_UPPER_LIMIT,
////    IDLE_ANIMATION_SPEED,
////    IDLE_ANIMATION_LOOP
////  );
////
////  attackAnimation_.init(
////    ATTACK_ANIMATION_INITIAL_VALUE,
////    ATTACK_ANIMATION_LOWER_LIMIT,
////    ATTACK_ANIMATION_UPPER_LIMIT,
////    ATTACK_ANIMATION_COUNT,
////    ATTACK_ANIMATION_DURATION,
////    ATTACK_ANIMATION_LOOP
////  );
//}
//
//void resetEnemyAnimations() {
////  attackInterval_.reset();
////  attackAnimation_.reset();
////  flashAnimation_.reset();
////  idleAnimation_.reset();
//}
//
//
//struct Interval {
//  bool active = false;
//  int frame = 0;
//  int interval = 0;
//  int intervalMin = 0;
//  int intervalMax = 0;
//
//  void Interval::init(int interval_) {
//    intervalMin = interval_;
//    interval = getInterval();
//  }
//
//  void Interval::init(int intervalMin_, int intervalMax_) {
//    intervalMin = intervalMin_;
//    intervalMax = intervalMax_;
//    interval = getInterval();
//  }
//
//  void Interval::update() {
//    frame++;
//    active = false;
//    
//    if (frame == interval) {
//      active = true;
//      interval = getInterval();
//      frame = 0;
//    }
//  }
//
//  void Interval::reset() {
//    frame = 0;
//    interval = getInterval();
//    active = false;
//  }
//
//  bool Interval::isActive() {
//    return active;
//  }
//
//  int Interval::getInterval() {
//    if (intervalMax > 0) {
//      return random(intervalMin, intervalMax);
//    }
//
//    return intervalMin;
//  }
//};
//
//
//struct Animation {
//  int frame = 0;
//  int interval = 0;
//  int value = 0;
//};
//
//
//struct Score {
//  unsigned long int value = 0;
//
//  void render(int x, int y, int alignment, int color) {
//    switch(alignment) {
//      case ALIGN_CENTER:
//        renderAlignCenter(x, y, color);
//        break;
//      case ALIGN_RIGHT:
//        renderAlignRight(x, y, color);
//        break;
//      default:
//        renderAlignLeft(x, y, color);
//        break;
//    };
//  }
//
//  int calculateDigitCount() {
//    unsigned long int num = value;
//    int count = 1;
//    
//    while (num /= 10) count++;  
//
//    return count;
//  }
//
//  int calculateWidth() {
//    int digitWidth = numberSprite[0] + 2;
//    
//    return (calculateDigitCount() * digitWidth) - 2;  
//  }
//
//  void renderDigit(int digit, int x, int y, int color) {
//    color == BLACK
//     ? sprites.drawErase(x, y, numberSprite, digit)
//     : sprites.drawSelfMasked(x, y, numberSprite, digit);   
//  }
//
//  void renderAlignRight(int x, int y, int color) {
//    unsigned long int num = value;
//
//    if (num == 0) {
//      renderDigit(0, x - numberSprite[0], y, color);
//      return;
//    }
//
//    int index = 0;
//    int offset = 0;
//
//    while (num) {
//      unsigned long int digit = num % 10;
//      offset = (index * (numberSprite[0] + 2));
//
//      renderDigit(digit, x - offset - numberSprite[0], y, color);  
//
//      num /= 10;
//      index++;
//    }
//  }
//
//  void renderAlignCenter(int x, int y, int color) {
//    renderAlignRight(x + (int)ceil((float)calculateWidth()/(float)2), y, color);
//  }
//
//  void renderAlignLeft(int x, int y, int color) {
//    renderAlignRight(x + calculateWidth(), y, color);
//  }
//};
//
//
//struct Player {
//  Score score;
//  int health = PLAYER_HEALTH_MAX;
//};
//
//
//struct Enemy {
//  int type = ENEMY_TYPE_SKELETON;
//  int health = enemyData[ENEMY_TYPE_SKELETON][ENEMY_DATA_HEALTH];
//};
//
//struct Gem {
//  int type = 0;
//  int x = 0;
//  int y = 0;
//  int velX = 0;
//  int velY = 0;
//
//  void pop() {
//    type = GEM_POPPING_ANIMATION_START_FRAME;
//  }
//
//  void update() {
////    // popping
////    if (type >= GEM_POPPING_ANIMATION_START_FRAME) {
////      if (arduboy.everyXFrames(POPPING_GEM_FRAME_LENGTH)) {
////        if (type < GEM_POPPING_ANIMATION_END_FRAME) {
////          type++;
////        } else {
////          type = GEM_HIDDEN_TYPE;
////        }
////      }
////    }
////
////    // clearing
////    if (arduboy.everyXFrames(CLEARING_GEM_FRAME_LENGTH)) {
////      if (y < SCREEN_HEIGHT) {
////        y += velX;
////        x += velY;
////        velY += GRAVITY_ACCELERATION;
////      } else {
////        type = GEM_HIDDEN_TYPE;
////      }
////    }
////
////    // falling
////    if (arduboy.everyXFrames(gameState.fallSpeed)) {
////      x_ += GEM_MOVE_X_INCREMENT;
////    }
//  }
//
//  void init() {
//    velX = random(0, 3) - 1;
//    velY = random(0, 3) - 2;
//  }
//
//  void render() {
//    if (type != GEM_HIDDEN_TYPE) {
//      sprites.drawPlusMask(x, y, gemSpritePlusMask, type);
//    }
//  }
//};
//
//struct Weapon {
//  int activeGemCount = 0;
//  int gemCount = 0;
//  int y = 0;
//  Gem gems[WEAPON_GEM_COUNT];
//  Gem fallingGem;
//  Gem previewGem;
//
//  void render() {
//    for (int i = 0; i < activeGemCount; i++) {
//      gems[i].render();
//    }
//  }
//};
//
//struct WeaponSet {
//  int order[WEAPON_COUNT];
//  Weapon weapons[WEAPON_COUNT];
//
//  Weapon& get(int i) {
//    return weapons[order[i]];
//  }
//
//  Weapon& getRandom() {
//    return weapons[random(0, WEAPON_COUNT)];
//  }
//
//  void swap(int i) {
////    int tmp = order[i];
////    order[i] = order[i + 1];
////    order[i + 1] = tmp;
////
////
////    bool fallingGem1Exists = fallingGems.gems[fallingGems.order[cursor]] != GEM_HIDDEN_TYPE;
////    bool fallingGem2Exists = fallingGems.gems[fallingGems.order[cursor + 1]] != GEM_HIDDEN_TYPE;
////    int fallingGem1X = fallingGems[fallingGemOrder[gameState.weaponCursor]][GEM_DATA_X];
////    int fallingGem2X = fallingGems[fallingGemOrder[gameState.weaponCursor + 1]][GEM_DATA_X];
////    int weapon1GemHeadX = gemPositions[weapons[weaponOrder[gameState.weaponCursor]][WEAPON_DATA_GEM_COUNT] + 1][GEM_POSITION_X];
////    int weapon2GemHeadX = gemPositions[weapons[weaponOrder[gameState.weaponCursor + 1]][WEAPON_DATA_GEM_COUNT] + 1][GEM_POSITION_X];
////
////    if ((fallingGem1Exists && fallingGem1X < weapon2GemHeadX) || (fallingGem2Exists && fallingGem2X < weapon1GemHeadX)) {
////      int tmpOrder = weaponOrder[gameState.weaponCursor];
////      fallingGemOrder[gameState.weaponCursor] = fallingGemOrder[gameState.weaponCursor + 1];
////      fallingGemOrder[gameState.weaponCursor + 1] = tmpOrder;
////    }
//  }
//
//  void render(int x, int y) {
//    for (int i = 0; i < WEAPON_COUNT; i++) {
//      get(i).render();
//    }
//  }
//};
//
//struct Puzzle {
//  int cursor = 0;
//  // Interval forcedFastFallInterval;
//  int fallSpeed = FALL_SPEED_DEFAULT;
//  bool fallSpeedLocked = false;
//
//  WeaponSet weapons;
//
//  void enableFastFall() {
//    if (fallSpeedLocked) return;
//    fallSpeed = FALL_SPEED_FAST;
//  }
//
//  void disableFastFall() {
//    if (fallSpeedLocked) return;
//    fallSpeed = FALL_SPEED_DEFAULT;
//  }
//
//  void enableForcedFastFall() {
//    // forcedFastFallInterval.run(3000);
//    fallSpeedLocked = true;
//    fallSpeed = FALL_SPEED_FAST;
//  }
//
//  void disableForcedFastFall() {
//    fallSpeedLocked = false;
//    fallSpeed = FALL_SPEED_DEFAULT;
//  }
//
//  void moveCursorUp() {
//    // if (clearingGems.count > 0) return;
//    if (cursor == PUZZLE_CURSOR_MIN) return;
//    cursor--;  
//  }
//
//  void moveCursorDown() {
//    // if (clearingGems.count > 0) return;
//    if (cursor == PUZZLE_CURSOR_MAX) return;
//    cursor++;  
//  }
//
//  void swapWeapons() {
//    // if (clearingGems.count > 0) return;
//    weapons.swap(cursor);
//  }
//
//  void update() {
//    //if (preview.count == 0) {
//    //  preview.queueRandomGem();
//    //  preview.queueRandomGem();
//    //}
//
//    //for (int i = 0; i < WEAPON_COUNT; i++) {
//      //if (preview.gems[i] == GEM_HIDDEN_TYPE) continue;
//      //if (weapons.get(i).count == WEAPON_GEM_MAX) 
//      //weapons.get(i).setFallingGem(preview.gems[i]);
//    //}
//
//    //weapons.update();
//
////    if (forcedFastFallInterval.update()) {
////      disableForcedFastFall();
////    }
//  }
//
//  void render(int x, int y) {
//    arduboy.fillRect(
//      x + PUZZLE_PREVIEW_DIVIDER_X,
//      y + PUZZLE_PREVIEW_DIVIDER_Y,
//      PUZZLE_PREVIEW_DIVIDER_WIDTH,
//      PUZZLE_PREVIEW_DIVIDER_HEIGHT
//    );
//
//    weapons.render(x, y);
//    //previewGems.render(x + PUZZLE_PREVIEW_GEMS_X, y);
//  }
//};
//
//
//struct EnemyHealthBar {
//  void render(int x, int y, Enemy& enemy) {
//    float maxHealth = enemyData[enemy.type][ENEMY_DATA_HEALTH];
//    float percentHealth = (float)enemy.health / maxHealth;
//    int width = ceil(percentHealth * (float)ENEMY_HEALTH_BAR_WIDTH_MAX);
//
//    arduboy.fillRect(
//      x,
//      y,
//      width,
//      ENEMY_HEALTH_BAR_HEIGHT,
//      WHITE
//    ); 
//  }
//};
//
//
//struct EnemyPortrait {
//  int frame = 0;
//  bool hidden = false;
//
//  void update() {
////    attackAnimation_.update();
////    flashAnimation_.update();
////    idleAnimation_.update();
////
////    int frame = idleAnimation_.getValue();
////
////    if (attackAnimation_.isRunning()) {
////      frame = attackAnimation_.getValue();
////    } else if (flashAnimation_.isRunning()) {
////      frame = ENEMY_DAMAGE_FRAME;
////    }
////
////    enemy.frame = frame + (enemy_->getType() * ENEMY_FRAME_COUNT);
//  };
//
//  void render(int x, int y, Enemy& enemy) {
////    if (flashAnimation_.getValue() == 0) {
////      sprites.drawOverwrite(
////        x + shakeAnimation_.getValue(),
////        y,
////        enemySprite,
////        frame_
////      );
////    }
//  };
//};
//
//
//struct EnemyPanel {
//  EnemyHealthBar healthBar;
//  EnemyPortrait portrait;
//
//  void update() {
//    portrait.update();
//  }
//
//  void render(int x, int y, Enemy& enemy) {
//    healthBar.render(
//      x + ENEMY_PANEL_HEALTH_BAR_X, 
//      y + ENEMY_PANEL_HEALTH_BAR_Y,
//      enemy
//    );
//
//    portrait.render(
//      x + ENEMY_PANEL_PORTRAIT_X,
//      y + ENEMY_PANEL_PORTRAIT_Y,
//      enemy
//    );
//  }
//};
//
//
//struct Hearts {
//  void render(int x, int y, int health) {
//    for (int i = 0; i < HEARTS_MAX; i++) {  
//      sprites.drawErase(
//        x + (i * (heartSprite[0] + 1)),
//        y,
//        heartSprite,
//        i < health ? 0 : 1
//      );
//    }  
//  }
//};
//
//
//struct PlayerPanel {
//  Hearts hearts;
//
//  void render(int x, int y, Player& player) {
//    arduboy.fillRect(x, y, PANEL_WIDTH, PANEL_HEIGHT);
//    hearts.render(x + PLAYER_PANEL_HEARTS_X, y + PLAYER_PANEL_HEARTS_Y, player.health);
//    player.score.render(x + PLAYER_PANEL_SCORE_X, y + PLAYER_PANEL_SCORE_Y, ALIGN_RIGHT, BLACK);
//  }
//};



////////
// VIEWS
////////



//
//
//struct BattleView: public View {
//  bool paused = false;
//
//  Puzzle puzzle;
//  EnemyPanel enemyPanel;
//  PlayerPanel playerPanel;
//
//  void reset() {
//    puzzle.reset();
//    enemyPanel.reset();
//  }
//
//  void handleInput(Game& game) {
//    if (arduboy.justPressed(RIGHT_BUTTON)) {
//      paused = !paused;
//    }
//
//    if (paused) return;
//
//    if (arduboy.justPressed(LEFT_BUTTON)) {
//      puzzle.enableFastFall();
//    }
//
//    if (arduboy.justReleased(LEFT_BUTTON)) {
//      puzzle.disableFastFall();
//    }
//
//    if (arduboy.justPressed(UP_BUTTON)) {
//      puzzle.moveCursorUp();
//      playMoveSound();
//    }
//
//    if (arduboy.justPressed(DOWN_BUTTON)) {
//      puzzle.moveCursorDown();
//      playMoveSound();
//    }
//
//    if (arduboy.justPressed(A_BUTTON)) {
//      puzzle.swapWeapons();
//      playConfirmSound();
//    }
//  }
//
//  void update(Game& game) {
//    if (paused) return;
//
//    enemyPanel.update(game.enemy);
//    puzzle.update(game);
//
//    if (attackInterval.update()) {
//      enemyPanel.portrait.attackAnimation.run();
//    }
//
//    if (enemyPanel.portrait.attackAnimation.getValue() == ENEMY_ATTACK_EFFECT_FRAME) {
//      attack(game.enemy.type);
//    }
//  }
//
//  void attack(int enemyType) {
//    switch (enemyType) {
//      case ENEMY_TYPE_SKELETON:
//        puzzle.weapons.getRandom().popLastGem();
//        break;
//      case ENEMY_TYPE_ORC:
//        puzzle.previewGems.create();
//        break;
//      case ENEMY_TYPE_GOLEM:
//        puzzle.weapons.swap(random(WEAPON_CURSOR_MIN, WEAPON_CURSOR_MAX));
//        break;
//      case ENEMY_TYPE_DEMON:
//        puzzle.enableForcedFastFall();
//        break;
//      case ENEMY_TYPE_SORCERER:
//        attack(random(0, 4));
//        break;
//    }
//  }
//
//  void render(Game& game) {
//    playerPanel.render(
//      BATTLE_VIEW_PLAYER_PANEL_X,
//      BATTLE_VIEW_PLAYER_PANEL_Y,
//      game.player
//    );
//
//    enemyPanel.render(
//      BATTLE_VIEW_ENEMY_PANEL_X,
//      BATTLE_VIEW_ENEMY_PANEL_Y,
//      game.enemy
//    );
//
//    puzzle.render(
//      BATTLE_VIEW_PUZZLE_X,
//      BATTLE_VIEW_PUZZLE_Y
//    );
//
//    if (paused) {
//      sprites.drawOverwrite(
//        BATTLE_VIEW_PAUSED_X,
//        BATTLE_VIEW_PAUSED_Y,
//        pausedTextImage,
//        0
//      );
//    }
//  }
//};
//
//
//struct WinView: public View {
//  void handleInput(Game& game) {
//    if (arduboy.justPressed(A_BUTTON)) {
//      game.goToTitleView();
//      playConfirmSound();
//    }
//  }
//
//  void render(Game& game) {
//    sprites.drawOverwrite(
//      WIN_VIEW_VICTORY_X,
//      WIN_VIEW_VICTORY_Y,
//      victoryImage,
//      0
//    );
//
//    sprites.drawOverwrite(
//      WIN_VIEW_TEXT_X,
//      WIN_VIEW_TEXT_Y,
//      winTextImage,
//      0
//    );    
//
//    sprites.drawOverwrite(
//      WIN_VIEW_DIVIDER_X,
//      WIN_VIEW_DIVIDER_Y,
//      dividerImage,
//      0
//    );
//
//    game.player.score.render(
//      LOSE_VIEW_SCORE_X,
//      LOSE_VIEW_SCORE_Y,
//      ALIGN_CENTER,
//      WHITE
//    );
//  }
//};
//
//
//struct LoseView: public View {
//  void handleInput(Game& game) {
//    if (arduboy.justPressed(A_BUTTON)) {
//      game.goToTitleView();
//      playConfirmSound();
//    }
//  }
//
//  void render(Game& game) {
//    sprites.drawOverwrite(
//      LOSE_VIEW_YOU_DIED_X,
//      LOSE_VIEW_YOU_DIED_Y,
//      youDiedImage, 
//      0
//    );
//
//    sprites.drawOverwrite(
//      LOSE_VIEW_TRY_AGAIN_X,
//      LOSE_VIEW_TRY_AGAIN_Y,
//      tryAgainImage,
//      0
//    );   
//
//    sprites.drawOverwrite(
//      LOSE_VIEW_DIVIDER_X,
//      LOSE_VIEW_DIVIDER_Y,
//      dividerImage,
//      0
//    );
//
//    game.player.score.render(
//      LOSE_VIEW_SCORE_X,
//      LOSE_VIEW_SCORE_Y,
//      ALIGN_CENTER,
//      WHITE
//    );
//  }
//};
