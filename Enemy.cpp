#include "Enemy.h"

#include "Animation.h"

#define ENEMY_HEALTH_BAR_X 2
#define ENEMY_HEALTH_BAR_Y 50
#define ENEMY_HEALTH_BAR_HEIGHT 1
#define ENEMY_HEALTH_BAR_WIDTH 20

#define ENEMY_SPRITE_X 0
#define ENEMY_SPRITE_Y 0

#define ENEMY_IDLE_ANIMATION_FRAME_COUNT 3
#define ENEMY_IDLE_ANIMATION_INTERVAL 30

namespace SkeletonIdleAnimation
{
  AnimationBounce animation;

  void init()
  {
    animation.init(
      ENEMY_IDLE_ANIMATION_FRAME_COUNT,
      ENEMY_IDLE_ANIMATION_INTERVAL,
      true
    );
  }

  void update()
  {
    animation.update();
  }

  void render(int x, int y)
  {
    sprites.drawOverwrite(
      x,
      y,
      skeletonIdleSprite,
      animation.frame
    );
  }
}

namespace OrcIdleAnimation
{
  AnimationBounce animation;

  void init()
  {
    animation.init(
      ENEMY_IDLE_ANIMATION_FRAME_COUNT,
      ENEMY_IDLE_ANIMATION_INTERVAL,
      true
    );
  }

  void update()
  {
    animation.update();
  }

  void render(int x, int y)
  {
    sprites.drawOverwrite(
      x,
      y,
      orcIdleSprite,
      animation.frame
    );
  }
}

namespace GolemIdleAnimation
{
  AnimationBounce animation;

  void init()
  {
    animation.init(
      ENEMY_IDLE_ANIMATION_FRAME_COUNT,
      ENEMY_IDLE_ANIMATION_INTERVAL,
      true
    );
  }

  void update()
  {
    animation.update();
  }

  void render(int x, int y)
  {
    sprites.drawOverwrite(
      x,
      y,
      golemIdleSprite,
      animation.frame
    );
  }
}

namespace DemonIdleAnimation
{
  AnimationLoop animation;

  void init()
  {
    animation.init(
      ENEMY_IDLE_ANIMATION_FRAME_COUNT,
      ENEMY_IDLE_ANIMATION_INTERVAL,
      true
    );
  }

  void update()
  {
    animation.update();
  }

  void render(int x, int y)
  {
    sprites.drawOverwrite(
      x,
      y,
      demonIdleSprite,
      animation.frame
    );
  }
}

namespace SorcererIdleAnimation
{
  AnimationBounce animation;

  void init()
  {
    animation.init(
      ENEMY_IDLE_ANIMATION_FRAME_COUNT,
      ENEMY_IDLE_ANIMATION_INTERVAL,
      true
    );
  }

  void update()
  {
    animation.update();
  }

  void render(int x, int y)
  {
    sprites.drawOverwrite(
      x,
      y,
      sorcererIdleSprite,
      animation.frame
    );
  }
}

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
    switch (type)
    {
      case ENEMY_TYPE_SKELETON:
        SkeletonIdleAnimation::render(x, y);
        break;
      case ENEMY_TYPE_ORC:
        OrcIdleAnimation::render(x, y);
        break;
      case ENEMY_TYPE_GOLEM:
        GolemIdleAnimation::render(x, y);
        break;
      case ENEMY_TYPE_DEMON:
        DemonIdleAnimation::render(x, y);
        break;
      case ENEMY_TYPE_SORCERER:
        SorcererIdleAnimation::render(x, y);
        break;
    }
  }
}

void Enemy::init()
{
  SkeletonIdleAnimation::init();
  OrcIdleAnimation::init();
  GolemIdleAnimation::init();
  DemonIdleAnimation::init();
  SorcererIdleAnimation::init();
}

void Enemy::update()
{
  SkeletonIdleAnimation::update();
  OrcIdleAnimation::update();
  GolemIdleAnimation::update();
  DemonIdleAnimation::update();
  SorcererIdleAnimation::update();
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
