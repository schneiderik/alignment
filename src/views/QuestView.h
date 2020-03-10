#ifndef QUEST_VIEW_H
#define QUEST_VIEW_H

#include "../../global.h"
#include "../../Enemy.h"
#include "../animations/TranslateAnimation.h"

class QuestView {
  public:
    QuestView();

    void handleInput();
    void update();
    void render();

  private:
    static const int DATA_LENGTH = 2;
    static const int DATA_X = 0;
    static const int DATA_Y = 1;
    static const int DATA[Enemy::COUNT][DATA_LENGTH];

    static int getXData_(int);
    static int getYData_(int);

    const int GRAVE_INDEX = 6;
    const int MYSTERY_INDEX = 5;

    const int BOUNCE_ANIMATION_LOWER_LIMIT = -1;
    const int BOUNCE_ANIMATION_UPPER_LIMIT = 1;
    const int BOUNCE_ANIMATION_SPEED = 8;
    const bool BOUNCE_ANIMATION_LOOP = true;

    void renderText_();
    void renderCursor_();
    void renderPaths_();
    void renderEnemies_();
    void renderEnemy_(int);

    TranslateAnimation* bounceAnimation_;
};

#endif
