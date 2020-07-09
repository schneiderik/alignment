#ifndef LOSE_VIEW_H
#define LOSE_VIEW_H

#include "../../global.h"
#include "View.h"

class LoseView: public View {
  public:
    void handleInput(const Game&) override;
    void render(const Game&) override;
};

#endif
