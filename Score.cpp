#include "Score.h"

unsigned long int Score::get() {
  return value_;
}

void Score::render() {
  unsigned long int score = value_;
  
  if (score == 0) {
    sprites.drawOverwrite(
      SCORE_X,
      SCORE_Y,
      numberSprite,
      0
    );

    return;
  }

  int index = 0;

  while (score) {
    int digit = score % 10;

    sprites.drawOverwrite(
      SCORE_X - (index * (numberSprite[0] + NUMBER_SPACING)),
      SCORE_Y,
      numberSprite,
      digit
    );

    score /= 10;
    index++;
  }
}

void Score::increase() {
  // increase score
}

void Score::reset() {
  value_ = 0;
}
