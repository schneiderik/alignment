#ifndef GAME_H
#define GAME_H

#include "global.h"
#include "Title.h"
#include "Info.h"
#include "Quest.h"
#include "Battle.h"
#include "Enemy.h"
#include "Player.h"


#define GAME_STATE_TITLE 0
#define GAME_STATE_INFO 1
#define GAME_STATE_QUEST 2
#define GAME_STATE_BATTLE 3
#define GAME_STATE_LOSE 4
#define GAME_STATE_WIN 5

class Game {
  public:
    Game() {};

    void handleInput();
    void update();
    void render();

    void goToTitleScreen();
    void goToInfoScreen();
    void goToQuestScreen();
    void goToBattleScreen();
    void goToLoseScreen();
    void goToWinScreen();

    void defeatEnemy();
    
    Player player;
    Enemy enemy;
    Title title;
    Info info;
    Quest quest;
    Battle battle;

  private:
    int state_ = GAME_STATE_BATTLE;
};

#endif
