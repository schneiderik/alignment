#ifndef BATTLE_H
#define BATTLE_H

#include "global.h"

class Battle {
  public:
    Battle() {};

    void update(Game&);
    void render(Game&);

  private:
    int hearts_ = HEARTS_MAX;
};

#endif
