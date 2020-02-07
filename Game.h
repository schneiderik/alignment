#ifndef GAME_H
#define GAME_H

#include "global.h";

#define GAME_STATE_TITLE 0
#define GAME_STATE_INFO 1
#define GAME_STATE_QUEST 2
#define GAME_STATE_BATTLE 3
#define GAME_STATE_WIN 4
#define GAME_STATE_LOSE 5

class Game {
  public:
    void goToTitle();
    void goToInfo();
    void goToQuest();
    void goToBattle();
    void goToWin();
    void goToLose();
  
    int state = GAME_STATE_TITLE;
};

#endif
