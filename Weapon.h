#ifndef WEAPON_H
#define WEAPON_H

#include "global.h";

class Weapon {
  public:
    Weapon(int i);
        
    int type;
    int y;
    int gemCount;
    Gem* lastGem = NULL;

    bool isFull();
    bool isEmpty();
    void addGem(Gem&);
    void popLastGem();
    void clearGems();
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
