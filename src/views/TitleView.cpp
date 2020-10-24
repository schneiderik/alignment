#include "TitleView.h"

#include "../../Game.h"
#include "../components/Sound.h"

#define TITLE_VIEW_TITLE_X 0
#define TITLE_VIEW_TITLE_Y 5
#define TITLE_VIEW_PLAY_X 56
#define TITLE_VIEW_PLAY_Y 38
#define TITLE_VIEW_INFO_X 56
#define TITLE_VIEW_INFO_Y 45
#define TITLE_VIEW_SFX_ON_X 52
#define TITLE_VIEW_SFX_ON_Y 52
#define TITLE_VIEW_SFX_OFF_X 50
#define TITLE_VIEW_SFX_OFF_Y 52
#define TITLE_VIEW_CURSOR_LEFT_OFFSET_X -5
#define TITLE_VIEW_CURSOR_RIGHT_OFFSET_X 3
#define TITLE_VIEW_CURSOR_OFFSET_Y 1
#define TITLE_VIEW_CURSOR_MIN 0
#define TITLE_VIEW_CURSOR_MAX 2
#define TITLE_VIEW_CURSOR_WIDTH 2
#define TITLE_VIEW_CURSOR_HEIGHT 2

namespace
{
  uint8_t cursor;

  void handleInput()
  {
    if (arduboy.justPressed(UP_BUTTON))
    {
      if (cursor > TITLE_VIEW_CURSOR_MIN)
      {
        cursor--;  
      }  
    }

    if (arduboy.justPressed(DOWN_BUTTON))
    {
      if (cursor < TITLE_VIEW_CURSOR_MAX)
      {
        cursor++;
      }  
    }

    if (arduboy.justPressed(A_BUTTON))
    {
      switch(cursor)
      {
        case 0:
          Game::goToQuestView();
          break;
        case 1:
          Game::goToInfoView();
          break;
        case 2:
          Sound::toggle();
          break;
      };
    }
  }

  void renderTitle()
  {
    sprites.drawOverwrite(
      TITLE_VIEW_TITLE_X,
      TITLE_VIEW_TITLE_Y,
      titleImage,
      0
    );
  }

  void renderPlay()
  {
    sprites.drawOverwrite(
      TITLE_VIEW_PLAY_X,
      TITLE_VIEW_PLAY_Y,
      playTextImage,
      0
    );
  }

  void renderInfo()
  {
    sprites.drawOverwrite(
      TITLE_VIEW_INFO_X,
      TITLE_VIEW_INFO_Y,
      infoTextImage,
      0
    );
  }

  void renderSfxOn()
  {
    sprites.drawOverwrite(
      TITLE_VIEW_SFX_ON_X,
      TITLE_VIEW_SFX_ON_Y,
      sfxOnTextImage,
      0
    );
  }

  void renderSfxOff()
  {
    sprites.drawOverwrite(
      TITLE_VIEW_SFX_OFF_X,
      TITLE_VIEW_SFX_OFF_Y,
      sfxOffTextImage,
      0
    );
  }

  void renderSfx()
  {
    if (Sound::isOn())
    {
      renderSfxOn();
    }
    else
    {
      renderSfxOff();
    }
  }

  void renderCursor(uint8_t x, uint8_t y, uint8_t width)
  {
    arduboy.fillRect(
      x + TITLE_VIEW_CURSOR_LEFT_OFFSET_X,
      y + TITLE_VIEW_CURSOR_OFFSET_Y,
      TITLE_VIEW_CURSOR_WIDTH,
      TITLE_VIEW_CURSOR_HEIGHT
    );

    arduboy.fillRect(
      x + width + TITLE_VIEW_CURSOR_RIGHT_OFFSET_X,
      y + TITLE_VIEW_CURSOR_OFFSET_Y,
      TITLE_VIEW_CURSOR_WIDTH,
      TITLE_VIEW_CURSOR_HEIGHT
    );
  }

  void renderMenu()
  {
    renderPlay();
    renderInfo();
    renderSfx();

    switch(cursor)
    {
      case 0:
        renderCursor(
          TITLE_VIEW_PLAY_X,
          TITLE_VIEW_PLAY_Y,
          playTextImage[0]
        );
        break;
      case 1:
        renderCursor(
          TITLE_VIEW_INFO_X,
          TITLE_VIEW_INFO_Y,
          infoTextImage[0]
        );
        break;
      case 2:
        if (Sound::isOn()) {
          renderCursor(
            TITLE_VIEW_SFX_ON_X,
            TITLE_VIEW_SFX_ON_Y,
            sfxOnTextImage[0]
          );
        }
        else
        {
          renderCursor(
            TITLE_VIEW_SFX_OFF_X,
            TITLE_VIEW_SFX_OFF_Y,
            sfxOffTextImage[0]
          );
        }
        break;
    }
  }

  void render()
  {
    renderTitle();
    renderMenu();
  }
}

void TitleView::loop()
{
  handleInput();
  render();
}
