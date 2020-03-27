#ifndef WEAPON_H
#define WEAPON_H

#include "../../global.h";

class Weapon {
  public:
    static const int COUNT = 4;
    static const int GEM_MAX = 7;
    static const int Y_OFFSETS[COUNT];
    static const int GEM_X_OFFSETS[GEM_MAX];

    Weapon(int i);
        
    void reset(int);
    void render(bool);
    void update();

    void createPreviewGem();
    void dropPreviewGem();
    void stackFallingGem();
    void swap(Weapon&);

    bool isClearing();
    bool hasPreviewGem();
    bool hasFallingGem();
    bool previewIsEmpty();
    bool fallingGemAboveX(int);

    int getEndOfRowX();
    int getOrder();
    void setOrder(int);
    Gem* getPreviewGem();
    void setPreviewGem(Gem*);
    Gem* getFallingGem();
    void setFallingGem(Gem*);
    void setGemStackTargetY(int);

  private:
    static const int STATE_DEFAULT = 0;
    static const int STATE_CLEARING = 1;

    const int MOVE_Y_INCREMENT = 3;

    int type_;
    int order_;
    int state_ = STATE_DEFAULT;
    int y_;
    int gemCount_ = 0;
    Gem* lastGem_ = NULL;
    Gem* fallingGem_ = NULL;
    Gem* previewGem_ = NULL;

    void updateY_();
    void updateGemStack_();
    void updateFallingGem_();

    void setGemRows_(int);
    void popLastGems_();
    void clearStackedGems_();
    void removeGemFromStack_(Gem*);

    void adjustY_();

    bool isFull_();
    bool isOverflowed_();
    bool isEmpty_();
    bool isMisaligned_();
    bool isMatchable_();
    bool isCleared_();
    bool lastGemsMatch_();
    bool gemsOutOfOrder_();

    void renderGemStack_();
    void renderIcon_(bool);
    void renderDivider_();
};

#endif
