#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduboy2.h>

extern Arduboy2 arduboy;
extern Sprites sprites;

#define FPS 60
#define INTERVAL_LENGTH 30
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define PREVIEW_GEM_X 91
#define PREVIEW_THRESHOLD_X 85
#define INITIAL_GAME_SPEED 8
#define FAST_FALL_SPEED 4
#define GRAVITY_ACCELERATION 1
#define NUMBER_HEIGHT 6
#define SMALL_NUMBER_HEIGHT 5
#define ENEMY_COUNT 5
#define HEALTH_MAX 3
#define ALIGN_LEFT 0
#define ALIGN_CENTER 1
#define ALIGN_RIGHT 2

#include "images.h"

class Game;
class Weapon;
class Gem;
class Enemy;

#endif
