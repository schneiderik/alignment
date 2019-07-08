#ifndef TITLE_H
#define TITLE_H

#include "global.h"

#define TITLE_STATE_PLAY 0
#define TITLE_STATE_INFO 1
#define TITLE_STATE_SFX 2
#define TITLE_OPTION_COUNT 3
#define LAST_TITLE_OPTION TITLE_OPTION_COUNT - 1

#define TITLE_IMAGE_X 5
#define TITLE_IMAGE_Y 6

#define TITLE_PLAY_TEXT_X 56
#define TITLE_PLAY_TEXT_Y 38

#define TITLE_INFO_TEXT_X 56
#define TITLE_INFO_TEXT_Y 45

#define TITLE_SFX_ON_TEXT_X 52
#define TITLE_SFX_ON_TEXT_Y 52

#define TITLE_SFX_OFF_TEXT_X 50
#define TITLE_SFX_OFF_TEXT_Y TITLE_SFX_ON_TEXT_Y

#define TITLE_CURSOR_SIZE 2
#define TITLE_CURSOR_X_OFFSET 3
#define TITLE_CURSOR_Y_OFFSET 1


class Title {
  public:
    Title() {};

    void handleInput(Game&);
    void render();

  private:
    int state_ = TITLE_STATE_PLAY;
    void handleConfirm_(Game&);
    void renderCursor_(int, int, int);
};

#endif
