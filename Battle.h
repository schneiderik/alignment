#ifndef BATTLE_H
#define BATTLE_H

#include "global.h"
#include "Puzzle.h"

#define BATTLE_PAUSED_TEXT_X 50
#define BATTLE_PAUSED_TEXT_Y 28

#define BATTLE_HEARTS_X 2
#define BATTLE_HEARTS_Y 2

#define BATTLE_SCORE_X 97
#define BATTLE_SCORE_Y 2

#define BATTLE_CURSOR_MAX 2
#define BATTLE_INTERVAL 10

#define BATTLE_ENEMY_PANEL_X 104
#define BATTLE_ENEMY_PANEL_Y 0
#define BATTLE_ENEMY_PANEL_WIDTH 24
#define BATTLE_ENEMY_PANEL_HEIGHT 64

#define BATTLE_ENEMY_PORTRAIT_X 106
#define BATTLE_ENEMY_PORTRAIT_Y 2

#define BATTLE_ENEMY_HEALTH_X 106
#define BATTLE_ENEMY_HEALTH_Y 60
#define BATTLE_ENEMY_HEALTH_WIDTH 20
#define BATTLE_ENEMY_HEALTH_HEIGHT 2

class Battle {
  public:
    Battle() {};

    void handleInput(Game&);
    void update(Game&);
    void render(Game&);

  private:
    void handleRightButtonPress_();
    void handleAButtonPress_();
    void handleUpButtonPress_();
    void handleDownButtonPress_();
    
    void renderPaused_();
    void renderEnemy_(int);
    void renderEnemyPanel_();
    void renderEnemyPortrait_(int);
    void renderEnemyHealth_();

    Puzzle puzzle_;
    bool paused_ = false;
    int interval_ = 0;
};

#endif
