#ifndef ENEMY_H
#define ENEMY_H

#include "global.h"
#include "Event.h"
#include "Weapon.h"

#define ENEMY_DATA_LENGTH 5
#define ENEMY_DATA_HEALTH 0
#define ENEMY_DATA_WEAPON_MODIFIERS 1

class Enemy {
  public:
    static const int SKELETON = 0;
    static const int ORC = 1;
    static const int GOLEM = 2;
    static const int DEMON = 3;
    static const int SORCERER = 4;

    Enemy();
    
    void init(int);
    void initNext();
    void onNotify(Weapon, Event) override;

    void takeDamage(int, int);
    int getType();
    int getHealth();
    int getMaxHealth();
    bool isDead();
    bool isLastEnemy();

  private:
    static const int LAST_ENEMY = ENEMY_COUNT - 1;
    static const int DATA[ENEMY_COUNT][ENEMY_DATA_LENGTH];

    static int getHealthData_(int);
    static int getWeaponModifierData_(int, int);

    int type_;
    int health_;
};

#endif
