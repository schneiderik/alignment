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

#define FALL_SPEED_DEFAULT 8
#define FALL_SPEED_FAST 4


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
