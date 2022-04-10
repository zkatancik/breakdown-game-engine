#ifndef BREAKOUT_GAME_LEVEL_HPP
#define BREAKOUT_GAME_LEVEL_HPP
#include <base/GridRenderComponent.hpp>
#include "base/Level.hpp"
#include "breakout/Ball.hpp"
#include "breakout/Paddle.hpp"
#include "breakout/Block.hpp"
#include "base/ResourceManager.hpp"
#include "base/GameVariableComponent.hpp"

class BreakoutGameLevel : public Level {
 public:
  enum GameDifficulty { Easy = 0, Medium, Hard };

  BreakoutGameLevel(int w, int h, GameDifficulty difficulty, int levelNumber) : Level(w, h),
  gameDifficulty_(difficulty), mLevelNumber(levelNumber)
  {};

  void setDifficulty(GameDifficulty difficulty) {gameDifficulty_ = difficulty;};

  void initialize() override;

  bool isLevelInProgress();

  int getScore();

  int getLevelNumber() {return mLevelNumber;};

  inline bool isGameWon() {
    int numLivesLeft = livesIndicator.lock()->getGenericComponent<GameVariableComponent<int>>()->getVariable();
    return numLivesLeft > 0 && numBlocksLeft == 0;
  }

 private:
  std::shared_ptr<Ball> createBallObject();

  std::shared_ptr<GameObject> createLevelIndicatorObject();

  std::shared_ptr<GameObject> createLivesIndicatorObject();

  std::shared_ptr<GameObject> createScoreIndicatorObject();

  std::weak_ptr<GameObject> livesIndicator;

  std::weak_ptr<GameObject> scoreIndicator;

  int numBlocksLeft;
  const int livesPerGame{3};

  int blocksPerRow = 0;
  int rowsOfBlocks = 0;
  int blocksPerColor = 2;

  bool needNewBall{false};

  Uint32 needNewBallTicks{0};

  GameDifficulty gameDifficulty_{GameDifficulty::Easy};
  int mLevelNumber{1};

};

#endif
