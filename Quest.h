#ifndef QUEST_H
#define QUEST_H

#include "global.h"

#define QUEST_SPRITE_GRAVE_INDEX 6
#define QUEST_SPRITE_MYSTERY_INDEX 5

class Quest {
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
