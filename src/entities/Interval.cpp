#include "Interval.h"

void Interval::init(int interval) {
  intervalMin_ = interval;
  interval_ = getInterval_();
}

void Interval::init(int intervalMin, int intervalMax) {
  intervalMin_ = intervalMin;
  intervalMax_ = intervalMax;
  interval_ = getInterval_();
}

void Interval::update() {
  frame_++;
  active_ = false;
  
  if (frame_ == interval_) {
    active_ = true;
    interval_ = getInterval_();
    frame_ = 0;
  }
}

void Interval::reset() {
  frame_ = 0;
  interval_ = getInterval_();
  active_ = false;
}

bool Interval::isActive() {
  return active_;
}

int Interval::getInterval_() {
  if (maxInterval_ > 0) {
    return random(intervalMin_, intervalMax_);
  }

  return intervalMin_;
}
