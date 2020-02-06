#ifndef WEAPON_MANAGER_H
#define WEAPON_MANAGER_H

#include "global.h";

class WeaponManager {
  public:
    WeaponManager();
    
    Weapon* weapons[WEAPON_COUNT];

    void update();
    void render(int);
    Weapon& get(int);

    bool isClearing();
};

#endif
