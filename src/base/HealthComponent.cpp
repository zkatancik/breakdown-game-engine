#include "base/HealthComponent.hpp"

#include <utility>

HealthComponent::HealthComponent(GameObject &gameObject, int health)
    : GenericComponent(gameObject), mHealth(health) {}

void HealthComponent::collision(Level &level, std::shared_ptr<GameObject> obj) {
  auto healthModifier = mHealthModifiers.find(obj->tag());
  if (healthModifier != mHealthModifiers.end()) {
    mHealth += healthModifier->second;
  }
}

void HealthComponent::update(Level &level) {
  if (mHealth <= 0) {
    level.removeObject(getGameObject().shared_from_this());
    mCallbackAtDeath();
  } else {
    mCallbackAtUpdate(mHealth);
  }
}

void HealthComponent::setCallbackAtDeath(
    const std::function<void(void)> &callbackAtDeath) {
  mCallbackAtDeath = callbackAtDeath;
}

void HealthComponent::setCallbackAtUpdate(
    const std::function<void(int)> &callbackAtUpdate) {
  mCallbackAtUpdate = callbackAtUpdate;
}

void HealthComponent::addHealthModifier(int tag, int healthIncrementVal) {
  auto healthModifier = mHealthModifiers.find(tag);
  if (healthModifier == mHealthModifiers.end()) {
    mHealthModifiers.insert({tag, healthIncrementVal});
  }
}
