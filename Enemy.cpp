#include "Enemy.h"

#define ENEMY_HEALTH_BAR_X 2
#define ENEMY_HEALTH_BAR_Y 50
#define ENEMY_HEALTH_BAR_HEIGHT 1
#define ENEMY_HEALTH_BAR_WIDTH 20

#define ENEMY_SPRITE_X 0
#define ENEMY_SPRITE_Y 0

namespace
{
  void renderHealthBar(
    int x,
    int y,
    float health,
    float maxHealth
  )
  {
    float percentHealth = health / maxHealth;
    int width = ceil(percentHealth * ENEMY_HEALTH_BAR_WIDTH);

    arduboy.fillRect(
      x,
      y,
      width,
      ENEMY_HEALTH_BAR_HEIGHT,
      WHITE
    ); 
  }

  void renderSprite(int x, int y, uint8_t type)
  {
//  int frame = 0;
//  bool hidden = false;
//
//  void update() {
////    attackAnimation_.update();
////    flashAnimation_.update();
////    idleAnimation_.update();
////
////    int frame = idleAnimation_.getValue();
////
////    if (attackAnimation_.isRunning()) {
////      frame = attackAnimation_.getValue();
////    } else if (flashAnimation_.isRunning()) {
////      frame = ENEMY_DAMAGE_FRAME;
////    }
////
////    enemy.frame = frame + (enemy_->getType() * ENEMY_FRAME_COUNT);
//  };
//
//  void render(int x, int y, Enemy& enemy) {
////    if (flashAnimation_.getValue() == 0) {
////      sprites.drawOverwrite(
////        x + shakeAnimation_.getValue(),
////        y,
////        enemySprite,
////        frame_
////      );
////    }
//  };
  }
}

void Enemy::init()
{
}

void Enemy::update()
{

}

void Enemy::render(
  int x,
  int y,
  uint8_t type,
  int health,
  int maxHealth
)
{
  renderHealthBar(
    x + ENEMY_HEALTH_BAR_X,
    y + ENEMY_HEALTH_BAR_Y,
    health,
    maxHealth
  );

  renderSprite(
    x + ENEMY_SPRITE_X,
    y + ENEMY_SPRITE_Y,
    type
  );
}
