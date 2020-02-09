#ifndef GEM_COLLECTION_H
#define GEM_COLLECTION_H

#include "global.h"
#include "Gem2.h"

class GemCollection {
  public:
    GemCollection();

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
    static const int GEM_COLLECTION_SIZE = 30;
    Gem2 gems_[GEM_COLLECTION_SIZE];
    Gem2* firstAvailable_;
    
    int fallingGemCount_;
    int belowPreviewThresholdCount_;
    int clearingGemCount_;
    int inactiveGemCount_;
};

#endif
