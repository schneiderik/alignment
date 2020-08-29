#include "Game.h"

#include "TitleView.h"
#include "InfoView.h"
#include "QuestView.h"
#include "BattleView.h"
#include "WinView.h"
#include "LoseView.h"

#define GAME_STATE_TITLE 0
#define GAME_STATE_INFO 1
#define GAME_STATE_QUEST 2
#define GAME_STATE_BATTLE 3
#define GAME_STATE_WIN 4
#define GAME_STATE_LOSE 5

namespace
{
  uint8_t state = GAME_STATE_TITLE;
}

uint8_t Game::playerHealth = PLAYER_HEALTH_MAX;
unsigned long int Game::score = 0;

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

void Game::goToBattleView()
{
  state = GAME_STATE_BATTLE;
}

void Game::goToWinView()
{
  state = GAME_STATE_WIN;
}

void Game::goToLoseView()
{
  state = GAME_STATE_LOSE;
}

void Game::init()
{
  CurrentEnemy::init(ENEMY_TYPE_SKELETON);
  QuestView::init();
  BattleView::init();
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
    case GAME_STATE_BATTLE:
      BattleView::loop();
      break;
    case GAME_STATE_WIN:
      WinView::loop();
      break;
    case GAME_STATE_LOSE:
      LoseView::loop();
      break;
  }
}
