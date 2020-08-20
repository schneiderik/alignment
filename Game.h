#ifndef GAME_H
#define GAME_H

#include "global.h"

namespace Game
{
  extern uint8_t enemy;
  extern uint8_t playerHealth;
  extern unsigned long int score;

  void init();
  void loop();

  void goToTitleView();
  void goToInfoView();
  void goToQuestView();
  void goToBattleView();
}

#endif
