#ifndef GAME_H
#define GAME_H

#include "global.h"

namespace Game
{
  extern uint8_t playerHealth;
  extern unsigned long int score;
  extern int enemyType;
  extern int enemyHealth;
  extern int enemyHealthMax;

  void init();
  void setEnemy(int);
  void loop();

  void goToTitleView();
  void goToInfoView();
  void goToQuestView();
  void goToBattleView();
  void goToWinView();
  void goToLoseView();
}

#endif
