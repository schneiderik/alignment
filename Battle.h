#ifndef BATTLE_H
#define BATTLE_H

#include "global.h"

class Battle {
  public:    
    void handleInput();
    void update();
    void render();
    void reset();

    void renderTopBar();
    void renderHealth();
    void renderPreviewDivider();
    void renderPaused();

    int paused = false;
};

#endif
