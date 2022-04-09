#ifndef GRAVE_RUNNER_HPP
#define GRAVE_RUNNER_HPP
#include <base/GridRenderComponent.hpp>
#include <base/Level.hpp>
#include "graverunner/LevelData.hpp"

class Jack;
class BreakoutBlock;

class GraveRunnerLevel : public Level {
 public:
  GraveRunnerLevel(int w, int h, int levelNum) : Level(w, h), currentLevelNumber(levelNum) {};

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

  const std::string BACKGROUND_IMAGE = "graveyardtiles/png/BG.jpg";

  int currentLevelNumber{1};

  GraveRunnerLevelData mLevelData;
};

#endif
