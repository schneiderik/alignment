#ifndef GAME_H
#define GAME_H

#include "global.h"

#include "Enemy.h"

namespace Game
{
  extern uint8_t playerHealth;
  extern unsigned long int score;

  void init();
  void loop();

  void goToTitleView();
  void goToInfoView();
  void goToQuestView();
  void goToBattleView();
  void goToWinView();
  void goToLoseView();
}

#endif
