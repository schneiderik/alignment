#include "TitleView.h"

void TitleView::handleInput(const Game& game) {
  if (arduboy.justPressed(UP_BUTTON)) decrementState_(game);   
  if (arduboy.justPressed(DOWN_BUTTON)) incrementState_(game);
  if (arduboy.justPressed(A_BUTTON)) selectOption_(game);   
}

void TitleView::decrementState_(const Game& game) {
  if (state > 0) {
    state--;  
    game.getAudio().playMoveSound();
  }  
}

void TitleView::incrementState_(const Game& game) {
  if (state < LAST_TITLE_STATE) {
    state++;
    game.getAudio().playMoveSound();
  }  
}

void TitleView::selectOption_(const Game& game) {
  switch(state) {
    case TITLE_STATE_PLAY:
      game.goToQuestView();
      break;
    case TITLE_STATE_INFO:
      game.goToInfoView();
      break;
    case TITLE_STATE_SFX:
      game.getAudio().toggle()
      break;
  };

  game.getAudio().playConfirmSound();
}

void TitleView::render(const Game& game) {
  renderMainImage_();
  renderPlayOption_();
  renderInfoOption_();
  renderSfxOption_();
}

void TitleView::renderMainImage_() {
  sprites.drawOverwrite(0, 5, titleImage, 0);
}

void TitleView::renderPlayOption_() {
  sprites.drawOverwrite(56, 38, playTextImage, 0);
  if (state == TITLE_STATE_PLAY) renderCursor_(56, 38, playTextImage[0]);
}

void TitleView::renderInfoOption_() {
  sprites.drawOverwrite(56, 45, infoTextImage, 0);
  if (state == TITLE_STATE_INFO) renderCursor_(56, 45, infoTextImage[0]);   
}

void TitleView::renderSfxOption_() {
  if (arduboy.audio.enabled()) {
    sprites.drawOverwrite(52, 52, sfxOnTextImage, 0);
    if (state == TITLE_STATE_SFX) renderCursor_(52, 52, sfxOnTextImage[0]);
  } else {
    sprites.drawOverwrite(50, 52, sfxOffTextImage, 0);
    if (state == TITLE_STATE_SFX) renderCursor_(50, 52, sfxOffTextImage[0]);
  }  
}
       
void TitleView::renderCursor_(int x, int y, int textWidth) {
  arduboy.fillRect(x - 5, y + 1, 2, 2);
  arduboy.fillRect(x + textWidth + 3, y + 1, 2, 2);
}
