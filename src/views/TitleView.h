#ifndef TITLE_VIEW_H
#define TITLE_VIEW_H

#include "../../global.h"

#define TITLE_STATE_PLAY 0
#define TITLE_STATE_INFO 1
#define TITLE_STATE_SFX 2

#define TITLE_STATE_COUNT 3
#define LAST_TITLE_STATE TITLE_STATE_COUNT - 1

class TitleView {
  public:
    TitleView() {};
    void handleInput();
    void decrementState();
    void incrementState();
    void selectOption();
    
    void render();
    void renderMainImage();
    void renderPlayOption();
    void renderInfoOption();
    void renderSfxOption();
    void renderCursor(int, int, int);

    int state = TITLE_STATE_PLAY;
};

#endif
