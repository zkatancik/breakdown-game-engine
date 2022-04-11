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
                          levelNumber, true){};

  void initialize() override;

 private:

  void refreshLevelEditor();

  int mScreenHeight;
  std::string mSoundPath = "2DBreakout/SFX/ButtonClick_SFX.wav";

  BreakoutLevelData mLevelData;
  BreakoutLevelItem currentlySelected{BreakoutLevelItem::NONE};

  static std::string getBreakoutBlockPath(const std::string &name)
  {
    return ("2DBreakout/Graphics/element_rectangle_" + name + ".png");
  }

  std::vector<BreakoutLevelItem> itemVector = {
      BreakoutLevelItem::BLOCKBLUE,
      BreakoutLevelItem::BLOCKRED,
      BreakoutLevelItem::BLOCKYELLOW,
      BreakoutLevelItem::BLOCKGREEN,
      BreakoutLevelItem::BLOCKPURPLE,
      BreakoutLevelItem::WALL,
      BreakoutLevelItem::HARDBLOCK};
};

#endif
