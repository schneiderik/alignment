#ifndef WEAPON_MANAGER_H
#define WEAPON_MANAGER_H

#include "../../global.h";

#define ACTIVE_INDEX_MIN 0
#define ACTIVE_INDEX_MAX 2

class WeaponManager {
  public:
    WeaponManager();
    
    Weapon* weapons[WEAPON_COUNT];
    int activeIndex = ACTIVE_INDEX_MIN;

    void update();
    void render();
    void reset();
    Weapon& get(int);
    void incrementActiveIndex();
    void decrementActiveIndex();
    void swap();
};

#endif
