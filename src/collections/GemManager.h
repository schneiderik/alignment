#ifndef GEM_MANAGER_H
#define GEM_MANAGER_H

#include "../../global.h"
#include "../entities/Gem.h"
#include "../battle/Preview.h"
#include "../battle/FallingGems.h"

class GemManager {
  public:
    GemManager();

    Gem* create();
    void setFirstActive(Gem*);
    Gem* getFirstInactive();
    void update();
    void remove(Gem*);
    void render();
    void reset();
    void moveGemsInObstructedRows(int, int);

  private:
    static const int GEM_MANAGER_SIZE = 30;
    Gem gems_[GEM_MANAGER_SIZE];
    Gem* firstInactive_;
    Gem* firstActive_;

    Preview preview_;
    FallingGems fallingGems_;
};

#endif
