#ifndef WEAPON_H
#define WEAPON_H

#include "global.h"

class Weapon {
  public:
    Weapon() {};

    void setType(int);
    int getType();
    void update(Game&);
    void render(int, bool);
    void reset();

  private:
    int type_;
    void renderActiveIcon_(int);
    void renderInactiveIcon_(int);
    void renderDividers_(int);
};

#endif
