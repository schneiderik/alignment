#ifndef ROUTER_H
#define ROUTER_H

#include "../../global.h"
#include "./View.h"

class Router {
  public:
    void init(View*);
    void navigateTo(View*);
    View getView();

  private:
    View* view_ = NULL;
};

#endif
