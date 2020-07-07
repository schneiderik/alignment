#ifndef HEARTS_H
#define HEARTS_H

#include "../../Player.h"


class Hearts
  public:
    void init(Player);
    void render(int, int);

  private:
    Player* player_ = NULL;
}

#endif
