#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "assets.h"

extern Arduboy2 arduboy;
extern Sprites sprites;
extern ArduboyTones sound;

#define FPS 60
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define GRAVITY 1

#define ALIGN_LEFT 0
#define ALIGN_CENTER 1
#define ALIGN_RIGHT 2

#define PLAYER_HEALTH_MAX 3

#define ENEMY_TYPE_SKELETON 0
#define ENEMY_TYPE_ORC 1
#define ENEMY_TYPE_GOLEM 2
#define ENEMY_TYPE_DEMON 3
#define ENEMY_TYPE_SORCERER 4

#define ENEMY_COUNT 5
#define LAST_ENEMY ENEMY_COUNT - 1
#define ENEMY_DAMAGE_BASE 5
#define ENEMY_ATTACK_INTERVAL_MIN 700
#define ENEMY_ATTACK_INTERVAL_MAX 1200

#define FALL_SPEED_DEFAULT 8
#define FALL_SPEED_FAST 4

#define PUZZLE_X 0
#define PUZZLE_Y 14
#define PUZZLE_CURSOR_MIN 0
#define PUZZLE_CURSOR_MAX 2

#define PAUSED_X 50
#define PAUSED_Y 28

#define PREVIEW_GEM_X 91
#define PREVIEW_THRESHOLD_X 85

#define ATTACK_INTERVAL_MIN 700
#define ATTACK_INTERVAL_MAX 1200

#define ENEMY_FRAME_COUNT 9
#define ENEMY_DAMAGE_FRAME 9
#define ENEMY_ATTACK_EFFECT_FRAME 3

#define FLASH_ANIMATION_INITIAL_VALUE 0
#define FLASH_ANIMATION_LOWER_LIMIT 0
#define FLASH_ANIMATION_UPPER_LIMIT 1
#define FLASH_ANIMATION_DURATION 40
#define FLASH_ANIMATION_COUNT 3
#define FLASH_ANIMATION_LOOP true

#define IDLE_ANIMATION_INITIAL_VALUE 0
#define IDLE_ANIMATION_LOWER_LIMIT 0
#define IDLE_ANIMATION_UPPER_LIMIT 3
#define IDLE_ANIMATION_SPEED 30
#define IDLE_ANIMATION_LOOP false

#define ATTACK_ANIMATION_INITIAL_VALUE 4
#define ATTACK_ANIMATION_LOWER_LIMIT 4
#define ATTACK_ANIMATION_UPPER_LIMIT 9
#define ATTACK_ANIMATION_DURATION 50
#define ATTACK_ANIMATION_COUNT 1
#define ATTACK_ANIMATION_LOOP false

#define PUZZLE_PREVIEW_DIVIDER_X 89
#define PUZZLE_PREVIEW_DIVIDER_Y 0
#define PUZZLE_PREVIEW_DIVIDER_WIDTH 1
#define PUZZLE_PREVIEW_DIVIDER_HEIGHT 49

#define PUZZLE_WEAPONS_X 0
#define PUZZLE_WEAPONS_Y 1

#define FALLING_GEMS_X_MAX 92
#define FALLING_GEMS_X_INCREMENT -3

#define WEAPON_COUNT 4
#define WEAPON_GEM_COUNT 6
#define WEAPON_MOVE_Y_INCREMENT 3

#define GEM_HIDDEN_TYPE -1
#define GEM_POPPING_ANIMATION_START_FRAME 5
#define GEM_POPPING_ANIMATION_END_FRAME 7
#define POPPING_GEM_FRAME_LENGTH 5
#define CLEARING_GEM_FRAME_LENGTH 5


#endif
