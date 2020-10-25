#include "Game.h"

#include "src/views/TitleView.h"
#include "src/views/InfoView.h"
#include "src/views/QuestView.h"
#include "src/views/BattleView.h"
#include "src/views/WinView.h"
#include "src/views/LoseView.h"

#define GAME_STATE_TITLE 0
#define GAME_STATE_INFO 1
#define GAME_STATE_QUEST 2
#define GAME_STATE_BATTLE 3
#define GAME_STATE_WIN 4
#define GAME_STATE_LOSE 5

#define GAME_ENEMY_DATA_LENGTH 5
#define GAME_ENEMY_DATA_HEALTH 0
#define GAME_ENEMY_DATA_WEAPON_MODIFIERS 1

namespace
{
  uint8_t state = GAME_STATE_TITLE;

  const int enemyData[ENEMY_COUNT][GAME_ENEMY_DATA_LENGTH] = {
    {100, 0, 0, 0, 0},
    {200, 0, 0, 0, 0},
    {200, -1, 2, -2, 1},
    {150, -1, -1, 2, 0},
    {250, 2, -1, -1, -2}
  };
}

int Game::playerHealth = PLAYER_HEALTH_MAX;
unsigned long int Game::score = 0;
int Game::enemyType;
int Game::enemyHealth;
int Game::enemyHealthMax;

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
  QuestView::init();
  state = GAME_STATE_QUEST;
}

void Game::goToBattleView()
{
  BattleView::init();
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
  setEnemy(ENEMY_TYPE_SKELETON);
}

void Game::setEnemy(int type)
{
  enemyType = type;
  enemyHealth = enemyData[type][GAME_ENEMY_DATA_HEALTH];
  enemyHealthMax = enemyData[type][GAME_ENEMY_DATA_HEALTH];
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
