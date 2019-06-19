#ifndef BATTLE_H
#define BATTLE_H

#include "global.h"
#include "Enemy.h"

class Battle {
  public:
    Battle() {};

    void update(Game&);
    void render(Game&);
    void setEnemy(int);

  private:
    int hearts_ = HEARTS_MAX;
    void renderScore_(unsigned long int);
    void renderHearts_();
    Enemy enemy_;
};

#endif
