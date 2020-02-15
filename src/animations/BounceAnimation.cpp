#include "BounceAnimation.h"

BounceAnimation::BounceAnimation(
  int count,
  int lowerLimit,
  int upperLimit,
  int duration
):
  count_(count),
  lowerLimit_(lowerLimit),
  upperLimit_(upperLimit)
{
  intervalCount_ = (upperLimit - lowerLimit) * 2 * count;
  intervalLength_ = (int)ceil((float)duration/(float)intervalCount_);
  currentInterval_ = intervalCount_;
};

BounceAnimation::BounceAnimation(
  int speed,
  int lowerLimit,
  int upperLimit
):
  lowerLimit_(lowerLimit),
  upperLimit_(upperLimit),
  intervalCount_(0),
  currentInterval_(0),
  intervalLength_(speed)
{};

void BounceAnimation::run() {
  currentInterval_ = 0;
  offset_ = 0;
  velocity_ = 1;
}

void BounceAnimation::reset() {
  currentInterval_ = intervalCount_;
  offset_ = 0;
  velocity_ = 1;
}

void BounceAnimation::update() {
  if (intervalCount_ != 0 && currentInterval_ == intervalCount_) return;

  if (arduboy.everyXFrames(intervalLength_)) {
    if (isAtLimit_()) velocity_ = -velocity_;

    offset_ += velocity_;
    if (intervalCount_ != 0) currentInterval_++;
  }  
}

int BounceAnimation::getOffset() {
  return offset_;
}

bool BounceAnimation::isAtLimit_() {
  return offset_ == upperLimit_ || offset_ == lowerLimit_;
}
