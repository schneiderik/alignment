#ifndef WEAPON_MANAGER_H
#define WEAPON_MANAGER_H

#include "../../global.h";
#include "../entities/Weapon.h";

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

  private:
    static const int CURSOR_MIN = 0;
    static const int CURSOR_MAX = 2;

    int cursor_ = CURSOR_MIN;

    Weapon* weapons_[Weapon::COUNT];
    WeaponManagerState state_;
    WeaponManagerState nextState_;

    void updateWeapons_();
    void initNextState_();
    void applyNextState_();

    Weapon* getWeaponAtIndex_(int);
    void dropPreviewGems_();
    void populatePreviewGems_();
    void populatePreviewGemForRandomWeapon_();
    Weapon* getRandomWeapon_();

    bool isActiveWeapon_(int);
};

#endif
