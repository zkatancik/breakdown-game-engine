#ifndef TD_ENEMY_EDITOR_HPP
#define TD_ENEMY_EDITOR_HPP
#include <base/GridRenderComponent.hpp>

#include "base/GameVariableComponent.hpp"
#include "base/GridObject.hpp"
#include "base/ResourceManager.hpp"
#include "editor/LevelEditButton.hpp"
#include "custom/TdLevel.hpp"
#include "custom/LevelData.hpp"
#include "base/UICounter.hpp"
#include "editor/TDEnemyCounter.hpp"

class TdEnemyEditor : public TdLevel {
 public:
  TdEnemyEditor(int w, int h, int levelNumber)
      : mScreenHeight(h), TdLevel(w - xOffset, h, levelNumber){};

  void refreshLevelEditor();

  void initialize() override;

 private:
  const int xOffset = 360;
  std::shared_ptr<GridRenderComponent> mGridRenderComponent;

  int mScreenHeight;

  std::vector<std::vector<EnemyCounter>> mCounters;

  std::string mSoundPath = "TD2D/Audio/Common/Click1.mp3";

  TdLevelData mLevelData;

  std::vector<TdLevelItem> itemVector = {
      TdLevelItem::SCORPIONS,
      TdLevelItem::WIZARD,
      TdLevelItem::OGRE,
      TdLevelItem::HELMETSWORDSMAN,
      TdLevelItem::HELMETOGRE,
      TdLevelItem::SWORDCAT,
      TdLevelItem::ETCAT,
      TdLevelItem::MOONOGRE,
      TdLevelItem::ETSHURIKEN,
      TdLevelItem::HELMETOGRESWORDSMAN
  };
};

#endif
