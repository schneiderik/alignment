#ifndef WIN_VIEW_H
#define WIN_VIEW_H

#include "../../global.h"
#include "./View.h"

class WinView: public View {
  public:
    void handleInput() override;
    void render() override;
};

#endif
