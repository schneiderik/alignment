#include "Weapon.h"

void Weapon::setType(int type) {
  type_ = type;
}

int Weapon::getType() {
  return type_;
}

void Weapon::reset() {
  // reset gems and stuff
}

void Weapon::render(int pos, bool active) {
  int yOffset = pos * (weaponSprite[1] + WEAPON_SPACING);
  
  if (active) {
    renderActiveIcon_(yOffset);
  } else {
    renderInactiveIcon_(yOffset);
  }

  renderDividers_(yOffset);
}

void Weapon::renderActiveIcon_(int yOffset) {
  arduboy.fillRect(
    WEAPON_ACTIVE_X,
    WEAPON_ACTIVE_Y + yOffset,
    WEAPON_ACTIVE_WIDTH,
    WEAPON_ACTIVE_HEIGHT
  );
  
  sprites.drawErase(
    WEAPON_ICON_X ,
    WEAPON_ICON_Y + yOffset,
    weaponSprite,
    type_
  );  
}

void Weapon::renderInactiveIcon_(int yOffset) {
  sprites.drawOverwrite(
    WEAPON_ICON_X,
    WEAPON_ICON_Y + yOffset,
    weaponSprite,
    type_
  );  
}

void Weapon::renderDividers_(int yOffset) {
  arduboy.fillRect(
    WEAPON_DIVIDER_LEFT_X,
    WEAPON_DIVIDER_Y + yOffset,
    WEAPON_DIVIDER_WIDTH,
    WEAPON_DIVIDER_HEIGHT
  );

  arduboy.fillRect(
    WEAPON_DIVIDER_RIGHT_X,
    WEAPON_DIVIDER_Y + yOffset,
    WEAPON_DIVIDER_WIDTH,
    WEAPON_DIVIDER_HEIGHT
  ); 
}
