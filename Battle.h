#ifndef BATTLE_H
#define BATTLE_H

#include "global.h"
#include "Weapon.h"

class Battle {
  public:
    Battle();

    void handleInput(Game&);
    void update(Game&);
    void render(Game&);
    void reset();

  private:
    int cursorIndex_ = 0;
    void handlePause_();
    void handleSwapWeapons_();
    void handleMoveCursorUp_();
    void handleMoveCursorDown_();
    void renderPaused_();
    Weapon* weapons_;
    int* weaponPositions_;
    bool paused_ = false;
};

#endif
