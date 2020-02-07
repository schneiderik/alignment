#ifndef HELPERS_H
#define HELPERS_H

#include "global.h"

void renderDigitBlack(int, int, int);
void renderDigitWhite(int, int, int);
void renderDigit(int, int, int, bool);
int digitCount(int);
int numberWidth(int);
void renderNumberAlignRight(int, int, int, bool);
void renderNumberAlignCenter(int, int, int, bool);

void removeGemFromArray(Gem**, int, int&);
Gem& addGemToArray(Gem**, Gem&, int&);

void confirmSound();
void moveSound();
void swapSound();
void loseHeartSound();

#endif
