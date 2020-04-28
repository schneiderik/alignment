#include "./Router.h"

void Router::init(View* view) {
  view_ = view;
}

void Router::navigateTo(View* view) {
  view_->handleNavigateFrom();
  view_ = view;
  view_->handleNavigateTo();
}

View Router::getView() {
  return *view_;
}
