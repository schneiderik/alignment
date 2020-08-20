#include "Game.h"

#include "TitleView.h"
#include "InfoView.h"
#include "QuestView.h"
#include "BattleView.h"

#define GAME_STATE_TITLE 0
#define GAME_STATE_INFO 1
#define GAME_STATE_QUEST 2
#define GAME_STATE_BATTLE 3
#define GAME_STATE_WIN 4
#define GAME_STATE_LOSE 5

#define ENEMY_DATA_LENGTH 5
#define ENEMY_DATA_HEALTH 0
#define ENEMY_DATA_WEAPON_MODIFIERS 1

namespace
{
  uint8_t state = GAME_STATE_TITLE;

  const int enemyData[ENEMY_COUNT][ENEMY_DATA_LENGTH] = {
    {100, 0, 0, 0, 0},
    {200, 0, 0, 0, 0},
    {200, -1, 2, -2, 1},
    {150, -1, -1, 2, 0},
    {250, 2, -1, -1, -2}
  };
}

uint8_t Game::enemyType = ENEMY_TYPE_SKELETON;
int Game::enemyHealth = enemyData[ENEMY_TYPE_SKELETON][ENEMY_DATA_HEALTH];
int Game::enemyHealthMax = enemyData[ENEMY_TYPE_SKELETON][ENEMY_DATA_HEALTH];
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

void Game::init()
{
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
  }
}
