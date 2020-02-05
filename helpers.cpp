#include "helpers.h"
#include "Gem.h"

void renderDigitBlack(int digit, int x, int y) {
  sprites.drawErase(x, y, numberSprite, digit);
}

void renderDigitWhite(int digit, int x, int y) {
  sprites.drawOverwrite(x, y, numberSprite, digit);   
}

void renderDigit(int digit, int x, int y, bool black) {
  black 
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

void renderNumberAlignRight(int num, int x, int y, bool black) {
  if (num == 0) {
    renderDigit(0, x - numberSprite[0], y, black);
    return;
  }

  int index = 0;
  int offset = 0;
  int absNum = abs(num);

  while (absNum) {
    int digit = absNum % 10;
    offset = (index * (numberSprite[0] + 2));

    renderDigit(digit, x - offset - numberSprite[0], y, black);  

    absNum /= 10;
    index++;
  }

  if (num < 0) {
    arduboy.fillRect(x - offset - 5 - numberSprite[0], y + (numberSprite[1]/2) - 1, 3, 1, !black);  
  }
}

void renderNumberAlignCenter(int num, int x, int y, bool black) {
  int numWidth = numberWidth(num);
          
  renderNumberAlignRight(num, x + (numWidth / 2), y, black);
}

void removeGemFromArray(Gem** gems, int i, int& size) {
  size--;
  
  for(int j = i; j < size; j++) *gems[j] = *gems[j + 1];
}

Gem& addGemToArray(Gem** gems, Gem& gem, int& size) {
  Gem& nextGem = *gems[size];
  nextGem = gem;
  size++;

  return nextGem;
}