#ifndef GRAVE_RUNNER_HPP
#define GRAVE_RUNNER_HPP
#include <base/GridRenderComponent.hpp>
#include <base/Level.hpp>
#include "graverunner/LevelData.hpp"

class Jack;
class Block;

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

  std::shared_ptr<Jack> jack;

  std::shared_ptr<Block> exitBlock = nullptr;

  int blocksPerRow = 0;
  int rowsOfBlocks = 0;
  Vector2D<int> blockSize;

  SDL_Texture *background{nullptr};
  SDL_Rect bg_dest;

  int currentLevelNumber{1};

  int score{0};

  LevelData mLevelData;

};

#endif
