#ifndef GEM_MANAGER_H
#define GEM_MANAGER_H

#include "global.h"

#define GEM_MAX 2

class GemManager {
  public:
    GemManager();
    
    void update();
    void render();
    void reset();
    void create();
    void create(int);
    Gem& add(Gem&);
    void remove(int);
    Gem& get(int);
    Gem& getNext();

    bool gemExistsInRow(int);
    int randomEmptyRow();
    bool isClearing();
    bool isEmpty();
    bool gemsBelowPreviewThreshold();
    void moveGemsInObstructedRows(int, int);

    int count = 0;
    Gem* gems[GEM_MAX];
};

#endif
