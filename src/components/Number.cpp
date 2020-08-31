#include "Number.h"

namespace
{
  int calculateDigitCount(unsigned long int value)
  {
    unsigned long int num = value;
    int count = 1;
    
    while (num /= 10) count++;  

    return count;
  }

  int calculateWidth(unsigned long int value)
  {
    int digitWidth = numberSprite[0] + 2;
    
    return (calculateDigitCount(value) * digitWidth) - 2;  
  }

  void renderDigit(
    uint8_t digit,
    int x,
    int y,
    uint8_t color
  )
  {
    color == BLACK
     ? sprites.drawErase(x, y, numberSprite, digit)
     : sprites.drawSelfMasked(x, y, numberSprite, digit);   
  }

  void renderAlignRight(
    unsigned long int value,
    int x,
    int y,
    uint8_t color
  )
  {
    unsigned long int num = value;

    if (num == 0)
    {
      renderDigit(0, x - numberSprite[0], y, color);
      return;
    }

    uint8_t index = 0;
    uint8_t offset = 0;

    while (num)
    {
      uint8_t digit = num % 10;
      offset = (index * (numberSprite[0] + 2));

      renderDigit(
        digit,
        x - offset - numberSprite[0],
        y,
        color
      );  

      num /= 10;
      index++;
    }
  }

  void renderAlignCenter(
    unsigned long int value,
    int x,
    int y,
    uint8_t color
  )
  {
    renderAlignRight(
      value,
      x + (int)ceil((float)calculateWidth(value)/(float)2),
      y,
      color
    );
  }

  void renderAlignLeft(
    unsigned long int value,
    int x,
    int y,
    uint8_t color
  )
  {
    renderAlignRight(
      value,
      x + calculateWidth(value),
      y,
      color
    );
  }
};

void Number::render(
  unsigned long int value,
  int x,
  int y,
  uint8_t alignment,
  uint8_t color
)
{
  switch(alignment) {
    case ALIGN_CENTER:
      renderAlignCenter(value, x, y, color);
      break;
    case ALIGN_RIGHT:
      renderAlignRight(value, x, y, color);
      break;
    default:
      renderAlignLeft(value, x, y, color);
      break;
  };
}
