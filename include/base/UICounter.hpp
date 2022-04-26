#ifndef BASE_UI_COUNTER
#define BASE_UI_COUNTER
#include "base/Level.hpp"
#include "base/Collection.hpp"


class UICounter : public Collection {
 public:
  explicit UICounter(Level& level, float x, float y, int currentValue = 0, int minValue = 0, int maxValue = 100);

  int getCounterValue();

 private:
  std::weak_ptr<GameObject> mCounterValue;
};

#endif