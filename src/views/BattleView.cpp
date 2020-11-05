#include "BattleView.h"

#include "../../Game.h"
#include "../classes/Counter.h"
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

    if (arduboy.justPressed(LEFT_BUTTON))
    {
      Puzzle::enableFastFall();
    }

    if (arduboy.justReleased(LEFT_BUTTON))
    {
      Puzzle::disableFastFall();
    }

    if (arduboy.justPressed(A_BUTTON))
    {
      Puzzle::swapActiveWeapons();
    }
  }

  void handleStrike(uint8_t enemyType)
  {
    switch (enemyType) {
      case ENEMY_TYPE_SKELETON:
        //Puzzle::stackRandomGem();
        break;
      case ENEMY_TYPE_ORC:
        //Puzzle::queueRandomPreviewGem();
        break;
      case ENEMY_TYPE_GOLEM:
        //Puzzle::swapRandomWeapons();
        break;
      case ENEMY_TYPE_DEMON:
        //Puzzle::enableForcedFastFall();
        break;
      case ENEMY_TYPE_SORCERER:
        //handleStrike(random(0, 4));
        break;
    }
  }

  void handleStrike()
  {
    handleStrike(Game::enemyType);
  }

  void handleAttack()
  {
    attackCounter.init(
      random(
        BATTLE_VIEW_ATTACK_INTERVAL_MIN,
        BATTLE_VIEW_ATTACK_INTERVAL_MAX
      ),
      1,
      &handleAttack
    );

    attackCounter.run();
    EnemyPanel::attack();
  }

  void handleWeaponClear()
  {
    Game::playerHealth--;
  }

  void handleWeaponMatch()
  {
    Game::score += SCORE_MATCH;
    Game::enemyHealth -= DAMAGE_BASE;
  }

  void handleWeaponGemStack()
  {
    Game::score += SCORE_GEM_STACK;
  }

  void update()
  {
    if (Game::playerHealth == 0) Game::goToLoseView();
    if (Game::enemyHealth <= 0)
    {
      if (Game::enemyType == LAST_ENEMY) 
      {
        Game::goToWinView();
      }
      else
      {
        Game::setEnemy(Game::enemyType + 1);
        Game::goToQuestView();
      }
    }

    if (paused) return;

    Puzzle::update();

    if (Puzzle::isClearing()) return;

    EnemyPanel::update();
    attackCounter.update();
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
      Game::enemyHealth,
      Game::enemyHealthMax
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
  attackCounter.init(
    random(
      BATTLE_VIEW_ATTACK_INTERVAL_MIN,
      BATTLE_VIEW_ATTACK_INTERVAL_MAX
    ),
    1,
    &handleAttack
  );

  Game::playerHealth = PLAYER_HEALTH_MAX;
  attackCounter.run();
  EnemyPanel::init(Game::enemyType, &handleStrike);
  Puzzle::init(&handleWeaponClear, &handleWeaponMatch, &handleWeaponGemStack);
}

void BattleView::loop()
{
  handleInput();
  update();
  render();
}
