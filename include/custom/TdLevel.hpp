#ifndef TD_HPP
#define TD_HPP
#include <base/GridObject.hpp>
#include <base/GridRenderPreviewComponent.hpp>
#include <base/Level.hpp>

#include "custom/LevelData.hpp"

static const int sideBarXOffset = 200;
static const int sideBarYOffset = 100;

class TdLevel : public Level {
 public:
  TdLevel(int w, int h, int levelNum)
      : Level(w, h),
        mLevelNumber(levelNum){};

  void initialize() override;

  inline int getLevelNumber() { return mLevelNumber; };

  /**
   * @brief Is this level in a "win" state?
   */
  bool isLevelWon() const;

  /**
   * @brief Is this level still in progress?
   */
  bool isLevelInProgress() const;

 private:
  int mLevelNumber{0};
  int mNumEnemiesLeft{0};

  std::shared_ptr<GameObject> mStartWaveButton;

  std::string mSoundPath = "TD2D/Audio/Common/Click2.mp3";
  TdLevelItem currentlySelected{TdLevelItem::NONE};
  TdLevelData mLevelData;
  std::weak_ptr<GridObject> mGridObject;
  std::weak_ptr<GameObject> mScoreIndicator;
  std::weak_ptr<GameObject> mCoinIndicator;
  std::weak_ptr<GameObject> mHealthIndicator;
  std::weak_ptr<GameObject> mCurrentWaveNumberIndicator;

  void createSidebarControls();
  void createBottomBarControls();
  void createGrid();
  std::shared_ptr<GameObject> createLevelIndicatorObject();
  std::shared_ptr<GameObject> createIndicatorObject(std::string label,
                                                    int initialVal, int x, int y);
  void spawnEnemy(TdLevelItem enemyType, int delay);

  std::string getTdBlockPath(TdLevelItem item);

  std::vector<TdLevelItem> itemVector = {TdLevelItem::PLACETOWER,
                                         TdLevelItem::ROCKTHROWER};
};

#endif
