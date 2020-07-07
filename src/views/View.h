#ifndef VIEW_H
#define VIEW_H

#include "../../Game.h"

class View {
  public:
    virtual void init(Game) {};
    virtual void handleInput(Game) {};
    virtual void update(Game) {};
    virtual void render(Game) {};
    virtual void navigateTo(Game) {};
    virtual void navigateFrom(Game) {};
};

#endif
