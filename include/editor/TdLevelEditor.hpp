#ifndef TD_LEVEL_EDITOR_HPP
#define TD_LEVEL_EDITOR_HPP
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
  const int xOffset = 360;
  std::shared_ptr<GridRenderComponent> mGridRenderComponent;
  int mScreenHeight;
  std::string mSoundPath = "TD2D/Audio/Common/Click1.mp3";

  TdLevelData mLevelData;
  TdLevelItem currentlySelected{TdLevelItem::NONE};

  static std::string getTdBlockPath(TdLevelItem item);

  std::vector<TdLevelItem> itemVector = {
      TdLevelItem::END,
      TdLevelItem::START,
      TdLevelItem::PATHBLOCK0,
      TdLevelItem::PATHBLOCK1,
      TdLevelItem::PATHBLOCK2,
      TdLevelItem::PATHBLOCK3,
      TdLevelItem::PATHBLOCK4,
      TdLevelItem::PATHBLOCK5,
      TdLevelItem::PATHBLOCK6,
      TdLevelItem::PATHBLOCK7,
      TdLevelItem::PATHBLOCK8,
      TdLevelItem::PATHBLOCK9,
      TdLevelItem::PATHBLOCKA,
      TdLevelItem::PLACETOWER,
      TdLevelItem::BUSH1,
      TdLevelItem::BUSH2,
      TdLevelItem::BUSH3,
      TdLevelItem::FOREST1,
      TdLevelItem::GRASS1,
      TdLevelItem::GRASS2,
      TdLevelItem::GRASS3,
      TdLevelItem::GRASS4,
      TdLevelItem::STONE1,
      TdLevelItem::TREE1,
      TdLevelItem::TREE2,
      TdLevelItem::TREE3,
      TdLevelItem::TREE4,
      TdLevelItem::TREE5
      };
};

#endif
