#ifndef CYCLIC_COUNTER_HPP
#define CYCLIC_COUNTER_HPP

#include "base/GenericComponent.hpp"

/**
 * @brief Component for tracking a counter which cycles through a
 * fixed number of integer values.
 */
class CyclicCounterComponent : public GenericComponent {
 public:
  CyclicCounterComponent(GameObject &gameObject, int max, bool frameGovern);
  CyclicCounterComponent(GameObject &gameObject, int start, int max);
  virtual void update(Level &level);  //!< Update the object.
  inline void collision(Level &level, std::shared_ptr<GameObject> obj){};

  inline int getCounter() { return counter_; }
  inline void setCounter(int val) { counter_ = val; }

 private:
  int counter_;
  int max_;
  bool frameGovern_;

  const int GOVERN_FACTOR{6};
  int frameCount{0};
};

#endif  // CYCLIC_COUNTER_HPP
