#ifndef GAME_H
#define GAME_H

#include "global.h"
#include "Title.h"
#include "Info.h"
#include "Quest.h"
#include "Battle.h"
#include "Win.h"
#include "Lose.h"
#include "Enemy.h"
#include "WeaponManager.h"

#define GAME_STATE_TITLE 0
#define GAME_STATE_INFO 1
#define GAME_STATE_QUEST 2
#define GAME_STATE_BATTLE 3
#define GAME_STATE_WIN 4
#define GAME_STATE_LOSE 5

class Game {
  public:
    void handleInput();
    void update();
    void render();

    void reset();
    
    void goToTitle();
    void goToInfo();
    void goToQuest();
    void goToBattle();
    void goToWin();
    void goToLose();

    bool isClearingGems();
  
    int state = GAME_STATE_TITLE;
    unsigned long int score;
    int clearingGemCount;

    WeaponManager weapons;
    Enemy enemy;  
    Title title;
    Battle battle;
    Info info;
    Quest quest;
    Win win;
    Lose lose;
};

#endif
