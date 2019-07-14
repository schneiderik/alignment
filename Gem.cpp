#include "Gem.h"

void Gem::setType(int type) {
  type_ = type;
}

int Gem::getType() {
  return type_;
}

void Gem::setX(int x) {
  x_ = x;
}

int Gem::getX() {
  return x_;
}

void Gem::setTargetX(int x) {
  targetX_ = x;
}

int Gem::getTargetX() {
  return targetX_;
}

int Gem::getXPlusWidth() {
  return x_ + gemSpritePlusMask[0];
}

void Gem::setY(int y) {
  y_ = y;
}

void Gem::setTargetY(int y) {
  targetY_ = y;
}

int Gem::getY() {
  return y_;
}

void Gem::ready() {
  state_ = GEM_STATE_READY;
}

void Gem::drop() {
  state_ = GEM_STATE_FALLING;
}

void Gem::stop() {
  state_ = GEM_STATE_STOPPED;
}

void Gem::adjust() {
  state_ = GEM_STATE_ADJUSTING;
}

void Gem::hide() {
  state_ = GEM_STATE_HIDDEN;
}

void Gem::clear() {
  state_ = GEM_STATE_CLEARING;
  frame_ = GEM_CLEAR_ANIMATION_START_INDEX;
}

int Gem::getState() {
  return state_;
}

bool Gem::isReady() {
  return state_ == GEM_STATE_READY;
}

bool Gem::isFalling() {
  return state_ == GEM_STATE_FALLING;
}

bool Gem::isStopped() {
  return state_ == GEM_STATE_STOPPED;
}

bool Gem::isAdjusting() {
  return state_ == GEM_STATE_ADJUSTING;
}

bool Gem::isHidden() {
  return state_ == GEM_STATE_HIDDEN;
}

bool Gem::isClearing() {
  return state_ == GEM_STATE_CLEARING;
}

bool Gem::isAnimating() {
  return isFalling() || isAdjusting() || isClearing();
}

void Gem::update() {  
  updateX_();
  updateY_();
  updateClearAnimation_();
}

void Gem::updateClearAnimation_() {
  if (clearAnimationInterval_ == GEM_CLEAR_ANIMATION_FRAME_LENGTH) {
    if (isClearing()) {
      if (frame_ == GEM_CLEAR_ANIMATION_END_INDEX) {
        hide();
      } else {
        frame_++;
      }
    }
    
    clearAnimationInterval_ = 0;
  }
  
  clearAnimationInterval_++;
}

void Gem::updateX_() {
  if (fallInterval_ == GEM_FALL_FRAME_LENGTH) {
    if (isFalling() || isAdjusting()) { 
      if (x_ <= targetX_) {
        stop();
      } else {
        x_ -= GEM_FALL_INCREMENT;
      }      
    }
    
    fallInterval_ = 0;
  } 
  
  fallInterval_++; 
}

void Gem::updateY_() {
  if (moveInterval_ == GEM_MOVE_FRAME_LENGTH) {
    if (y_ != targetY_) {
      setY(y_ < targetY_ ? y_ + GEM_MOVE_INCREMENT : y_ - GEM_MOVE_INCREMENT);
    }

    moveInterval_ = 0;
  }

  moveInterval_++;  
}

void Gem::render() {
  if (isHidden()) return;
  
  sprites.drawPlusMask(
    x_, 
    y_, 
    gemSpritePlusMask, 
    isClearing() ? frame_ : type_
  );
}
