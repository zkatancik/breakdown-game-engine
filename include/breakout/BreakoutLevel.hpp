#ifndef BREAKOUT_LEVEL_HPP
#define BREAKOUT_LEVEL_HPP
#include <base/GridRenderComponent.hpp>
#include <base/Level.hpp>
#include "breakout/Ball.hpp"
#include "breakout/Paddle.hpp"
#include "breakout/Block.hpp"
#include "base/ResourceManager.hpp"

class BreakoutLevel : public Level {
 public:
  enum GameDifficulty { Easy = 0, Medium, Hard };

  BreakoutLevel(int w, int h, GameDifficulty difficulty, Language language) : Level(w, h),
                                                                              language_(language),
                                                                              gameDifficulty_(difficulty)
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

  Paddle *paddle = nullptr;
  Ball *ball = nullptr;

  std::string highestScoreUsername;

  static const int livesPerGame = 3;
  int lives = livesPerGame;
  int highestScore = 0;

  int blocksPerRow = 0;
  int rowsOfBlocks = 0;
  int numBlocks = -1;
  int blocksPerColor = 2;
  std::vector<std::shared_ptr<Block>> blockList;
  bool blocksLeft;

  int level{1};
  bool needNewBall{false};

  Uint32 needNewBallTicks{0};

  int score{0};

  Language language_{Language::ENGLISH};
  GameDifficulty gameDifficulty_{GameDifficulty::Easy};

};

#endif
