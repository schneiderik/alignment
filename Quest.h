#ifndef QUEST_H
#define QUEST_H

#include "global.h"

class Quest {
  public:
    Quest() {};

    void update(Game&);
    void render(int);

  private:
    int cursorOffset_ = 0;
    int cursorInterval_ = 0;
    boolean cursorAnimationDirection_ = true;
};

#endif
