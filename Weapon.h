#ifndef WEAPON_H
#define WEAPON_H

#include "global.h";

class Weapon {
  public:
    Weapon(int i);
    
    Weapon& operator=(const Weapon&);
    
    int type;
    int y;
    int gemCount;
    int stackCount;
    Gem* gems[WEAPON_GEMS_MAX];

    bool isFull();
    void addGem(Gem&);
    Gem& getGem(int);
    Gem& getLastGem();
    Gem& getNextGem();
    void popLastGem();
    void clearGems();
    bool isClearing();
    void empty();
    void reset(int);
    void render(bool);
    void renderIcon(bool);
    void renderDivider();
    void renderGems();
    void swap(Weapon&);
    int getOrder();
    void update();
    void updateY();
    void updateGems();
    int endOfRowX();
};

#endif
