#ifndef GRAVERUNNER_LEVEL_EDITOR_HPP
#define GRAVERUNNER_LEVEL_EDITOR_HPP
#include <base/GridRenderComponent.hpp>

#include "base/GameVariableComponent.hpp"
#include "base/ResourceManager.hpp"
#include "graverunner/GraveRunnerLevel.hpp"
#include "graverunner/LevelData.hpp"
#include "editor/LevelEditButton.hpp"

class GraveRunnerLevelEditor : public GraveRunnerLevel {
 public:
  GraveRunnerLevelEditor(int w, int h, int levelNumber)
      : mScreenHeight(h), GraveRunnerLevel(w - xOffset, h, levelNumber){};

  inline void setGridRenderComponent(
      std::shared_ptr<GridRenderComponent> gridRenderComponent) {
    mGridRenderComponent = gridRenderComponent;
  }

  void initialize() override;

 private:
  static const int xOffset = 200;
  std::shared_ptr<GridRenderComponent> mGridRenderComponent;
  int mScreenHeight;
  std::string mSoundPath = "Graverunner/2DPlatformer_SFX/ButtonClick_SFX.wav";

  GraveRunnerLevelData mLevelData;
  GraveRunnerLevelItem currentlySelected{GraveRunnerLevelItem::NONE};

  static std::string getGraverunnerBlockPath(GraveRunnerLevelItem item);

  std::vector<GraveRunnerLevelItem> itemVector = {
      GraveRunnerLevelItem::TILE1,        GraveRunnerLevelItem::TILE2,
      GraveRunnerLevelItem::TILE3,        GraveRunnerLevelItem::TILEX,
      GraveRunnerLevelItem::TILEY,        GraveRunnerLevelItem::TILEZ,
      GraveRunnerLevelItem::CRATE,        GraveRunnerLevelItem::JACK,
      GraveRunnerLevelItem::PATROLZOMBIE, GraveRunnerLevelItem::FOLLOWZOMBIE,
      GraveRunnerLevelItem::WALL,         GraveRunnerLevelItem::KEY,
      GraveRunnerLevelItem::EXIT};
};

#endif
