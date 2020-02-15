#ifndef QUEST_VIEW_H
#define QUEST_VIEW_H

#include "../../global.h"
#include "../animations/BounceAnimation.h"

#define QUEST_SPRITE_GRAVE_INDEX 6
#define QUEST_SPRITE_MYSTERY_INDEX 5

class QuestView {
  public:
    QuestView();

    void handleInput();
    void update();
    void render();
    void renderText();
    void renderCursor();
    void renderPaths();
    void renderEnemies();
    void renderEnemy(int);

  private:
    const int BOUNCE_LOWER_LIMIT = -1;
    const int BOUNCE_UPPER_LIMIT = 1;
    const int BOUNCE_SPEED = 8;

    BounceAnimation* bounceAnimation_;
};

#endif
