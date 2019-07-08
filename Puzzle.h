#ifndef PUZZLE_H
#define PUZZLE_H

#define PUZZLE_X 0
#define PUZZLE_Y 15

#define PUZZLE_CURSOR_MIN 0
#define PUZZLE_CURSOR_MAX 2

#define PUZZLE_PREVIEW_DIVIDER_X_OFFSET 92
#define PUZZLE_PREVIEW_DIVIDER_Y_OFFSET 1
#define PUZZLE_PREVIEW_DIVIDER_WIDTH 1
#define PUZZLE_PREVIEW_DIVIDER_HEIGHT 48

#define PUZZLE_WEAPON_COUNT 4

#define PUZZLE_WEAPON_HEIGHT 12

#include "global.h"
#include "Weapon.h"
#include "GemManager.h"

class Puzzle {
  public:
    Puzzle();

    void update();
    void render();
    
    int* matches;
    void checkForMatches();
    void clearMatches();
    void resetMatches();

    void swapWeapons();
    void moveCursorUp();
    void moveCursorDown();

    bool isWaitingForAnimation();

  private:
    int* weaponOrder_;
    Weapon* weapons_;
//    GemManager gemManager_;
    
    int x_ = PUZZLE_X;
    int y_ = PUZZLE_Y;

    int cursorIndex_ = 0;
    int activeGemCount_ = 0;

    bool previewIsEmpty_();
    void populatePreview_();
    void activatePreviewGems_();

    void renderPreviewDivider_();
};

#endif
