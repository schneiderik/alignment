#ifndef PUZZLE_H
#define PUZZLE_H

#include "../../global.h";

#define PUZZLE_PREVIEW_DIVIDER_X 89
#define PUZZLE_PREVIEW_DIVIDER_Y 0
#define PUZZLE_PREVIEW_DIVIDER_WIDTH 1
#define PUZZLE_PREVIEW_DIVIDER_HEIGHT 49

#define PUZZLE_WEAPONS_X 0
#define PUZZLE_WEAPONS_Y 1

class Puzzle {
  public:
    void update();
    void render(int, int);
    void reset();

    void enableFastFall();
    void disableFastFall();
    void forceEnableFastFall();
    void forceDisableFastFall();

  private:
    void renderPreviewDivider_(int, int);
    int getGameSpeed_();

    bool fastFall_ = false;
    bool forcedFastFall_ = false;
}

#endif



