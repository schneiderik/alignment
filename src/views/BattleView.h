#ifndef BATTLE_VIEW_H
#define BATTLE_VIEW_H

#include "../../global.h"
#include "View.h"
#include "../entities/Puzzle.h"
#include "../entities/PlayerPanel.h"
#include "../entities/EnemyPanel.h"

#define PLAYER_PANEL_X 0
#define PLAYER_PANEL_Y 0

#define PUZZLE_X 0
#define PUZZLE_Y 14

#define ENEMY_PANEL_X 104
#define ENEMY_PANEL_Y 12

#define PAUSED_X 50
#define PAUSED_Y 28

class BattleView: public View {
  public:    
    void init(const Game&) override;
    void handleInput(const Game&) override;
    void update(const Game&) override;
    void render(const Game&) override;
    void navigateTo(const Game&) override;

  private:
    void renderPaused();

    EnemyPanel enemyPanel_;
    PlayerPanel playerPanel_;
    Puzzle puzzle_;

    int paused = false;
};

#endif
