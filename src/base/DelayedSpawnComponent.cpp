#include "base/DelayedSpawnComponent.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"

DelayedSpawnComponent::DelayedSpawnComponent(GameObject &gameObject, int sec) : GenericComponent(gameObject) {
  mCounter = std::make_shared<CounterComponent>(gameObject, sec * 60, 0, CounterComponent::DECREMENT);
  // Remove all generic components to prevent being updated by the level's update function
  // Store it inside the component for later
  mGenericComponents = gameObject.genericComponents();
  gameObject.clearGenericComponents();
  // Remove the render component to prevent the level from rendering it
  // Save the render component for later
  mRenderComponent = gameObject.renderComponent();
  gameObject.setRenderComponent(nullptr);
  // Remove the physics component to prevent PhysicsManager from updating it
  // Save the component for later
  if (gameObject.physicsComponent()) {
    mBodyDef = gameObject.physicsComponent()->getBodyDef();
    gameObject.setPhysicsComponent(nullptr);
    hasPhysicsComponent = true;
  }

  // Add the counter as the only generic component that will be updated by the level
  gameObject.addGenericComponent(mCounter);
}
void DelayedSpawnComponent::update(Level &level) {
  GameObject& go = getGameObject();
  // Logic to add any other components added after the delayed spawn component was added
  auto curGenComponentList = go.genericComponents();
  if (curGenComponentList.size() > 2) {
    for (size_t i = 2; i < curGenComponentList.size(); i++)
      mGenericComponents.push_back(curGenComponentList[i]);
    go.clearGenericComponents();
    for (int i = 0; i < 2; i++) {
      go.addGenericComponent(curGenComponentList[i]);
    }
  }
  if (go.renderComponent() != nullptr) {
    mRenderComponent = go.renderComponent();
    go.setRenderComponent(nullptr);
  }
  if (go.physicsComponent() != nullptr) {
    mBodyDef = go.physicsComponent()->getBodyDef();
    hasPhysicsComponent = true;
    go.setPhysicsComponent(nullptr);
  }
  if (mCounter->getCounter() == 0 && !mHasSpawned) {
    // Remove yourself
    auto self = go.genericComponents()[0];
    go.clearGenericComponents();
    // Add the generic components back
    for (auto c : mGenericComponents)
      go.addGenericComponent(c);
    mGenericComponents.clear();
    // Add render component back
    go.setRenderComponent(mRenderComponent);
    mRenderComponent = nullptr;
    // Add physics component back
    if (hasPhysicsComponent)
      go.setPhysicsComponent(std::make_shared<PhysicsComponent>(go, std::get<0>(mBodyDef),
          std::get<1>(mBodyDef), std::get<2>(mBodyDef)));
    mHasSpawned = true;
  }
}


