#ifndef GAME_H
#define GAME_H

#include "global.h"
#include "Title.h"
#include "Info.h"
#include "Quest.h"
#include "Battle.h"
#include "Enemy.h"
#include "Player.h"

class Game {
  public:
    Game() {};

    void setState(int);
    void handleInput();
    void update();
    void render();
    Player player;
    Enemy enemy;

  private:
    int state_ = GAME_STATES::GAME_STATE_TITLE;

    Title title_;
    Info info_;
    Quest quest_;
    Battle battle_;
};

#endif
