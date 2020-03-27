#ifndef GEM_MANAGER_H
#define GEM_MANAGER_H

#include "../../global.h"
#include "../entities/Gem.h"

class GemManager {
  public:
    GemManager();

    Gem* create();
    void remove(Gem*);
    void reset();

  private:
    static const int GEM_MANAGER_SIZE = 30;
    Gem gems_[GEM_MANAGER_SIZE];
    Gem* firstInactive_;
};

#endif
