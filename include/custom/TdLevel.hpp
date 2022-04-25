#ifndef TD_HPP
#define TD_HPP
#include <base/GridObject.hpp>
#include <base/GridRenderPreviewComponent.hpp>
#include <base/Level.hpp>

#include "base/DelayedSpawnComponent.hpp"
#include "base/GameVariableComponent.hpp"
#include "base/GridObject.hpp"
#include "base/PerformHookOnCollideComponent.hpp"
#include "custom/CustomLevelEditButton.hpp"
#include "custom/LevelData.hpp"
#include "custom/LevelTimer.hpp"
#include "custom/MagicTower.hpp"
#include "custom/Mouse.hpp"
#include "custom/NonHostileEnemy.hpp"
#include "custom/RockThrowerTower.hpp"
#include "custom/Tag.hpp"
#include "custom/TdBlock.hpp"
#include "custom/TdButton.hpp"

static const int sideBarXOffset = 200;
static const int sideBarYOffset = 100;

/**
 * @brief A class representing a level, including all of its necessary data, of
 * our Tower Defense game.
 */
class TdLevel : public Level {
 public:
  /**
   * @brief Construct a new Td Level object
   *
   * @param w level width
   * @param h level height
   * @param levelNum level number
   */
  TdLevel(int w, int h, int levelNum) : Level(w, h), mLevelNumber(levelNum){};

  /**
   * @brief Setup this level, including loading it from a file, creating game
   * objects, creating UI / UI objects, etc.
   */
  void initialize() override;

  /**
   * @brief Get this level's number
   *
   * @return int level num
   */
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

  std::weak_ptr<GameObject> mStartWaveButton;

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
                                                    int initialVal, int x,
                                                    int y);

  void spawnEnemy(TdLevelItem enemyType, int delay, int enemyNumber);

  std::string getTdBlockPath(TdLevelItem item);

  std::vector<TdLevelItem> itemVector = {
      TdLevelItem::PLACETOWER, TdLevelItem::ROCKTHROWER,
      TdLevelItem::ANTITANKMINE, TdLevelItem::MAGICTOWER};
};

#endif
