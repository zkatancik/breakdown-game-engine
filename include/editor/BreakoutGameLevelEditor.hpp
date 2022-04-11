#ifndef BREAKOUT_GAME_LEVEL_EDITOR_HPP
#define BREAKOUT_GAME_LEVEL_EDITOR_HPP
#include <base/GridRenderComponent.hpp>

#include "base/GameVariableComponent.hpp"
#include "base/ResourceManager.hpp"
#include "breakout/Ball.hpp"
#include "breakout/Block.hpp"
#include "breakout/BreakoutGameLevel.hpp"
#include "breakout/LevelData.hpp"
#include "breakout/Paddle.hpp"
#include "editor/LevelEditButton.hpp"

// TODO: Find a better place for this
const int xOffset = 200;

class BreakoutGameLevelEditor : public BreakoutGameLevel {
 public:
  BreakoutGameLevelEditor(int w, int h, int levelNumber)
      : mScreenHeight(h),
        BreakoutGameLevel(w - xOffset, h,
                          BreakoutGameLevel::GameDifficulty::Easy,
                          levelNumber, true){
                            std::cout << "BreakoutGameLevelEditor Constructor->IsEditor:" << std::to_string(true) << "\n";
                          };

  inline void setGridRenderComponent(
      std::shared_ptr<GridRenderComponent> gridRenderComponent) {
    mGridRenderComponent = gridRenderComponent;
  }

  void initialize() override;

 private:
  std::shared_ptr<GridRenderComponent> mGridRenderComponent;
  int mScreenHeight;
  std::string mSoundPath = "2DBreakout/SFX/ButtonClick_SFX.wav";

  BreakoutLevelData mLevelData;
  BreakoutLevelItem currentlySelected{BreakoutLevelItem::NONE};

  std::map<BreakoutLevelItem, std::string> itemMap = {
      {BreakoutLevelItem::PLAINBLOCK,
       "2DBreakout/Graphics/element_blue_rectangle.png"},
      {BreakoutLevelItem::WALL,
       "2DBreakout/Graphics/element_wall_rectangle.png"},
      {BreakoutLevelItem::HARDBLOCK,
       "2DBreakout/Graphics/element_grey_rectangle.png"}};
};

#endif
