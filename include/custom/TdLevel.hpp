#ifndef TD_HPP
#define TD_HPP
#include <base/GridRenderComponent.hpp>
#include <base/Level.hpp>

#include "custom/LevelData.hpp"

class TdLevel : public Level {
 public:
  TdLevel(int w, int h, int levelNum)
      : Level(w, h), currentLevelNumber(levelNum){};

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

  std::shared_ptr<GameObject> createLevelIndicatorObject();

  std::shared_ptr<GameObject> createScoreIndicatorObject();
};

#endif
