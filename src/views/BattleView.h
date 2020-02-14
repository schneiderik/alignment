#ifndef BATTLE_VIEW_H
#define BATTLE_VIEW_H

#include "../../global.h"

class BattleView {
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
