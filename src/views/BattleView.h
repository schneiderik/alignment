#ifndef BATTLE_VIEW_H
#define BATTLE_VIEW_H

#include "../../global.h"
#include "View.h"
#include "../collections/WeaponManager.h"

#define PLAYER_PANEL_X 0
#define PLAYER_PANEL_Y 0

#define PUZZLE_X 0
#define PUZZLE_Y 15

#define ENEMY_PANEL_X 104
#define ENEMY_PANEL_Y 12

#define ATTACK_INTERVAL_MIN 700
#define ATTACK_INTERVAL_MAX 1200

#define PAUSED_X 50
#define PAUSED_Y 28

class BattleView: public View {
  public:    
    void init(Game) override;
    void handleInput(Game) override;
    void update(Game) override;
    void render(Game) override;
    void navigateTo(Game) override;

  private:
    void renderPaused();
    void attack_();

    EnemyPanel enemyPanel_;
    PlayerPanel playerPanel_;
    Puzzle puzzle_;
    Interval attackInterval_;

    int paused = false;
};

#endif
