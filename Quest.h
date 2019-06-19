#ifndef QUEST_H
#define QUEST_H

#include "global.h"

class Quest {
  public:
    Quest() {};

    void update(Game&);
    void render(Game&);

  private:
    int cursorOffset_ = 0;
    int cursorInterval_ = 0;
    int cursorVelocity_ = -1;
};

#endif
