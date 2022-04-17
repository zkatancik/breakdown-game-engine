#ifndef CUSTOM_LEVEL_TIMER
#define CUSTOM_LEVEL_TIMER
#include "base/GameObject.hpp"
#include "base/Tag.hpp"
#include <functional>

/**
 * @brief A count-down timer used in the TDLevel object to show when enemies will spawn.
 */
class TowerDefenseLevelTimer : public GameObject {
 public:
  TowerDefenseLevelTimer(Level& level, float x, float y, int sec, std::function<void(void)> callBackWhenDone,
                         const std::string& timerLabel = "Time Remaining");

};


#endif
