#include "Title.h"

void Title::handleInput(int& gameState) {
  if (arduboy.justPressed(UP_BUTTON)) decrementState();   
  if (arduboy.justPressed(DOWN_BUTTON)) incrementState();
  if (arduboy.justPressed(A_BUTTON)) selectOption(gameState);   
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

void Title::selectOption(int& gameState) {
  switch(state) {
    case TITLE_STATE_PLAY:
      gameState = GAME_STATE_QUEST;
      break;
    case TITLE_STATE_INFO:
      gameState = GAME_STATE_INFO;
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

void Title::reset() {
  state = TITLE_STATE_PLAY;
}
