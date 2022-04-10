#ifndef BREAKOUT_GAME_LEVEL_EDITOR_HPP
#define BREAKOUT_GAME_LEVEL_EDITOR_HPP
#include <base/GridRenderComponent.hpp>
#include "breakout/BreakoutGameLevel.hpp"
#include "breakout/Ball.hpp"
#include "breakout/Paddle.hpp"
#include "breakout/Block.hpp"
#include "base/ResourceManager.hpp"
#include "base/GameVariableComponent.hpp"

//TODO: Find a better place for this
const int xOffset = 200;

class BreakoutGameLevelEditor : public BreakoutGameLevel {
 public:

  BreakoutGameLevelEditor(int w, int h, int levelNumber) : BreakoutGameLevel(w - xOffset, h,
                                                                             BreakoutGameLevel::GameDifficulty::Easy,
                                                                             levelNumber) {};

  void initialize() override;


 private:

  std::weak_ptr<GridRenderComponent> mGridRenderComponent;

  BreakoutLevelData mLevelData;

};

#endif
