#ifndef GAME_H
#define GAME_H

#include "src/views/Router.h"
#include "src/views/TitleView.h"
#include "src/views/InfoView.h"
#include "src/views/QuestView.h"
#include "src/views/BattleView.h"
#include "src/views/WinView.h"
#include "src/views/LoseView.h"

class Game {
  public:
    Game();

    void handleInput();
    void update();
    void render();
    
    void goToTitleView();
    void goToInfoView();
    void goToQuestView();
    void goToBattleView();
    void goToWinView();
    void goToLoseView();

    int getGameSpeed();
    void enableFastFall();
    void disableFastFall();
    void forceEnableFastFall();
    void forceDisableFastFall();

  private:
    bool fastFall_ = false;
    bool forcedFastFall_ = false;

    Router router_;
    TitleView titleView_;
    BattleView battleView_;
    InfoView infoView_;
    QuestView questView_;
    WinView winView_;
    LoseView loseView_;
};

#endif
