#ifndef BREAKOUT_GAME_LEVEL_HPP
#define BREAKOUT_GAME_LEVEL_HPP
#include <base/GridRenderComponent.hpp>
#include "breakout/BreakoutLevel.hpp"
#include "breakout/Ball.hpp"
#include "breakout/Paddle.hpp"
#include "breakout/Block.hpp"
#include "base/ResourceManager.hpp"

class BreakoutGameLevel : public BreakoutLevel {
 public:
  enum GameDifficulty { Easy = 0, Medium, Hard };

  BreakoutGameLevel(int w, int h, GameDifficulty difficulty, Language language, int levelNumber) : BreakoutLevel(w, h, language),
  gameDifficulty_(difficulty), mLevelNumber(levelNumber)
  {};

  void initialize() override;

  inline void setGridRenderComponent(
      std::shared_ptr<GridRenderComponent> gridRenderComponent) {
    mGridRenderComponent = gridRenderComponent;
  }

  inline std::shared_ptr<GridRenderComponent> getGridRenderComponent() {
    return mGridRenderComponent;
  }

 private:
  std::shared_ptr<GridRenderComponent> mGridRenderComponent;

  std::string highestScoreUsername;

  static const int livesPerGame = 3;
  int lives = livesPerGame;
  int highestScore = 0;

  int blocksPerRow = 0;
  int rowsOfBlocks = 0;
  int numBlocks = -1;
  int blocksPerColor = 2;
  bool blocksLeft;

  bool needNewBall{false};

  Uint32 needNewBallTicks{0};

  int score{0};

  Language language_{Language::ENGLISH};
  GameDifficulty gameDifficulty_{GameDifficulty::Easy};
  int mLevelNumber{1};

};

#endif
