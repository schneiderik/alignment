#ifndef GAME_H
#define GAME_H

#include "Audio.h"
#include "Player.h"
#include "Enemy.h"

#include "src/views/View.h"
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
    
    void navigateTo(View*);
    void goToTitleView();
    void goToInfoView();
    void goToQuestView();
    void goToBattleView();
    void goToWinView();
    void goToLoseView();

    Player getPlayer();
    Enemy getCurrentEnemy();
    Audio getAudio();

  private:
    View* view_ = NULL;

    TitleView titleView_;
    BattleView battleView_;
    InfoView infoView_;
    QuestView questView_;
    WinView winView_;
    LoseView loseView_;

    Player player_;
    Enemy enemy_;
    Audio audio_;
};

#endif
