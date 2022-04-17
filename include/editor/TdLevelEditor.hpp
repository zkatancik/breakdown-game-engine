#ifndef GRAVERUNNER_LEVEL_EDITOR_HPP
#define GRAVERUNNER_LEVEL_EDITOR_HPP
#include <base/GridRenderComponent.hpp>

#include "base/GameVariableComponent.hpp"
#include "base/GridObject.hpp"
#include "base/ResourceManager.hpp"
#include "editor/LevelEditButton.hpp"
#include "custom/TdLevel.hpp"
#include "custom/LevelData.hpp"

class TdLevelEditor : public TdLevel {
 public:
  TdLevelEditor(int w, int h, int levelNumber)
      : mScreenHeight(h), TdLevel(w - xOffset, h, levelNumber){};

  inline void setGridRenderComponent(
      std::shared_ptr<GridRenderComponent> gridRenderComponent) {
    mGridRenderComponent = gridRenderComponent;
  }

  void refreshLevelEditor();

  void initialize() override;

 private:
  const int xOffset = 200;
  std::shared_ptr<GridRenderComponent> mGridRenderComponent;
  int mScreenHeight;
  std::string mSoundPath = "TD2D/Audio/Common/Click1.mp3";

  TdLevelData mLevelData;
  TdLevelItem currentlySelected{TdLevelItem::NONE};

  static std::string getTdBlockPath(TdLevelItem item);

  std::vector<TdLevelItem> itemVector = {
      TdLevelItem::TILE1,        TdLevelItem::TILE2,
      TdLevelItem::TILE3,        TdLevelItem::TILEX,
      TdLevelItem::TILEY,        TdLevelItem::TILEZ,
      TdLevelItem::JACK,         TdLevelItem::PATROLZOMBIE,
      TdLevelItem::FOLLOWZOMBIE, TdLevelItem::KEY,
      TdLevelItem::EXIT};
};

#endif
