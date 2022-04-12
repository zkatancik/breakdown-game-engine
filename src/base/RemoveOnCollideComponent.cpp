#include "base/RemoveOnCollideComponent.hpp"

#include "base/Level.hpp"

#include <iostream>

RemoveOnCollideComponent::RemoveOnCollideComponent(GameObject& gameObject,
                                                   int tag)
    : GenericComponent(gameObject), mTag(tag) {}

void RemoveOnCollideComponent::collision(Level& level,
                                         std::shared_ptr<GameObject> obj) {
  if (obj->tag() == mTag) {
    level.removeObject(obj);
    hasCollided = true;
  }
}
