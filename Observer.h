#ifndef OBSERVER_H
#define OBSERVER_H

#include "global.h"

class Observer {
  public:
    virtual ~Observer() {}
    virtual void onNotify(const Player& player, Event event) {};
    virtual void onNotify(const Enemy& enemy, Event event) {};
    virtual void onNotify(const Weapon& weapon, Event event) {};
    virtual void onNotify(const Gem& gem, Event event) {};
};

#endif
