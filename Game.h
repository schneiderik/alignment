#ifndef GAME_H
#define GAME_H

#include "global.h"

#include "Audio.h"
#include "Player.h"
#include "Enemy.h"
#include "Event.h"
#include "Observer.h"

#include "src/views/View.h"
#include "src/views/TitleView.h"
#include "src/views/InfoView.h"
#include "src/views/QuestView.h"
#include "src/views/BattleView.h"
#include "src/views/WinView.h"
#include "src/views/LoseView.h"

class Game: public Observer {
  public:
    Game();

    void handleInput();
    void update();
    void render();
    void reset();

    void onNotify(const Player&, Event) override;
    void onNotify(const Enemy&, Event) override;
    
    void navigateTo(View*);
    void goToTitleView();
    void goToInfoView();
    void goToQuestView();
    void goToBattleView();
    void goToWinView();
    void goToLoseView();

    Player& getPlayer();
    Enemy& getCurrentEnemy();
    Audio& getAudio();

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
