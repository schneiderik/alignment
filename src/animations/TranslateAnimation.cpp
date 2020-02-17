#include "TranslateAnimation.h"

// loop false: lower limit to upper limit forever at X speed
// loop true: loop through limits forever at X speed
TranslateAnimation::TranslateAnimation(
  int lowerLimit,
  int upperLimit,
  int speed,
  bool loop
):
  lowerLimit_(lowerLimit),
  upperLimit_(upperLimit),
  intervalCount_(0),
  currentInterval_(0),
  intervalLength_(speed),
  initialVelocity_(upperLimit < lowerLimit ? -1 : 1),
  velocity_(initialVelocity_),
  isLooping_(loop)
{};

// loop false: lower limit to upper limit X times over duration
// loop true: loop through limits X times over duration
TranslateAnimation::TranslateAnimation(
  int lowerLimit,
  int upperLimit,
  int count,
  int duration,
  bool loop
):
  lowerLimit_(lowerLimit),
  upperLimit_(upperLimit),
  count_(count),
  initialVelocity_(upperLimit < lowerLimit ? -1 : 1),
  velocity_(initialVelocity_),
  isLooping_(loop)
{
  intervalCount_ = abs(upperLimit - lowerLimit) * (loop ? 2 : 1) * count;
  intervalLength_ = (int)ceil((float)duration/(float)intervalCount_);
  currentInterval_ = intervalCount_;
};

void TranslateAnimation::run() {
  currentInterval_ = 0;
  value_ = 0;
  velocity_ = initialVelocity_;
}

void TranslateAnimation::reset() {
  currentInterval_ = intervalCount_;
  value_ = 0;
  velocity_ = initialVelocity_;
}

void TranslateAnimation::update() {
  if (intervalCount_ != 0 && currentInterval_ == intervalCount_) return;

  if (arduboy.everyXFrames(intervalLength_)) {
    if (isLooping_) {
      if (isAtLimit_()) velocity_ = -velocity_;

      value_ += velocity_;
    } else {
      if (isAtUpperLimit_()) {
        value_ = lowerLimit_;
      } else {
        value_ += velocity_;
      }
    }

    if (intervalCount_ != 0) currentInterval_++;
  }  
}

bool TranslateAnimation::isRunning() {
  if (intervalCount_ == 0) return true;

  return currentInterval_ < intervalCount_;
}

int TranslateAnimation::getValue() {
  return value_;
}

bool TranslateAnimation::isAtLimit_() {
  return isAtUpperLimit_() || isAtLowerLimit_();
}

bool TranslateAnimation::isAtUpperLimit_() {
  return upperLimit_ > lowerLimit_
    ? value_ >= upperLimit_
    : value_ <= upperLimit_;
}

bool TranslateAnimation::isAtLowerLimit_() {
  return upperLimit_ > lowerLimit_
    ? value_ <= lowerLimit_
    : value_ >= lowerLimit_;
}
