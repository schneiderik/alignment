#ifndef GEM_H
#define GEM_H

#include "global.h";

#define GEM_STATE_INACTIVE 0
#define GEM_STATE_ACTIVE 1
#define GEM_STATE_CLEARING 2

class Gem {
  public:
    Gem();
    
    Gem& operator=(const Gem& gem) {
      if (this != &gem) {
        type = gem.type;
        row = gem.row;
        x = gem.x;
        y = gem.y;
        state = gem.state;
        velocityX = gem.velocityX;
        velocityY = gem.velocityY;
      }
      return *this;
    }
    
    int type;
    int row;
    int x;
    int y;
    int velocityX;
    int velocityY;
    int initialVelocityY;
    int state = GEM_STATE_ACTIVE;

    void render();
    void update();
    void updateX();
    void updateY();
    void updateClear();

    bool isInactive();
    bool isActive();
    bool isClearing();
    
    Weapon& getWeapon();
    bool atEndOfRowX();
    void clear();
};

#endif
