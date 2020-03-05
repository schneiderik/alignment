#ifndef WEAPON_H
#define WEAPON_H

#include "../../global.h";

#define WEAPON_STATE_ACTIVE 0
#define WEAPON_STATE_CLEARING 1

class Weapon {
  public:
    Weapon(int i);
        
    void reset(int);
    void render(bool);
    void update();

    void addGem(Gem&);
    void setGemRows(int);

    void empty();
    void clear();
    void activate();

    int getType();
    Gem& getLastGem();
    int getOrder();
    int getEndOfRowX();

    bool isFull();
    bool isOverflowed();
    bool isEmpty();
    bool isClearing();
    bool isActive();

  private:
    int type_;
    int state_ = WEAPON_STATE_ACTIVE;
    int y_;
    int gemCount_ = 0;
    Gem* lastGem_ = NULL;

    void updateY_();
    void updateClearing_();

    bool lastGemsMatch_();
    void popLastGems_();

    void renderIcon_(bool);
    void renderDivider_();
};

#endif
