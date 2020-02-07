#ifndef BATTLE_H
#define BATTLE_H

#include "global.h"
#include "GemManager.h"

class Battle {
  public:    
    void handleInput();
    void update();
    void render();
    void reset();

    void handlePlayerDefeated();
    void handleEnemyDefeated();

    void swapWeapons();
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

    void renderTopBar();
    void renderHealth();
    void renderPreviewDivider();
    void renderPaused();

    int health = HEALTH_MAX;
    int paused = false;
    
    GemManager previewGems;
    GemManager fallingGems;
};

#endif
