#ifndef PREVIEW_H
#define PREVIEW_H

#include "../../global.h"

class Preview {
  public:
    void clear();
    void populate(int);
    bool isEmpty();

  private:
    Gem* head_ = NULL;

    int randomEmptyRow_();
    bool gemExistsInRow_(int);
};

#endif
