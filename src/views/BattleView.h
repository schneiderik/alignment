#ifndef BATTLE_VIEW_H
#define BATTLE_VIEW_H

#include "../../global.h"
#include "./View.h"

class BattleView: public View {
  public:    
    void handleInput() override;
    void update() override;
    void render() override;
    void reset();

    void renderTopBar();
    void renderHealth();
    void renderPreviewDivider();
    void renderPaused();

    int paused = false;
};

#endif
