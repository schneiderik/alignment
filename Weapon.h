#ifndef WEAPON_H
#define WEAPON_H

enum WEAPON_TYPES {
  WEAPON_TYPE_SWORD,
  WEAPON_TYPE_HAMMER,
  WEAPON_TYPE_ARROW,
  WEAPON_TYPE_STAFF
};

#define WEAPON_GEM_MAX 6

#define WEAPON_ACTIVE_INDICATOR_WIDTH 12
#define WEAPON_ACTIVE_INDICATOR_HEIGHT 12

#define WEAPON_ICON_X_OFFSET 2
#define WEAPON_ICON_Y_OFFSET 2

#define WEAPON_DIVIDER_WIDTH 1
#define WEAPON_DIVIDER_HEIGHT 10
#define WEAPON_DIVIDER_Y_OFFSET 1

#define WEAPON_DIVIDER_X_OFFSET WEAPON_ACTIVE_INDICATOR_WIDTH + 2
#define WEAPON_GEMS_X_OFFSET WEAPON_DIVIDER_X_OFFSET + WEAPON_DIVIDER_WIDTH + 2
#define WEAPON_GEMS_Y_OFFSET 1
#define WEAPON_GEM_SPACING 2

#include "global.h"
#include "Gem.h"

class Weapon {
  public:
    Weapon();

    void render(int, int, bool);
    void update();

    void setType(int);
    int getGemCount();
    int getGemsMaxX();
    Gem* getGems();
    void addGem(Gem&);
    void clearGem(int);
    void emptyGems(); 

    bool isWaitingForAnimation();

  private:
    int type_;
    int gemCount_ = 0;  
    Gem* gems_;
    
    void renderActiveIcon_(int, int);
    void renderInactiveIcon_(int, int);
    void renderDivider_(int, int);
};

#endif
