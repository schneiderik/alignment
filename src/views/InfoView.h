#ifndef INFO_VIEW_H
#define INFO_VIEW_H

#include "../../global.h"
#include "View.h"

class InfoView: public View {
  public:
    void handleInput(const Game&) override;
    void render(const Game&) override;
};

#endif
