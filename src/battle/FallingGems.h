#ifndef FALLING_GEMS_H
#define FALLING_GEMS_H

#include "../../global.h"

class FallingGems {
  public:
    void add(Gem*);
    void clear();
    void moveGemsInObstructedRows(int, int);
    bool isEmpty();
    bool belowPreviewThreshold();

  private:
    Gem* head_;
};

#endif
