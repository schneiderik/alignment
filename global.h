#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "images.h"

#define DEBUG true

#define FPS 60
#define INTERVAL_LENGTH 30

#define ENEMY_COUNT 5
#define LAST_ENEMY ENEMY_COUNT - 1


#define SCORE_INCREMENT 10

#define WEAPON_COUNT 4
#define GEM_COUNT 4

#define ENEMY_DATA_LENGTH 5
#define ENEMY_DATA_HEALTH 0
#define ENEMY_DATA_MODIFIER 1


#define MATCH_MAX 3
#define MATCH_DATA_LENGTH 2
#define MATCH_DATA_X 0
#define MATCH_DATA_Y 1
#define MATCH_EMPTY -1

class Game;


enum ENEMY_TYPES {
  ENEMY_TYPE_SKELETON,
  ENEMY_TYPE_ORC,
  ENEMY_TYPE_GOLEM,
  ENEMY_TYPE_DEMON,
  ENEMY_TYPE_SORCERER
};

extern Arduboy2 arduboy;
extern Sprites sprites;
extern ArduboyTones sound;

#endif
