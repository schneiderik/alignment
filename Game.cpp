#include "Game.h"

#include "TitleView.h"
#include "InfoView.h"
#include "QuestView.h"

#define GAME_STATE_TITLE 0
#define GAME_STATE_INFO 1
#define GAME_STATE_QUEST 2
#define GAME_STATE_BATTLE 3
#define GAME_STATE_WIN 4
#define GAME_STATE_LOSE 5

uint8_t Game::enemy = ENEMY_TYPE_SKELETON;

namespace
{
  uint8_t state = GAME_STATE_TITLE;
}

void Game::goToTitleView()
{
  state = GAME_STATE_TITLE;
}

void Game::goToInfoView()
{
  state = GAME_STATE_INFO;
}

void Game::goToQuestView()
{
  state = GAME_STATE_QUEST;
}

void Game::init()
{
  QuestView::init();
}

void Game::loop()
{
  switch (state)
  {
    case GAME_STATE_TITLE:
      TitleView::loop();
      break;
    case GAME_STATE_INFO:
      InfoView::loop();
      break;
    case GAME_STATE_QUEST:
      QuestView::loop();
      break;
  }
}
