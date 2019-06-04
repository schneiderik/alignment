#include "Game.h"

void Game::setState(int state) {
  state_ = state; 
};

void Game::setCurrentEnemyType(int enemyType) {
  currentEnemyType_ = enemyType;
};

int Game::getCurrentEnemyType() {
  return currentEnemyType_;
};

void Game::update() {
  switch(state_) {
    case GAME_STATES::GAME_STATE_TITLE:
      title_.update(*this);
      break;
    case GAME_STATES::GAME_STATE_INFO:
      if (arduboy.justPressed(A_BUTTON)) { setState(GAME_STATES::GAME_STATE_TITLE); }
      break;
    case GAME_STATES::GAME_STATE_QUEST:
      quest_.update(*this);
      break;
    case GAME_STATES::GAME_STATE_BATTLE:
      battle_.update(*this);
      break;
  };
};

void Game::render() {
  switch(state_) {
    case GAME_STATES::GAME_STATE_TITLE:
      title_.render();
      break;
    case GAME_STATES::GAME_STATE_INFO:
      sprites.drawOverwrite(
        INFO_IMAGE_X,
        INFO_IMAGE_Y,
        infoImage,
        0
      );
      break;
    case GAME_STATES::GAME_STATE_QUEST:
      quest_.render(currentEnemyType_);
      break;
    case GAME_STATES::GAME_STATE_BATTLE:
      battle_.render(*this);
      break;
  };
};
          
//    void setCurrentEnemyType(int enemyType) { currentEnemyType_ = enemyType; };
//    int getCurrentEnemyType() { return currentEnemyType_; };
//    int getIntervalLength() { return intervalLength_; };
   
//    void setScore(int score) { currentScore_ = score; };
//    int getScore() { return currentScore_; };
//    void lose() {
//      setCurrentEnemyType(ENEMY_TYPES::SKELETON);
//      setState(GAME_STATES::GAME_OVER); 
//    }
//    void win() {
//      setCurrentEnemyType(ENEMY_TYPES::SKELETON);
//      setState(GAME_STATES::WIN); 
//    }
//    void continueQuest() {
//      setCurrentEnemyType(currentEnemyType_++);
//      setState(GAME_STATES::QUEST);
//    }
//    void update() {
//      switch(state_) {
//        case GAME_STATES::GAME_STATE_TITLE:
//          pTitle_->update();
//          break;
//        case GAME_STATES::INFO:
//          if (arduboy.justPressed(A_BUTTON)) { setState(GAME_STATES::TITLE); }
//          break;
//        case GAME_STATES::QUEST:
//          if (arduboy.justPressed(A_BUTTON)) { setState(GAME_STATES::BATTLE); }
//          break;
//        case GAME_STATES::BATTLE:
//          battle_.update();
//          break;
//        case GAME_STATES::GAME_OVER:
//          if (arduboy.justPressed(A_BUTTON)) { setState(GAME_STATES::TITLE); }
//          break;
//        case GAME_STATES::WIN:
//          if (arduboy.justPressed(A_BUTTON)) { setState(GAME_STATES::TITLE); }
//          break;
//      };
//    };
//    void render() {
//      switch(state_) {
//        case GAME_STATES::GAME_STATE_TITLE:
//          pTitle_->render();
//          break;
//        case GAME_STATES::INFO:
//          renderInfo_();
//          break;
//        case GAME_STATES::QUEST:
//          renderQuest_();
//          break;
//        case GAME_STATES::BATTLE:
//          battle_.render();
//          break;
//        case GAME_STATES::GAME_OVER:
//          renderGameOver_();
//          break;
//        case GAME_STATES::WIN:
//          renderWin_();
//          break;
//      };      
//    }
//
//  private:
//    void renderInfo_() {};
//    void renderQuest_() {};
//    void renderGameOver_() {};
//    void renderWin_() {};
//    int currentScore_ = 0;
//    int currentEnemyType_ = ENEMY_TYPES::SKELETON;
//    int intervalLength_ = INTERVAL_LENGTH;
//    int state_ = GAME_STATES::GAME_STATE_TITLE;
//    Title* pTitle_;
    // Battle battle_;
//};
