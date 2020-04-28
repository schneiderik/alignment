#ifndef INFO_VIEW_H
#define INFO_VIEW_H

#include "../../global.h"
#include "./View.h"

class InfoView: public View {
  public:
    void handleInput() override;
    void render() override;
};

#endif
