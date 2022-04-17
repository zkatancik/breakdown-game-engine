#ifndef COUNTER_COMPONENT_HPP
#define COUNTER_COMPONENT_HPP

#include "base/GenericComponent.hpp"

/**
 * @brief Component for tracking a counter. Can be both set to increment ot decrement.
 */
class CounterComponent : public GenericComponent {
 public:
  enum CounterMode {
    INCREMENT,
    DECREMENT
  };

  CounterComponent(GameObject &gameObject, int targetVal, CounterMode mode = INCREMENT);
  CounterComponent(GameObject &gameObject, int start, int targetVal, CounterMode mode = INCREMENT);
  virtual void update(Level &level);  //!< Update the object.
  inline void collision(Level &level, std::shared_ptr<GameObject> obj){};

  inline int getCounter() { return mCounter;}
  inline void resetCounter() {mCounter = mInitValue;}
  inline void modifyCounter(int mod, CounterMode mode = INCREMENT) {
    if (mode == INCREMENT)
      mCounter = mCounter + mod > mTargetVal ? mCounter : mCounter + mod;
    else if (mode == DECREMENT)
      mCounter = mCounter - mod < mTargetVal ? mCounter : mCounter - mod;
  }

 private:
  int mTargetVal;
  int mCounter;
  int mInitValue;
  CounterMode mMode;
};

#endif
