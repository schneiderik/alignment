#ifndef PREVIEW_H
#define PREVIEW_H

#include "../../global.h"

class Preview {
  public:
    void clear();
    void populate(int);
    bool isEmpty();
    Gem* getHead();

  private:
    Gem* head_ = NULL;

    void populate_();
    int randomEmptyRow_();
    bool gemExistsInRow_(int);
};

#endif
