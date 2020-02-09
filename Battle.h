#ifndef BATTLE_H
#define BATTLE_H

#include "global.h"

class Battle {
  public:    
    void handleInput();
    void update();
    void render();
    void reset();

    void handlePlayerDefeated();
    void handleEnemyDefeated();

    void swapWeapons();

    void handleFullWeapon(Gem&);
    bool isMatch(Gem&);
    void handleMatch(Gem&);
    void handleNoMatch(Gem&);
    void handleGemStack(Gem&);

    void renderTopBar();
    void renderHealth();
    void renderPreviewDivider();
    void renderPaused();

    int paused = false;
};

#endif
