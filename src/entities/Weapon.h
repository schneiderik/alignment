#ifndef WEAPON_H
#define WEAPON_H

#include "../../global.h";

class Weapon {
  public:
    static const int COUNT = 4;
    static const int GEMS_MAX = 7;
    static const int Y_OFFSETS[COUNT];

    Weapon(int i);
        
    void reset(int);
    void render(bool);
    void update();

    void addGem(Gem&);
    bool isClearing();
    void setOrder(int);
    int getEndOfRowX();

  private:
    static const int STATE_ACTIVE = 0;
    static const int STATE_CLEARING = 1;

    int type_;
    int order_;
    int state_ = STATE_ACTIVE;
    int y_;
    int gemCount_ = 0;
    Gem* lastGem_ = NULL;

    void setGemRows_(int);
    void clearGems_();
    void popLastGem_();
    void popLastGems_();

    void empty_();
    void clear_();
    void activate_();
    void adjustY_();

    bool isFull_();
    bool isOverflowed_();
    bool isEmpty_();
    bool isActive_();
    bool isMisaligned_();
    bool isMatchable_();
    bool isCleared_();
    bool lastGemsMatch_();
    bool gemsOutOfOrder_();

    void renderIcon_(bool);
    void renderDivider_();
};

#endif
