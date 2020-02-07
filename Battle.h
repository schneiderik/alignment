#ifndef BATTLE_H
#define BATTLE_H

#include "global.h"

#define FALLING_GEMS_MAX 2
#define PREVIEW_GEMS_MAX 2

class Battle {
  public:
    Battle();
    
    void handleInput();
    void update();
    void render();
    void reset();

    void handlePlayerDefeated();
    void handleEnemyDefeated();

    void swapWeapons();
    bool isClearing();
    bool shouldGeneratePreviewGems();
    void generatePreviewGems();
    void generatePreviewGem();
    bool shouldDropPreviewGems();
    void dropPreviewGems();
    void dropGems();
    bool fallingGemsBelowPreviewThreshold();
    int randomUniqueRow();

    void handleFullWeapon(Gem&);
    bool isMatch(Gem&);
    void handleMatch(Gem&);
    void handleNoMatch(Gem&);
    void handleGemStack(Gem&);

    int health = HEALTH_MAX;
    int paused = false;
    int previewGemCount = 0;
    int fallingGemCount = 0;
    Gem* previewGems[PREVIEW_GEMS_MAX];
    Gem* fallingGems[FALLING_GEMS_MAX];
};

#endif
