#ifndef WEAPON_MANAGER_H
#define WEAPON_MANAGER_H

#include "../../global.h";
#include "../entities/Weapon.h";

#define ACTIVE_INDEX_MIN 0
#define ACTIVE_INDEX_MAX 2

class WeaponManager {
  public:
    WeaponManager();
    
    Weapon* weapons[Weapon::COUNT];
    int activeIndex = ACTIVE_INDEX_MIN;

    void update();
    void render();
    void reset();
    Weapon& get(int);
    void incrementActiveIndex();
    void decrementActiveIndex();
    void swap();

    bool isClearing();
    bool isActive();

  private:
    const int STATE_ACTIVE = 0;
    const int STATE_CLEARING = 1;

    int state_ = STATE_ACTIVE;
};

#endif
