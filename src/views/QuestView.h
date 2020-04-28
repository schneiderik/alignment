#ifndef QUEST_VIEW_H
#define QUEST_VIEW_H

#include "../../global.h"
#include "./View.h"
#include "../../Enemy.h"
#include "../animations/Animation.h"

#define DATA_LENGTH 2
#define DATA_X 0
#define DATA_Y 1

#define GRAVE_INDEX 6
#define MYSTERY_INDEX 5

#define BOUNCE_ANIMATION_INITIAL_VALUE 0
#define BOUNCE_ANIMATION_LOWER_LIMIT -1
#define BOUNCE_ANIMATION_UPPER_LIMIT 1
#define BOUNCE_ANIMATION_SPEED 8
#define BOUNCE_ANIMATION_LOOP true

class QuestView: public View {
  public:
    QuestView();

    void handleInput() override;
    void update() override;
    void render() override;

  private:
    static const int DATA[Enemy::COUNT][DATA_LENGTH];

    static int getXData_(int);
    static int getYData_(int);

    void renderText_();
    void renderCursor_();
    void renderPaths_();
    void renderEnemies_();
    void renderEnemy_(int);

    Animation bounceAnimation_;
};

#endif
