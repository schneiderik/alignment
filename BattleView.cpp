#include "BattleView.h"

#include "Game.h"
#include "StatBar.h"
#include "EnemyPanel.h"

#define BATTLE_VIEW_STAT_BAR_X 0
#define BATTLE_VIEW_STAT_BAR_Y 0

#define BATTLE_VIEW_ENEMY_PANEL_X 104
#define BATTLE_VIEW_ENEMY_PANEL_Y 12

#define BATTLE_VIEW_ATTACK_INTERVAL_MIN 1000
#define BATTLE_VIEW_ATTACK_INTERVAL_MAX 1400

namespace
{
  Counter attackCounter;

  void handleInput()
  {
  }

  void handleStrike(uint8_t enemyType)
  {
    switch (enemyType) {
      case ENEMY_TYPE_SKELETON:
        //puzzle.weapons.getRandom().popLastGem();
        break;
      case ENEMY_TYPE_ORC:
        //puzzle.previewGems.create();
        break;
      case ENEMY_TYPE_GOLEM:
        //puzzle.weapons.swap(random(WEAPON_CURSOR_MIN, WEAPON_CURSOR_MAX));
        break;
      case ENEMY_TYPE_DEMON:
        //enableForcedFastFall();
        break;
      case ENEMY_TYPE_SORCERER:
        //strike(random(0, 4));
        break;
    }
  }

  void setAttackCounter()
  {
    attackCounter.init(
      random(
        BATTLE_VIEW_ATTACK_INTERVAL_MIN,
        BATTLE_VIEW_ATTACK_INTERVAL_MAX
      ),
      1
    );

    attackCounter.run();
  }

  void update()
  {
    EnemyPanel::update();
    
    if (EnemyPanel::didStrike)
    {
      handleStrike(Game::CurrentEnemy::type);
    }

    attackCounter.update();

    if (!attackCounter.running)
    {
      EnemyPanel::attack();
      setAttackCounter();
    }
  }

  void render()
  {
    StatBar::render(
      BATTLE_VIEW_STAT_BAR_X,
      BATTLE_VIEW_STAT_BAR_Y,
      Game::playerHealth,
      Game::score
    );

    EnemyPanel::render(
      BATTLE_VIEW_ENEMY_PANEL_X,
      BATTLE_VIEW_ENEMY_PANEL_Y,
      Game::CurrentEnemy::health,
      Game::CurrentEnemy::healthMax
    );
  }
}

void BattleView::init()
{
  EnemyPanel::init(
    Game::CurrentEnemy::type,
    Game::CurrentEnemy::idleSprite,
    Game::CurrentEnemy::idleSpriteFrameCount,
    Game::CurrentEnemy::idleSpriteFrameDuration,
    Game::CurrentEnemy::attackSprite,
    Game::CurrentEnemy::attackSpriteFrameCount,
    Game::CurrentEnemy::attackSpriteFrameDuration,
    Game::CurrentEnemy::attackSpriteStrikeFrame
  );

  setAttackCounter();
}

void BattleView::loop()
{
  handleInput();
  update();
  render();
}
