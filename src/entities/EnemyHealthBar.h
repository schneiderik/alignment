#ifndef ENEMY_HEALTH_BAR_H
#define ENEMY_HEALTH_BAR_H

#include "../../Enemy.h"
#include "../../Event.h"
#include "../../Observer.h"

#define ENEMY_HEALTH_BAR_HEIGHT 1
#define ENEMY_HEALTH_BAR_WIDTH_MAX 20

class EnemyHealthBar: public Observer {
  public:
    void onNotify(Enemy, Event) override;
    void reset();
    void render(int, int);

  private:
    int width_ = ENEMY_HEALTH_BAR_WIDTH_MAX;
}

#endif
