#ifndef WEAPON_MANAGER_H
#define WEAPON_MANAGER_H

#include "../../global.h";
#include "../entities/Weapon.h";

class WeaponManager {
  public:
    WeaponManager();

    void update();
    void render();
    void reset();
    void incrementCursor();
    void decrementCursor();
    void swap();
    void slashRandomWeapon();

  private:
    static const int STATE_DEFAULT = 0;
    static const int STATE_PREVIEW_EMPTY = 1;
    static const int STATE_READY_TO_DROP_PREVIEW = 2;
    static const int STATE_CLEARING_GEMS = 3;

    static const int CURSOR_MIN = 0;
    static const int CURSOR_MAX = 2;

    int cursor_ = CURSOR_MIN;
    int state_ = STATE_DEFAULT;

    Weapon* weapons_[Weapon::COUNT];

    void updateWeapons_();
    void updateClearingWeapons_();

    Weapon* getWeaponAtIndex_(int);
    void dropPreviewGems_();
    void populatePreviewGems_();
    void populatePreviewGemForRandomWeapon_();
    Weapon* getRandomWeapon_();

    bool isReadyToPopulatePreview_();
    bool isReadyToDropPreview_();
    bool isClearing_();
    bool isActiveWeapon_(int);
};

#endif
