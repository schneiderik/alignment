#ifndef LOSE_VIEW_H
#define LOSE_VIEW_H

#include "../../global.h"
#include "./View.h"

class LoseView: public View {
  public:
    void handleInput() override;
    void handleNavigateFrom() override;
    void render() override;
};

#endif
