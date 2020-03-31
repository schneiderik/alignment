#ifndef GEM_MANAGER_H
#define GEM_MANAGER_H

#include "../../global.h"
#include "../entities/Gem.h"

#define GEM_MANAGER_SIZE 30

class GemManager {
  public:
    GemManager();

    Gem* create();
    void remove(Gem*);
    void reset();

  private:
    Gem gems_[GEM_MANAGER_SIZE];
    Gem* firstInactive_;
};

#endif
