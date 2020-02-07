#include "Title.h"
#include "Game.h"

void Title::handleInput() {
  if (arduboy.justPressed(UP_BUTTON)) decrementState();   
  if (arduboy.justPressed(DOWN_BUTTON)) incrementState();
  if (arduboy.justPressed(A_BUTTON)) selectOption();   
}

void Title::decrementState() {
  if (state > 0) {
    state--;  
    moveSound();
  }  
}

void Title::incrementState() {
  if (state < LAST_TITLE_STATE) {
    state++;
    moveSound();
  }  
}

void Title::selectOption() {
  switch(state) {
    case TITLE_STATE_PLAY:
      game->goToQuest();
      break;
    case TITLE_STATE_INFO:
      game->goToInfo();
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

void Title::render() {
  renderMainImage();
  renderPlayOption();
  renderInfoOption();
  renderSfxOption();
}

void Title::renderMainImage() {
  sprites.drawOverwrite(0, 5, titleImage, 0);
}

void Title::renderPlayOption() {
  sprites.drawOverwrite(56, 38, playTextImage, 0);
  if (state == TITLE_STATE_PLAY) renderCursor(56, 38, playTextImage[0]);
}

void Title::renderInfoOption() {
  sprites.drawOverwrite(56, 45, infoTextImage, 0);
  if (state == TITLE_STATE_INFO) renderCursor(56, 45, infoTextImage[0]);   
}

void Title::renderSfxOption() {
  if (arduboy.audio.enabled()) {
    sprites.drawOverwrite(52, 52, sfxOnTextImage, 0);
    if (state == TITLE_STATE_SFX) renderCursor(52, 52, sfxOnTextImage[0]);
  } else {
    sprites.drawOverwrite(50, 52, sfxOffTextImage, 0);
    if (state == TITLE_STATE_SFX) renderCursor(50, 52, sfxOffTextImage[0]);
  }  
}
       
void Title::renderCursor(int x, int y, int textWidth) {
  arduboy.fillRect(x - 5, y + 1, 2, 2);
  arduboy.fillRect(x + textWidth + 3, y + 1, 2, 2);
}
