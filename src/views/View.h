#ifndef VIEW_H
#define VIEW_H

#include "../../global.h"

class View {
  public:
    virtual void init(const Game&) {};
    virtual void handleInput(const Game&) {};
    virtual void update(const Game&) {};
    virtual void render(const Game&) {};
    virtual void navigateTo(const Game&) {};
    virtual void navigateFrom(const Game&) {};
};

#endif
