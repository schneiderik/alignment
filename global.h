#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduboy2.h>
#include <ArduboyTones.h>

extern Arduboy2 arduboy;
extern Sprites sprites;
extern ArduboyTones sound;

#include "images.h"

class Player;
class Enemy;
class Game;
class Gem;
class Weapon;
class WeaponManager;
class GemManager;

#include "helpers.h"

#define FPS 60
#define INTERVAL_LENGTH 30
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define PREVIEW_GEM_X 92
#define PREVIEW_THRESHOLD_X 86
#define INITIAL_GAME_SPEED 8
#define GRAVITY_ACCELERATION 1
#define NUMBER_HEIGHT 6
#define SMALL_NUMBER_HEIGHT 5

extern Game* game;
extern Player* player;
extern Enemy* enemy;
extern WeaponManager* weaponManager;
extern GemManager* gemManager;

#endif
