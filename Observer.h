#ifndef OBSERVER_H
#define OBSERVER_H

#include "global.h"

class Observer {
  public:
    virtual ~Observer() {}
    virtual void onNotify(const Player& player, Event event) = 0;
    virtual void onNotify(const Enemy& enemy, Event event) = 0;
    virtual void onNotify(const Weapon& weapon, Event event) = 0;
};

#endif
