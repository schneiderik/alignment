#ifndef HEARTS_H
#define HEARTS_H

#include "../../global.h";
#include "../../Player.h"

class Hearts {
  public:
    void init(Player);
    void render(int, int);

  private:
    Player* player_ = NULL;
}

#endif
