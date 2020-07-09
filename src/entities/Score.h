#ifndef SCORE_H
#define SCORE_H

#include "../../global.h";
#include "../../Player"

class Score {
  public:
    void init(Player);
    void render(int, int, int, int);

  private:
    Player* player_ = NULL;

    void renderDigit_(int, int, int);
    void renderAlignCenter_(int, int, int);
    void renderAlignRight_(int, int, int);
    void renderAlignLeft_(int, int, int);
    int calculateDigitCount_();
    int calculateWidth_();
};

#endif

