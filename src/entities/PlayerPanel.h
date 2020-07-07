#ifndef PLAYER_PANEL_H
#define PLAYER_PANEL_H

#define PANEL_WIDTH 128
#define PANEL_HEIGHT 10

#define SCORE_X 126
#define SCORE_Y 2

#define HEARTS_X 2
#define HEARTS_Y 2

#include "../../Player.h"
#include "Hearts.h"
#include "Score.h"

class PlayerPanel {
  public:
    void init(Player);
    void render(int, int)

  private:
    Player* player_ = NULL;
    Hearts hearts_;
    Score score_;
}

#endif
