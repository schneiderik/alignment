#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduboy2.h>
#include <ArduboyTones.h>

extern Arduboy2 arduboy;
extern Sprites sprites;
extern ArduboyTones sound;

#include "images.h"

class Gem;
class Weapon;

#define FPS 60
#define INTERVAL_LENGTH 30
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define GAME_STATE_TITLE 0
#define GAME_STATE_INFO 1
#define GAME_STATE_QUEST 2
#define GAME_STATE_BATTLE 3
#define GAME_STATE_WIN 4
#define GAME_STATE_LOSE 5

#define TITLE_STATE_PLAY 0
#define TITLE_STATE_INFO 1
#define TITLE_STATE_SFX 2

#define TITLE_STATE_COUNT 3
#define LAST_TITLE_STATE TITLE_STATE_COUNT - 1

#define QUEST_SPRITE_GRAVE_INDEX 6
#define QUEST_SPRITE_MYSTERY_INDEX 5

#define HEALTH_MAX 3

#define ENEMY_COUNT 5
#define LAST_ENEMY ENEMY_COUNT - 1

#define ENEMY_HEALTH_BAR_WIDTH_MAX 20

#define ENEMY_TYPE_SKELETON 0
#define ENEMY_TYPE_ORC 1
#define ENEMY_TYPE_GOLEM 2
#define ENEMY_TYPE_DEMON 3
#define ENEMY_TYPE_SORCERER 4

#define ENEMY_DATA_LENGTH 7
#define ENEMY_DATA_HEALTH 0
#define ENEMY_DATA_MODIFIER 1
#define ENEMY_DATA_QUEST_X 5
#define ENEMY_DATA_QUEST_Y 6

#define BATTLE_CURSOR_MIN 0
#define BATTLE_CURSOR_MAX 2

#define WEAPON_COUNT 4

#define WEAPON_TYPE_SWORD 0
#define WEAPON_TYPE_HAMMER 1
#define WEAPON_TYPE_ARROW 2
#define WEAPON_TYPE_STAFF 3

#define WEAPON_GEMS_MAX 6

#define GEM_TYPE_COUNT 5

#define FALLING_GEMS_MAX 2
#define PREVIEW_GEMS_MAX 2
#define POPPING_GEMS_MAX 4
#define CLEARING_GEMS_MAX 14

#define PREVIEW_GEM_X 92
#define PREVIEW_THRESHOLD_X 89

#define INITIAL_GAME_SPEED 8

#define GRAVITY_ACCELERATION 1

#define GEM_POPPING_ANIMATION_START_FRAME 5
#define GEM_POPPING_ANIMATION_END_FRAME 7

#define ENEMY_TAKE_DAMAGE_ANIMATION_FRAME_LENGTH 3
#define ENEMY_TAKE_DAMAGE_ANIMATION_START_FRAME 0
#define ENEMY_TAKE_DAMAGE_ANIMATION_END_FRAME 12

#define ENEMY_TAKE_DAMAGE_FLASH_LENGTH 5
#define ENEMY_TAKE_DAMAGE_FLASH_COUNT_MAX 5

#define ENEMY_TAKE_DAMAGE_INDICATOR_FRAME_LENGTH 5
#define ENEMY_TAKE_DAMAGE_INDICATOR_START_FRAME 0
#define ENEMY_TAKE_DAMAGE_INDICATOR_END_FRAME 6
#define ENEMY_TAKE_DAMAGE_INDICATOR_X 111
#define ENEMY_TAKE_DAMAGE_INDICATOR_INITIAL_Y 36

//////////////////////////////
// CONSTANTS
//////////////////////////////

const int ENEMY_DATA[ENEMY_COUNT][ENEMY_DATA_LENGTH] = {
  {100, 0, 0, 0, 0, 5, 16},
  {200, 0, 0, 0, 0, 29, 31},
  {200, -1, 2, -2, 1, 53, 16},
  {150, -1, -1, 2, 0, 77, 31},
  {250, 2, -1, -1, -2, 101, 16}
};
const int weaponYOffsets[WEAPON_COUNT] = {13, 25, 37, 49};
const int gemYOffsets[WEAPON_COUNT] = {14, 26, 38, 50};
const int gemXOffsets[WEAPON_GEMS_MAX + 1] = {17, 29, 41, 53, 65, 77, 89};

extern Gem* tmpGem;
extern Weapon* tmpWeapon;
extern Weapon* weapons[WEAPON_COUNT];
extern Gem* weaponGems[WEAPON_COUNT][WEAPON_GEMS_MAX];
extern Gem* previewGems[PREVIEW_GEMS_MAX];
extern Gem* fallingGems[FALLING_GEMS_MAX];
extern Gem* poppingGems[POPPING_GEMS_MAX];
extern Gem* clearingGems[CLEARING_GEMS_MAX];

#endif
