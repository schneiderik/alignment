#ifndef TITLE_H
#define TITLE_H

#include "global.h"

class Title {
  public:
    Title() {};

    void handleInput(Game&);
    void render();

  private:
    int state_ = TITLE_STATES::TITLE_STATE_PLAY;
    void handleConfirm_(Game&);
    void renderCursor_(int, int, int);
};

#endif
