#include "FlashAnimation.h"

void FlashAnimation::run() {
  index_ = 0;  
}

void FlashAnimation::reset() {
  index_ = count_;
  visible_ = true;
}

void FlashAnimation::update() {
  if (index_ == count_) return;

  if (arduboy.everyXFrames(duration_)) {
    toggle_();

    if (isVisible()) index_++;  
  }
}

bool FlashAnimation::isVisible() {
  return visible_;
}

void FlashAnimation::toggle_() {
  visible_ = !visible_;
}
