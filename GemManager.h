#ifndef GEM_MANAGER_H
#define GEM_MANAGER_H

#include "global.h"
#include "Gem2.h"

class GemManager {
  public:
    GemManager();

    void create();
    void create(int);
    void update();
    void updateClearing();
    void updateFalling();
    void remove(Gem2&);
    void render();
    void reset();

    int randomEmptyRow();
    bool gemExistsInRow(int);
    void moveGemsInObstructedRows(int, int);
    bool hasClearingGems();
    bool hasInactiveGems();
    bool hasFallingGems();
    bool fallingGemsAreBelowPreviewThreshold();
    bool shouldCreateGems();

  private:
    static const int GEM_MANAGER_SIZE = 30;
    Gem2 gems_[GEM_MANAGER_SIZE];
    Gem2* firstAvailable_;
    
    int fallingGemCount_;
    int belowPreviewThresholdCount_;
    int clearingGemCount_;
    int inactiveGemCount_;
};

#endif
