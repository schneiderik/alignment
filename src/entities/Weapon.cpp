#include "Weapon.h"
#include "Gem.h"
#include "../../Player.h"
#include "../../Enemy.h"
#include "../collections/GemManager.h"

static const int Weapon::Y_OFFSETS[Weapon::COUNT] = {13, 25, 37, 49};
static const int Weapon::GEM_X_OFFSETS[Weapon::GEM_MAX] = {16, 28, 40, 52, 64, 76, 88};

Weapon::Weapon(int order) {
  reset(order);
}

void Weapon::reset(int order) {
  type_ = order;
  order_ = order;
  y_ = Weapon::Y_OFFSETS[order];
  previewGem_ = NULL;
  fallingGem_ = NULL;
  lastGem_ = NULL;
  gemCount_ = 0;
}

// UPDATE

void Weapon::update() {
  updateGemStack_();

  switch (state_) {
    case STATE_CLEARING:
      if (lastGem_ == NULL) state_ = STATE_DEFAULT;
      break;
    default:
      updateFallingGem_();
      updateY_();
      if (lastGemsMatch_()) popLastGems_();
      if (isOverflowed_()) clearStackedGems_();
      break;
  }
}

void Weapon::updateY_() {
  if (isMisaligned_()) {
    Gem* currentGem = lastGem_;

    y_ += y_ < Weapon::Y_OFFSETS[order_] ? MOVE_Y_INCREMENT : -MOVE_Y_INCREMENT;

    while (currentGem != NULL) {
      currentGem->setY(y_);

      currentGem = currentGem->getNext();
    }
  }
}

void Weapon::updateGemStack_() {
  Gem* currentGem = lastGem_;
  Gem* nextGem = NULL;

  while (currentGem != NULL) {
    currentGem->update();
    nextGem = currentGem->getNext();
    if (currentGem->isHidden()) removeGemFromStack_(currentGem);
    currentGem = nextGem;
  }
}

void Weapon::updateFallingGem_() {
  if (!hasFallingGem()) return;

  if (fallingGem_->getY() != Weapon::Y_OFFSETS[order_]) fallingGem_->setY(y_);

  fallingGem_->update();  

  if (fallingGem_->getX() <= getEndOfRowX()) stackFallingGem();
}

// RENDER

void Weapon::render(bool active) {
  renderIcon_(active);
  renderDivider_();
  renderGemStack_();
  if (hasPreviewGem()) previewGem_->render();
  if (hasFallingGem()) fallingGem_->render();
}

void Weapon::renderGemStack_() {
  Gem* currentGem = lastGem_;

  while (currentGem != NULL) {
    currentGem->render();
    currentGem = currentGem->getNext();
  }
}

void Weapon::renderIcon_(bool active) {
  if (active) {
    arduboy.fillRect(0, y_, 12, 12); 
    sprites.drawErase(2, y_ + 2, weaponSprite, type_);  
  } else {
    sprites.drawOverwrite(2, y_ + 2, weaponSprite, type_);    
  }  
}

void Weapon::renderDivider_() {
  arduboy.fillRect(14, y_ + 1, 1, 10);
}

void Weapon::createPreviewGem() {
  previewGem_ = gemManager->create();
  previewGem_->init(PREVIEW_GEM_X, y_);
}

void Weapon::dropPreviewGem() {
  if (!hasPreviewGem()) return;

  fallingGem_ = previewGem_;
  previewGem_ = NULL;
  fallingGem_->drop();
}

void Weapon::stackFallingGem() {
  player->addScore(10);
  fallingGem_->setNext(lastGem_);
  lastGem_ = fallingGem_;
  lastGem_->stop();
  fallingGem_ = NULL;
  gemCount_++;
}

void Weapon::popLastGems_() {
  lastGem_->pop();
  lastGem_->getNext()->pop();
  gemCount_ -= 2;

  player->addScore(100);
  enemy->takeDamage(5, type_);            
  confirmSound();
}

void Weapon::clearStackedGems_() {
  state_ = STATE_CLEARING;
  player->takeDamage();
  gemCount_ = 0;

  Gem* currentGem = lastGem_;
  
  while (currentGem != NULL) {
    currentGem->clear();
    currentGem = currentGem->getNext();
  }
}

void Weapon::slashLastGem() {
  Gem* gem = getLastGemInStack();

  if (gem == NULL) return;

  gem->pop();
  gemCount_--;
}

void Weapon::removeGemFromStack_(Gem* gem) {
  if (gem == lastGem_) {
    lastGem_ = gem->getNext();
    gemManager->remove(gem);
    return;
  }

  Gem* currentGem = lastGem_;

  while (currentGem != NULL) {
    if (currentGem->getNext() == gem) {
      currentGem->setNext(gem->getNext());
      gemManager->remove(gem);
      return;
    }

    currentGem = currentGem->getNext();
  }
}

int Weapon::getEndOfRowX() { return Weapon::GEM_X_OFFSETS[gemCount_]; }
int Weapon::getOrder() { return order_; }
void Weapon::setOrder(int order) { order_ = order; }
Gem* Weapon::getPreviewGem() { return previewGem_; }
void Weapon::setPreviewGem(Gem* gem) { previewGem_ = gem; }
Gem* Weapon::getFallingGem() { return fallingGem_; }
void Weapon::setFallingGem(Gem* gem) { fallingGem_ = gem; }
Gem* Weapon::getLastGemInStack() { return getLastGemInStack(lastGem_); }
Gem* Weapon::getLastGemInStack(Gem* gem) { 
  if (gem == NULL) return gem;
  return gem->isInactive() ? gem : getLastGemInStack(gem->getNext());
}
bool Weapon::isMisaligned_() { return y_ != Weapon::Y_OFFSETS[order_]; }
bool Weapon::isFull_() { return gemCount_ == Weapon::GEM_MAX - 1; }
bool Weapon::isOverflowed_() { return gemCount_ == Weapon::GEM_MAX; }
bool Weapon::isEmpty_() { return gemCount_ == 0; }
bool Weapon::isMatchable_() { return gemCount_ >= 2 && !lastGem_->isPopping(); }
bool Weapon::isClearing() { return state_ == STATE_CLEARING; }
bool Weapon::hasPreviewGem() { return previewGem_ != NULL; }
bool Weapon::hasFallingGem() { return fallingGem_ != NULL; }
bool Weapon::previewIsEmpty() { return !hasPreviewGem() && (!hasFallingGem() || fallingGem_->getX() <= PREVIEW_THRESHOLD_X); }
bool Weapon::lastGemsMatch_() { return isMatchable_() && lastGem_->getType() == lastGem_->getNext()->getType(); }
bool Weapon::fallingGemAboveX(int x) { return !hasFallingGem() || fallingGem_->getX() > x; }
