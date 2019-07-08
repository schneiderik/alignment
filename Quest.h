#ifndef QUEST_H
#define QUEST_H

#include "global.h"

#define QUEST_GRAVE_INDEX 5

#define QUEST_CURSOR_OFFSET_X 8
#define QUEST_CURSOR_OFFSET_Y 4

#define QUEST_CURSOR_ANIMATION_INTERVAL 10
#define QUEST_CURSOR_ANIMATION_MAX_OFFSET 1
#define QUEST_CURSOR_ANIMATION_MIN_OFFSET -1

class Quest {
  public:
    Quest() {};

    void handleInput(Game&);
    void update();
    void render(Game&);

  private:
    int cursorOffset_ = 0;
    int cursorInterval_ = 0;
    int cursorVelocity_ = -1;
    void renderCursor_(Game&);
    void renderEnemies_(Game&);
};

#endif
