#ifndef WEAPON_MANAGER_H
#define WEAPON_MANAGER_H

#include "../../global.h";
#include "../entities/Weapon.h";

#define WEAPON_MANAGER_CURSOR_MIN 0
#define WEAPON_MANAGER_CURSOR_MAX 2


struct WeaponManagerState {
  bool isReadyToPopulatePreview = false;
  bool isReadyToDropPreview = false;
  bool hasStackedGems = false;
  bool isClearing = false;
};

class WeaponManager {
  public:
    WeaponManager();

    void update();
    void render();
    void reset();
    void incrementCursor();
    void decrementCursor();
    void swap();
    Gem* popLastGemOfRandomWeapon();
    void populatePreviewGemForRandomWeapon();

  private:
    int cursor_ = WEAPON_MANAGER_CURSOR_MIN;

    Weapon weapons_[Weapon::COUNT];
    WeaponManagerState state_;
    WeaponManagerState nextState_;

    void updateWeapons_();
    void initNextState_();
    void applyNextState_();

    Weapon getWeaponAtIndex_(int);
    void dropPreviewGems_();
    void populatePreviewGems_();
    Weapon getRandomWeapon_();

    bool isActiveWeapon_(int);
};

#endif
