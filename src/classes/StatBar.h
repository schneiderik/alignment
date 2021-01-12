#ifndef STAT_BAR_H
#define STAT_BAR_H

#include "../../global.h"

#include "../components/Number.h"

#define STAT_BAR_X 0
#define STAT_BAR_Y 0
#define STAT_BAR_WIDTH 128
#define STAT_BAR_HEIGHT 10
#define STAT_BAR_HEARTS_X 2
#define STAT_BAR_HEARTS_Y 2
#define STAT_BAR_SCORE_X 126
#define STAT_BAR_SCORE_Y 2

struct StatBar
{
  void renderBar(uint8_t, uint8_t);
  void renderHeart(uint8_t, uint8_t, uint8_t);
  void renderHearts(uint8_t, uint8_t, uint8_t);
  void render(uint8_t, uint8_t, uint8_t, unsigned long int);
};

#endif
