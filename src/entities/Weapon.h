#ifndef WEAPON_H
#define WEAPON_H

#include "../../global.h";

class Weapon {
  public:
    Weapon(int i);
        
    void reset(int);
    void render(bool);
    void update();

    void addGem(Gem&);
    void popLastGem();
    void clearGems();
    void setGemRows(int);

    bool isFull();
    bool isEmpty();
    void empty();

    int getType();
    Gem& getLastGem();
    int getOrder();
    int getEndOfRowX();

  private:
    int type_;
    int y_;
    int gemCount_;
    Gem* lastGem_ = NULL;

    void renderIcon_(bool);
    void renderDivider_();
};

#endif
