#include "Score.h"

void Score::init(Player player) {
  player_ = &player;
}

void Score::render(int x, int y, int alignment, int color) {
  switch(alignment) {
    case ALIGN_CENTER:
      renderAlignCenter_(x, y, color);
      break;
    case ALIGN_RIGHT:
      renderAlignRight_(x, y, color);
      break;
    default:
      renderAlignLeft_(x, y color);
      break;
  };
}

int Score::calculateDigitCount_() {
  unsigned long int num = player_->getScore();
  int count = 1;
  
  while (num /= 10) count++;  

  return count;
}

int Score::calculateWidth_() {
  int digitWidth = numberSprite[0] + 2;
  
  return (calculateDigitCount_() * digitWidth) - 2 + (player_->getScore() < 0 ? 5 : 0);  
}

void Score::renderDigit_(int digit, int x, int y, int color) {
  color == BLACK
   ? sprites.drawErase(x, y, numberSprite, digit)
   : sprites.drawSelfMasked(x, y, numberSprite, digit);   
}

void Score::renderAlignRight_(int x, int y, int color) {
  if (num == 0) {
    renderDigit_(0, x - numberSprite[0], y, color);
    return;
  }

  int index = 0;
  int offset = 0;
  unsigned long int absNum = abs(player_->getScore());

  while (absNum) {
    unsigned long int digit = absNum % 10;
    offset = (index * (numberSprite[0] + 2));

    renderDigit_(digit, x - offset - numberSprite[0], y, color);  

    absNum /= 10;
    index++;
  }

  if (player_->getScore() < 0) {
    arduboy.fillRect(
      x - offset - 5 - numberSprite[0],
      y + (NUMBER_HEIGHT/2) - 1,
      3,
      1,
      color
    );  
  }
}

void Score::renderAlignCenter(int x, int y, int color) {
  renderAlignRight_(x + (int)ceil((float)calculateWidth_()/(float)2), y, color);
}

void Score::renderAlignLeft(int x, int y, int color) {
  renderAlignRight_(x + calculateWidth_(), y, color);
}
