#include "base/PerformHookOnCollideComponent.hpp"

#include <utility>

#include "base/Level.hpp"

PerformHookOnCollideComponent::PerformHookOnCollideComponent(GameObject &gameObject,
                                                             int tag,
                                                             std::function<void(Level &, std::shared_ptr<GameObject>)> f) :
    GenericComponent(gameObject), mHook(std::move(f)), mTag(tag)   {
}
void PerformHookOnCollideComponent::collision(Level &level, std::shared_ptr<GameObject> obj) {
  if (obj->tag() == mTag) {
    mHook(level, obj);
    hasPerformedHook = true;
  }
}
