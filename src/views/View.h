#ifndef VIEW_H
#define VIEW_H

#include "../../global.h"

class View {
  public:
    virtual void handleInput() {};
    virtual void update() {};
    virtual void render() {};
    virtual void handleNavigateTo() {};
    virtual void handleNavigateFrom() {};
};

#endif
