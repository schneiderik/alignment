#include "QuestView.h"

#include "../../Game.h"
#include "../classes/Counter.h"

#define QUEST_VIEW_TEXT_X 32
#define QUEST_VIEW_TEXT_Y 2
#define QUEST_VIEW_PATH_COUNT ENEMY_COUNT - 1
#define QUEST_VIEW_PATH_Y 50
#define QUEST_VIEW_ENEMY_SPRITE_MYSTERY_INDEX 5
#define QUEST_VIEW_ENEMY_SPRITE_GRAVE_INDEX 6
#define QUEST_VIEW_CURSOR_X 8
#define QUEST_VIEW_CURSOR_Y -4
#define QUEST_VIEW_ENEMY_POSITIONS_LENGTH 2
#define QUEST_VIEW_ENEMY_POSITIONS_X 0
#define QUEST_VIEW_ENEMY_POSITIONS_Y 1
#define QUEST_VIEW_BOUNCING_CURSOR_FRAME_COUNT 3
#define QUEST_VIEW_BOUNCING_CURSOR_INTERVAL 8

namespace
{
  const int pathOffsets[QUEST_VIEW_PATH_COUNT] = {
    16,
    54,
    64,
    102
  };

  const int enemyPositions[ENEMY_COUNT][QUEST_VIEW_ENEMY_POSITIONS_LENGTH] = {
    {5, 16},
    {29, 31},
    {53, 16},
    {77, 31},
    {101, 16}
  };

  Counter counter;

  void handleInput()
  {
    if (arduboy.justPressed(A_BUTTON))
    {
      Game::goToBattleView();
    }
  }

  void update()
  {
    counter.update();
  }

  void renderText()
  {
    sprites.drawOverwrite(
      QUEST_VIEW_TEXT_X,
      QUEST_VIEW_TEXT_Y,
      questText,
      0
    );     
  }

  int getEnemyPositionX(uint8_t i)
  {
    return enemyPositions[i][QUEST_VIEW_ENEMY_POSITIONS_X];
  }

  int getEnemyPositionY(uint8_t i)
  {
    return enemyPositions[i][QUEST_VIEW_ENEMY_POSITIONS_Y];
  }

  void renderEnemy(uint8_t i)
  {
    sprites.drawOverwrite(
      getEnemyPositionX(i),
      getEnemyPositionY(i),
      questSprite,
      Game::enemyType == i
        ? i
        : i < Game::enemyType
          ? QUEST_VIEW_ENEMY_SPRITE_GRAVE_INDEX
          : QUEST_VIEW_ENEMY_SPRITE_MYSTERY_INDEX
    );
  }

  void renderEnemies()
  {
    for (uint8_t i = 0; i < ENEMY_COUNT; i++)
    {
      renderEnemy(i);
    }
  }

  void renderPath(uint8_t i) 
  {
    sprites.drawOverwrite(
      pathOffsets[i],
      QUEST_VIEW_PATH_Y,
      i % 2 == 0 ? pathImage : pathReverseImage,
      0
    );
  }

  void renderPaths()
  {
    for (uint8_t i = 0; i < QUEST_VIEW_PATH_COUNT; i++)
    {
      renderPath(i);
    }
  }

  void renderCursor()
  {
    sprites.drawOverwrite(
      getEnemyPositionX(Game::enemyType) + QUEST_VIEW_CURSOR_X,
      getEnemyPositionY(Game::enemyType) + QUEST_VIEW_CURSOR_Y + counter.frame - 1,
      questCursorImage,
      0
    );  
  }

  void render()
  {
    renderCursor();
    renderText();
    renderEnemies();
    renderPaths();
  }
}

void QuestView::init()
{
  counter.init(
    QUEST_VIEW_BOUNCING_CURSOR_FRAME_COUNT,
    QUEST_VIEW_BOUNCING_CURSOR_INTERVAL
  );

  counter.alternate();
}

void QuestView::loop()
{
  handleInput();
  update();
  render();
}
