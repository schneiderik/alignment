#ifndef GAME_H
#define GAME_H

#include "src/views/TitleView.h"
#include "src/views/InfoView.h"
#include "src/views/QuestView.h"
#include "src/views/BattleView.h"
#include "src/views/WinView.h"
#include "src/views/LoseView.h"

#include "src/collections/WeaponManager.h"
#include "src/collections/GemManager.h"

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
    
    void goToTitleView();
    void goToInfoView();
    void goToQuestView();
    void goToBattleView();
    void goToWinView();
    void goToLoseView();

    WeaponManager weapons;
    GemManager gems;

  private:
    int state_ = GAME_STATE_TITLE;

    TitleView titleView_;
    BattleView battleView_;
    InfoView infoView_;
    QuestView questView_;
    WinView winView_;
    LoseView loseView_;
};

#endif
