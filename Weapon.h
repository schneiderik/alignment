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

#define WEAPON_MOVE_INCREMENT 3
#define WEAPON_MOVE_FRAME_LENGTH 1

#include "global.h"
#include "Gem.h"

class Weapon {
  public:
    Weapon();

    void render(bool);
    void update();

    void setType(int);
    int getType();
    void setX(int);
    int getX();
    int getGemX(int);
    void setY(int);
    void setTargetY(int);
    int getGemsY();
    int getGemCount();
    int getGemsMaxX();
    Gem* getGems();
    void addGem(int);
    void clearGemAtIndex(int);
    void removeGemAtIndex(int);
    void emptyGems(); 
    
    bool isStopped();
    bool isClearing();
    bool isSwapping();

  private:
    int type_;
    int x_ = 0;
    int y_ = 0;
    int targetY_ = 0;
    int gemCount_ = 0;  
    Gem* gems_;
    int* gemPositions_;
    int moveInterval_ = 0;

    void updateGems_();
    void removeGems_();
    void updateY_();
    
    void renderActiveIcon_();
    void renderInactiveIcon_();
    void renderDivider_();
};

#endif
