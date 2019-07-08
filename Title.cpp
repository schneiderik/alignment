#include "Title.h"
#include "Game.h"

void Title::handleInput(Game& game) {
  if (arduboy.justPressed(UP_BUTTON) && state_ > 0) { state_--; };
  if (arduboy.justPressed(DOWN_BUTTON) && state_ < LAST_TITLE_OPTION) { state_++; };
  if (arduboy.justPressed(A_BUTTON)) { handleConfirm_(game); }; 
};

void Title::handleConfirm_(Game& game) {
  switch(state_) {
    case TITLE_STATE_PLAY:
      game.goToQuestScreen();
      break;
    case TITLE_STATE_INFO:
      game.goToInfoScreen();
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
}

void Title::render() {
  sprites.drawOverwrite(
    TITLE_IMAGE_X,
    TITLE_IMAGE_Y,
    titleImage,
    0
  );

  sprites.drawOverwrite(
    TITLE_PLAY_TEXT_X,
    TITLE_PLAY_TEXT_Y,
    playTextImage,
    0
  ); 

  sprites.drawOverwrite(
    TITLE_INFO_TEXT_X,
    TITLE_INFO_TEXT_Y,
    infoTextImage,
    0
  ); 

  if (arduboy.audio.enabled()) {
    sprites.drawOverwrite(
      TITLE_SFX_ON_TEXT_X,
      TITLE_SFX_ON_TEXT_Y,
      sfxOnTextImage,
      0
    ); 
  } else {
    sprites.drawOverwrite(
      TITLE_SFX_OFF_TEXT_X,
      TITLE_SFX_OFF_TEXT_Y,
      sfxOffTextImage,
      0
    ); 
  }

  switch(state_) {
    case TITLE_STATE_PLAY:
      renderCursor_(TITLE_PLAY_TEXT_X, TITLE_PLAY_TEXT_Y, playTextImage[0]);
      break;
    case TITLE_STATE_INFO:
      renderCursor_(TITLE_INFO_TEXT_X, TITLE_INFO_TEXT_Y, infoTextImage[0]);
      break;
    case TITLE_STATE_SFX:
      if (arduboy.audio.enabled()) {
        renderCursor_(TITLE_SFX_ON_TEXT_X, TITLE_SFX_ON_TEXT_Y, sfxOnTextImage[0]);
      } else {
        renderCursor_(TITLE_SFX_OFF_TEXT_X, TITLE_SFX_OFF_TEXT_Y, sfxOffTextImage[0]);  
      }
      break;
  };
};

void Title::renderCursor_(int baseX, int baseY, int width) {
  int x1 = baseX - TITLE_CURSOR_X_OFFSET - TITLE_CURSOR_SIZE;
  int x2 = baseX + width + TITLE_CURSOR_X_OFFSET;
  int y = baseY + TITLE_CURSOR_Y_OFFSET;
  
  arduboy.fillRect(x1, y, TITLE_CURSOR_SIZE, TITLE_CURSOR_SIZE);
  arduboy.fillRect(x2, y, TITLE_CURSOR_SIZE, TITLE_CURSOR_SIZE);
}
