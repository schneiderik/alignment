#ifndef PLAYER_H
#define PLAYER_H

#define WEAPON_MATCH_POINTS 100
#define GEM_LOCK_POINTS 10

#include "global.h"
#include "Event.h"
#include "Observer.h"
#include "Subject.h"

class Player: public Observer: public Subject {
  public:
    void reset();

    void onNotify(const Weapon&, Event);
    void onNotify(const Gem&, Event);

    unsigned long int getScore();
    void addScore(int);

    bool isDead();
    void takeDamage();

    int getHealth();
    void resetHealth();

  private:
    unsigned long int score_ = 0;
    int health_ = HEALTH_MAX;
};

#endif
