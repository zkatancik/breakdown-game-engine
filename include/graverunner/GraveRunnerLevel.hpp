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

  // An internal pointer to Jack- note, he is still added as a gameobject so
  // this should generally be used read-only (e.g. to check if game over)
  std::weak_ptr<Jack> mJack;

  // The number of exits found when loading this level
  int initialNumExits{0};

  const std::string BACKGROUND_IMAGE = "graveyardtiles/png/BG.jpg";

  int currentLevelNumber{1};

  std::shared_ptr<GameObject> createLevelIndicatorObject();

  std::shared_ptr<GameObject> createKeyIndicatorObject();
};

#endif
