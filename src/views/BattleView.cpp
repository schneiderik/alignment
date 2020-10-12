#include "BattleView.h"

#include "../../Game.h"
#include "../../Counter.h"
#include "../components/StatBar.h"
#include "../components/EnemyPanel.h"
#include "../components/Puzzle.h"

#define BATTLE_VIEW_STAT_BAR_X 0
#define BATTLE_VIEW_STAT_BAR_Y 0

#define BATTLE_VIEW_PUZZLE_X 0
#define BATTLE_VIEW_PUZZLE_Y 14

#define BATTLE_VIEW_ENEMY_PANEL_X 104
#define BATTLE_VIEW_ENEMY_PANEL_Y 12

#define BATTLE_VIEW_PAUSED_X 50
#define BATTLE_VIEW_PAUSED_Y 28

#define BATTLE_VIEW_ATTACK_INTERVAL_MIN 1000
#define BATTLE_VIEW_ATTACK_INTERVAL_MAX 1400

namespace
{
  bool paused;
  Counter attackCounter;

  void handleInput()
  {
    if (arduboy.justPressed(RIGHT_BUTTON))
    {
      paused = !paused;
    }

    if (paused) return;
    if (Puzzle::isClearing()) return;

    if (arduboy.justPressed(UP_BUTTON))
    {
      Puzzle::decrementCursor();
    }

    if (arduboy.justPressed(DOWN_BUTTON))
    {
      Puzzle::incrementCursor();
    }

    if (arduboy.justPressed(A_BUTTON))
    {
      Puzzle::swapActiveWeapons();
    }
  }
  
  void initAttackCounter()
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

  void handleStrike(uint8_t enemyType)
  {
    switch (enemyType) {
      case ENEMY_TYPE_SKELETON:
        //Puzzle::addRandomGem();
        break;
      case ENEMY_TYPE_ORC:
        Puzzle::queueRandomPreviewGem();
        break;
      case ENEMY_TYPE_GOLEM:
        //Puzzle::swapRandomWeapons();
        break;
      case ENEMY_TYPE_DEMON:
        //Puzzle::enableForcedFastFall();
        break;
      case ENEMY_TYPE_SORCERER:
        handleStrike(random(0, 4));
        break;
    }
  }

  void update()
  {
    if (paused) return;

    Puzzle::update();

    if (Puzzle::isClearing()) return;

    EnemyPanel::update();
    attackCounter.update();

    if (!attackCounter.running)
    {
      EnemyPanel::attack();
      initAttackCounter();
    }
    
    if (EnemyPanel::isStriking)
    {
      handleStrike(Game::currentEnemy.type);
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
      Game::currentEnemy.health,
      Game::currentEnemy.healthMax
    );

    Puzzle::render(
      BATTLE_VIEW_PUZZLE_X,
      BATTLE_VIEW_PUZZLE_Y
    );

    if (paused) {
      sprites.drawOverwrite(
        BATTLE_VIEW_PAUSED_X,
        BATTLE_VIEW_PAUSED_Y,
        pausedTextImage,
        0
      );
    }
  }
}

void BattleView::init()
{
  initAttackCounter();
  EnemyPanel::init(Game::currentEnemy.type);
  Puzzle::init();
}

void BattleView::loop()
{
  handleInput();
  update();
  render();
}
