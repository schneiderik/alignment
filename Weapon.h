#ifndef WEAPON_H
#define WEAPON_H

#include "global.h";

class Weapon {
  public:
    Weapon(int i);
        
    int type;
    int y;
    int gemCount;
    int stackCount;
    Gem* gems[WEAPON_GEMS_MAX];

    bool isFull();
    bool isEmpty();
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
    int getOrder();
    void update();
    void updateY();
    void updateGems();
    int endOfRowX();
    void setGemRows(int);
};

#endif
