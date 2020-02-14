#include "TitleView.h"
#include "../../Game.h"

void TitleView::handleInput() {
  if (arduboy.justPressed(UP_BUTTON)) decrementState();   
  if (arduboy.justPressed(DOWN_BUTTON)) incrementState();
  if (arduboy.justPressed(A_BUTTON)) selectOption();   
}

void TitleView::decrementState() {
  if (state > 0) {
    state--;  
    moveSound();
  }  
}

void TitleView::incrementState() {
  if (state < LAST_TITLE_STATE) {
    state++;
    moveSound();
  }  
}

void TitleView::selectOption() {
  switch(state) {
    case TITLE_STATE_PLAY:
      game->goToQuestView();
      break;
    case TITLE_STATE_INFO:
      game->goToInfoView();
      break;
    case TITLE_STATE_SFX:
      if (arduboy.audio.enabled()) {
        arduboy.audio.off();
      } else {
        arduboy.audio.on();
      }
    
      arduboy.audio.saveOnOff();
      break;
  };
  confirmSound();  
}

void TitleView::render() {
  renderMainImage();
  renderPlayOption();
  renderInfoOption();
  renderSfxOption();
}

void TitleView::renderMainImage() {
  sprites.drawOverwrite(0, 5, titleImage, 0);
}

void TitleView::renderPlayOption() {
  sprites.drawOverwrite(56, 38, playTextImage, 0);
  if (state == TITLE_STATE_PLAY) renderCursor(56, 38, playTextImage[0]);
}

void TitleView::renderInfoOption() {
  sprites.drawOverwrite(56, 45, infoTextImage, 0);
  if (state == TITLE_STATE_INFO) renderCursor(56, 45, infoTextImage[0]);   
}

void TitleView::renderSfxOption() {
  if (arduboy.audio.enabled()) {
    sprites.drawOverwrite(52, 52, sfxOnTextImage, 0);
    if (state == TITLE_STATE_SFX) renderCursor(52, 52, sfxOnTextImage[0]);
  } else {
    sprites.drawOverwrite(50, 52, sfxOffTextImage, 0);
    if (state == TITLE_STATE_SFX) renderCursor(50, 52, sfxOffTextImage[0]);
  }  
}
       
void TitleView::renderCursor(int x, int y, int textWidth) {
  arduboy.fillRect(x - 5, y + 1, 2, 2);
  arduboy.fillRect(x + textWidth + 3, y + 1, 2, 2);
}
