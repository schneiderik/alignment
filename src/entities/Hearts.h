#ifndef HEARTS_H
#define HEARTS_H

#include "../../global.h";

class Hearts {
  public:
    void init(const Player&);
    void render(int, int);

  private:
    Player* player_ = NULL;
};

#endif
