#include "base/CounterComponent.hpp"


CounterComponent::CounterComponent(GameObject &gameObject, int targetVal, CounterMode mode)
    : GenericComponent(gameObject),
      mTargetVal(targetVal),
      mCounter(0),
      mInitValue(0),
      mMode(mode) {}

CounterComponent::CounterComponent(GameObject &gameObject,
                                   int start, int targetVal, CounterMode mode)
                                   : GenericComponent(gameObject), mTargetVal(targetVal), mCounter(start), mInitValue(start),
                                   mMode(mode) {}

void CounterComponent::update(Level &level) {
  if (mMode == INCREMENT)
    mCounter = mCounter + 1 > mTargetVal ? mCounter : mCounter + 1;
  else if (mMode == DECREMENT)
    mCounter = mCounter - 1 < mTargetVal ? mCounter : mCounter - 1;
}
