#ifndef WIN_VIEW_H
#define WIN_VIEW_H

#include "../../global.h"
#include "View.h"

class WinView: public View {
  public:
    void handleInput(const Game&) override;
    void render(const Game&) override;
};

#endif
