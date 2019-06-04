#ifndef GAME_H
#define GAME_H

#include "global.h"
#include "Title.h"
#include "Quest.h"
#include "Battle.h"

class Game {
  public:
    Game() {};

    void setState(int);
    void setCurrentEnemyType(int);
    int getCurrentEnemyType();
    void update();
    void render();

  private:
    int state_ = GAME_STATES::GAME_STATE_TITLE;
    int currentEnemyType_ = ENEMY_TYPES::ENEMY_TYPE_SKELETON;

    Title title_;
    Quest quest_;
    Battle battle_;
};

#endif
