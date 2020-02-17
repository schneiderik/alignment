#ifndef HELPERS_H
#define HELPERS_H

#include "global.h"

void renderDigitBlack(int, int, int);
void renderDigitWhite(int, int, int);
void renderDigit(int, int, int, int);
int digitCount(int);
int numberWidth(int);
void renderNumberAlignRight(int, int, int, int);
void renderNumberAlignCenter(int, int, int, int);

void fillRectWithStroke(int, int, int, int, int);
void renderIndicator(int, int, int, int);

void confirmSound();
void moveSound();
void swapSound();
void loseHeartSound();

#endif
