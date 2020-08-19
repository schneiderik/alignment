#include "QuestView.h"

#include "Game.h"
#include "Animation.h"

#define QUEST_VIEW_TEXT_X 32
#define QUEST_VIEW_TEXT_Y 2
#define QUEST_VIEW_PATH_COUNT ENEMY_COUNT - 1
#define QUEST_VIEW_PATH_Y 50
#define QUEST_VIEW_ENEMY_SPRITE_MYSTERY_INDEX 5
#define QUEST_VIEW_ENEMY_SPRITE_GRAVE_INDEX 6
#define QUEST_VIEW_CURSOR_X 8
#define QUEST_VIEW_CURSOR_Y -4
#define QUEST_VIEW_CURSOR_ANIMATION_FRAME_COUNT 3
#define QUEST_VIEW_CURSOR_ANIMATION_FRAME_LENGTH 8
#define QUEST_VIEW_CURSOR_ANIMATION_OFFSET_Y_MIN -1
#define QUEST_VIEW_CURSOR_ANIMATION_OFFSET_Y_MAX 1
#define QUEST_VIEW_ENEMY_POSITIONS_LENGTH 2
#define QUEST_VIEW_ENEMY_POSITIONS_X 0
#define QUEST_VIEW_ENEMY_POSITIONS_Y 1

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

  AnimationBounce cursorAnimation;

  void handleInput()
  {
    if (arduboy.justPressed(A_BUTTON))
    {
      Game::goToTitleView();
    }
  }

  void update()
  {
    cursorAnimation.update();
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
      Game::enemy == i
        ? i
        : i < Game::enemy
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

  void renderCursor()
  {
    sprites.drawOverwrite(
      getEnemyPositionX(Game::enemy) + QUEST_VIEW_CURSOR_X,
      getEnemyPositionY(Game::enemy) + QUEST_VIEW_CURSOR_Y + (cursorAnimation.frame - 1),
      questCursorImage,
      0
    );  
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
  cursorAnimation.init(
    QUEST_VIEW_CURSOR_ANIMATION_FRAME_COUNT,
    QUEST_VIEW_CURSOR_ANIMATION_FRAME_LENGTH
  );

  cursorAnimation.run();
}

void QuestView::loop()
{
  handleInput();
  update();
  render();
}
