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
    void updateClearing();
    void updateFalling();
    void remove(Gem*);
    void render();
    void reset();

    void moveGemsInObstructedRows(int, int);
    bool hasClearingGems();
    bool hasFallingGems();
    bool fallingGemsAreBelowPreviewThreshold();
    bool shouldCreateGems();

  private:
    static const int GEM_MANAGER_SIZE = 30;
    Gem gems_[GEM_MANAGER_SIZE];
    Gem* firstInactive_;
    Gem* firstActive_;

    int belowPreviewThresholdCount_;
    int clearingGemCount_;

    Preview preview_;
    FallingGems fallingGems_;
};

#endif
