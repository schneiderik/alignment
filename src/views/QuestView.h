#ifndef QUEST_VIEW_H
#define QUEST_VIEW_H

#include "../../global.h"

#define QUEST_SPRITE_GRAVE_INDEX 6
#define QUEST_SPRITE_MYSTERY_INDEX 5

class QuestView {
  public:
    void handleInput();
    void update();
    void render();
    void renderText();
    void renderCursor();
    void renderPaths();
    void renderEnemies();
    void renderEnemy(int);

    int cursorOffset = 0;
    int cursorVelocity = -1;
};

#endif
