#include "Gem.h"

void Gem::setType(int type) {
  type_ = type;
}

int Gem::getType() {
  return type_;
}

void Gem::activate() {
  state_ = GEM_STATE_ACTIVE;
}

void Gem::stop() {
  state_ = GEM_STATE_STOPPED;
}

void Gem::hide() {
  state_ = GEM_STATE_HIDDEN;
}

void Gem::animateOut() {
  state_ = GEM_STATE_ANIMATING_OUT;
  frame_ = GEM_ANIMATE_OUT_START_INDEX;
}

int Gem::getState() {
  return state_;
}

bool Gem::isActive() {
  return state_ == GEM_STATE_ACTIVE;
}

bool Gem::isStopped() {
  return state_ == GEM_STATE_STOPPED;
}

bool Gem::isHidden() {
  return state_ == GEM_STATE_HIDDEN;
}

bool Gem::isAnimatingOut() {
  return state_ == GEM_STATE_ANIMATING_OUT;
}

void Gem::update() {  
  if (isAnimatingOut()) {
    if (interval_ == GEM_ANIMATE_OUT_FRAME_LENGTH) {
      if (frame_ == GEM_ANIMATE_OUT_END_INDEX) hide();
      frame_++;
      interval_ = 0;
    }

    interval_++;
  }
}

void Gem::render(int x, int y) {
  if (isHidden()) return;
  
  sprites.drawPlusMask(
    x, 
    y, 
    gemSpritePlusMask, 
    isAnimatingOut() ? frame_ : type_
  );
}
