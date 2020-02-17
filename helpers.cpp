#include "helpers.h"

void renderDigitBlack(int digit, int x, int y) {
  sprites.drawErase(x, y, numberSprite, digit);
}

void renderDigitWhite(int digit, int x, int y) {
  sprites.drawSelfMasked(x, y, numberSprite, digit);   
}

void renderDigit(int digit, int x, int y, int color) {
  color == BLACK
   ? renderDigitBlack(digit, x, y) 
   : renderDigitWhite(digit, x, y);
}

int digitCount(int num) {
  int digitCount = 1;
  
  while (num /= 10) digitCount++;  

  return digitCount;
}

int numberWidth(int num) {
  int count = digitCount(num);
  int digitWidth = numberSprite[0] + 2;
  
  return (count * digitWidth) - 2 + (num < 0 ? 5 : 0);  
}

int roundedHalf(int num) {
  return (int)ceil((float)num/(float)2);
}

void renderNumberAlignRight(int num, int x, int y, int color) {
  if (num == 0) {
    renderDigit(0, x - numberSprite[0], y, color);
    return;
  }

  int index = 0;
  int offset = 0;
  int absNum = abs(num);

  while (absNum) {
    int digit = absNum % 10;
    offset = (index * (numberSprite[0] + 2));

    renderDigit(digit, x - offset - numberSprite[0], y, color);  

    absNum /= 10;
    index++;
  }

  if (num < 0) {
    arduboy.fillRect(
      x - offset - 5 - numberSprite[0],
      y + (NUMBER_HEIGHT/2) - 1,
      3,
      1,
      color
    );  
  }
}

void renderNumberAlignCenter(int num, int x, int y, int color) {
  int centerOffset = roundedHalf(numberWidth(num));
          
  renderNumberAlignRight(num, x + centerOffset, y, color);
}

void fillRectWithStroke(int x, int y, int width, int height, int color) {
  arduboy.fillRect(
    x,
    y,
    width,
    height,
    color == BLACK ? WHITE : BLACK
  );

  arduboy.fillRect(
    x + 1,
    y + 1,
    width - 2,
    height - 2,
    color
  );
}

void renderIndicator(int num, int x, int y, int color) {
  int height = NUMBER_HEIGHT + 4;
  int width = numberWidth(num) + 4;
  int centerOffset = roundedHalf(width - 1);

  arduboy.print(width);
  arduboy.print(centerOffset);

  fillRectWithStroke(
    x - centerOffset, 
    y,
    width,
    height,
    color
  );
  
  renderNumberAlignCenter(
    num,
    x,
    y + 2,
    color == BLACK ? WHITE : BLACK
  );
}

//////////////////////////////
// SOUNDS
//////////////////////////////

void confirmSound() {
  sound.tone(NOTE_C5, 50);
}

void moveSound() {
  sound.tone(NOTE_E4, 50);
}

void swapSound() {
  sound.tone(NOTE_C5, 100);
}

void loseHeartSound() {
  sound.tone(NOTE_E3, 150);
}
