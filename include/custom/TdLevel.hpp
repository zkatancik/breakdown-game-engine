#ifndef TD_HPP
#define TD_HPP
#include <base/GridObject.hpp>
#include <base/GridRenderPreviewComponent.hpp>
#include <base/Level.hpp>

#include "custom/LevelData.hpp"

static const int xOffset = 200;
static const int yOffset = 100;

class TdLevel : public Level {
 public:
  TdLevel(int w, int h, int levelNum)
      : Level(w, h),
        currentLevelNumber(levelNum),
        mScreenHeight(h),
        mScreenWidth(w){};

  void initialize() override;

  inline int getLevelNumber() { return currentLevelNumber; };

  /**
   * @brief Is this level in a "win" state?
   */
  bool isLevelWon() const;

  /**
   * @brief Is this level still in progress?
   */
  bool isLevelInProgress() const;

 private:
  int currentLevelNumber{0};
  int mScreenHeight{0};
  int mScreenWidth{0};

  std::string mSoundPath = "Graverunner/2DPlatformer_SFX/ButtonClick_SFX.wav";
  TdLevelItem currentlySelected{TdLevelItem::NONE};
  TdLevelData mLevelData;
  std::weak_ptr<GridObject> mGridObject;
  std::weak_ptr<GameObject> mScoreIndicator;
  std::weak_ptr<GameObject> mCoinIndicator;
  std::weak_ptr<GameObject> mHealthIndicator;

  void createSidebarControls();
  void createBottomBarControls();
  void createGrid();
  std::shared_ptr<GameObject> createLevelIndicatorObject();
  std::shared_ptr<GameObject> createIndicatorObject(std::string label,
                                                    int initialVal, int x, int y);
  void placeEnemy(TdLevelItem enemyType, int delay);

  std::string getTdBlockPath(TdLevelItem item);

  std::vector<TdLevelItem> itemVector = {TdLevelItem::PLACETOWER,
                                         TdLevelItem::ROCKTHROWER};
};

#endif
