#ifndef PUZZLE_H
#define PUZZLE_H

#define PUZZLE_X 0
#define PUZZLE_Y 15

#define PUZZLE_CURSOR_MIN 0
#define PUZZLE_CURSOR_MAX 2

#define PUZZLE_PREVIEW_DIVIDER_X_OFFSET 89
#define PUZZLE_PREVIEW_DIVIDER_Y_OFFSET 1
#define PUZZLE_PREVIEW_DIVIDER_WIDTH 1
#define PUZZLE_PREVIEW_DIVIDER_HEIGHT 48

#define PUZZLE_GEM_PREVIEW_X_OFFSET 92
#define PUZZLE_GEM_PREVIEW_THRESHOLD_X_OFFSET 89
#define PUZZLE_GEM_Y_OFFSET 1

#define PUZZLE_WEAPON_COUNT 4

#define PUZZLE_WEAPON_HEIGHT 12

#define PUZZLE_GEM_MAX 4
#define PUZZLE_LAST_GEM_INDEX PUZZLE_GEM_MAX - 1

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

  private:
    int* weaponOrder_;
    Weapon* weapons_;

    // GemManager
    int* gemWeaponTypes_;
    Gem* gems_;
    int gemIndex_ = 0;
    
    int x_ = PUZZLE_X;
    int y_ = PUZZLE_Y;

    int cursorIndex_ = 0;
    int activeGemCount_ = 0;

    Weapon& weaponAtIndex_(int);
    int indexOfWeapon_(Weapon&);

    bool isClearingGems_();
    bool previewIsEmpty_();
    void populatePreview_();
    bool previewIsReadyToActivate_();
    void activatePreview_();

    void renderPreviewDivider_();
};

#endif
