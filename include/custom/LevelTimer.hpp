#ifndef CUSTOM_LEVEL_TIMER
#define CUSTOM_LEVEL_TIMER
#include <functional>

#include "base/GameObject.hpp"
#include "base/Tag.hpp"

/**
 * @brief A count-down timer used in the TDLevel object to show when enemies
 * will spawn. Displays the number of seconds remaining.
 */
class TowerDefenseLevelTimer : public GameObject {
 public:
  /**
   * @brief Construct a new Tower Defense Level Timer object
   *
   * @param level the level this timer belongs to
   * @param x x coordinate of where to display the timer
   * @param y y coordinate of where to display the timer
   * @param sec timer duration (seconds)
   * @param callBackWhenDone hook to call when timer expires
   * @param timerLabel string label for display
   */
  TowerDefenseLevelTimer(Level& level, float x, float y, int sec,
                         std::function<void(void)> callBackWhenDone,
                         const std::string& timerLabel = "Time Remaining");
};

#endif
