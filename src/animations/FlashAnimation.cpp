#include "FlashAnimation.h"

FlashAnimation::FlashAnimation(int count, int duration):
  count_(count),
  index_(count)
{
  interval_ = (int)ceil((float)duration/(float)count);
};

void FlashAnimation::run() {
  index_ = 0;  
}

void FlashAnimation::reset() {
  index_ = count_;
  visible_ = true;
}

void FlashAnimation::update() {
  if (index_ == count_) return;

  if (arduboy.everyXFrames(interval_)) {
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
