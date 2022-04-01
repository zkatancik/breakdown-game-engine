
#include "base/CyclicCounterComponent.hpp"

CyclicCounterComponent::CyclicCounterComponent(GameObject &gameObject, int max,
                                               bool frameGovern)
    : GenericComponent(gameObject),
      counter_(0),
      max_(max),
      frameGovern_(frameGovern) {}

CyclicCounterComponent::CyclicCounterComponent(GameObject &gameObject,
                                               int start, int max)
    : GenericComponent(gameObject), counter_(start), max_(max) {}

void CyclicCounterComponent::update(Level &level) {
  if (!frameGovern_) {
    counter_++;
  } else {
    if (frameCount % GOVERN_FACTOR == 0) {
      counter_++;
    }
  }
  frameCount++;
  if (frameCount == 10000) {
    frameCount = 0;
  }

  counter_ %= max_;
}
