#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduboy2.h>
#include <ArduboyTones.h>

extern Arduboy2 arduboy;
extern Sprites sprites;
extern ArduboyTones sound;

#include "images.h"

class Game;
class Gem;
class Weapon;

#include "helpers.h"

#define FPS 60
#define INTERVAL_LENGTH 30
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define HEALTH_MAX 3
#define WEAPON_COUNT 4
#define WEAPON_GEMS_MAX 7
#define GEM_TYPE_COUNT 5
#define PREVIEW_GEM_X 92
#define PREVIEW_THRESHOLD_X 89
#define INITIAL_GAME_SPEED 8
#define GRAVITY_ACCELERATION 1
#define NUMBER_HEIGHT 6
#define SMALL_NUMBER_HEIGHT 5

const int weaponYOffsets[WEAPON_COUNT] = {13, 25, 37, 49};
const int gemYOffsets[WEAPON_COUNT] = {14, 26, 38, 50};
const int gemXOffsets[WEAPON_GEMS_MAX + 1] = {17, 29, 41, 53, 65, 77, 89};

extern Game* game;

#endif
