#ifndef GEM_COLLECTION_H
#define GEM_COLLECTION_H

#include "global.h"
#include "Gem2.h"

class GemCollection {
  public:
    GemCollection();

    Gem2& create();
    void update();

    int randomEmptyRow();
    bool gemExistsInRow(int);

  private:
    static const int GEM_COLLECTION_SIZE = 30;
    Gem2 gems_[GEM_COLLECTION_SIZE];
    Gem2* firstAvailable_;  
    int fallingGemCount_;
    int clearingGemCount_;
    int inactiveGemCount_;
};

#endif
