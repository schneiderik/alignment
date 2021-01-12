#include "StatBar.h"

void StatBar::renderBar(uint8_t x, uint8_t y)
{
  arduboy.fillRect(
    x,
    y,
    STAT_BAR_WIDTH,
    STAT_BAR_HEIGHT
  );
}

void StatBar::renderHeart(uint8_t x, uint8_t y, uint8_t frame)
{
  sprites.drawErase(
    x,
    y,
    heartSprite,
    frame
  );
}

void StatBar::renderHearts(uint8_t x, uint8_t y, uint8_t health)
{
  for (uint8_t i = 0; i < PLAYER_HEALTH_MAX; i++)
  {  
    renderHeart(
      x + (i * (heartSprite[0] + 1)),
      y,
      i < health ? 0 : 1
    );
  }  
}

void StatBar::render(
  uint8_t x,
  uint8_t y,
  uint8_t health,
  unsigned long int score
)
{
  renderBar(x + STAT_BAR_X, y + STAT_BAR_Y);
  renderHearts(x + STAT_BAR_HEARTS_X, y + STAT_BAR_HEARTS_Y, health);

  Number::render(
    score,
    x + STAT_BAR_SCORE_X,
    y + STAT_BAR_SCORE_Y,
    ALIGN_RIGHT,
    BLACK
  );
}
