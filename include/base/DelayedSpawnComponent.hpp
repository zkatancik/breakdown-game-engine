#ifndef BASE_DELAYED_SPAWN_COMPONENT
#define BASE_DELAYED_SPAWN_COMPONENT
#include "base/GenericComponent.hpp"
#include "base/CounterComponent.hpp"
#include "base/RenderComponent.hpp"
#include "base/PhysicsComponent.hpp"
#include <vector>

class DelayedSpawnComponent : public GenericComponent {
 public:
  DelayedSpawnComponent(GameObject& gameObject, int sec);

  void update(Level& level) override;
 private:
  bool mHasSpawned{false};
  std::vector<std::shared_ptr<GenericComponent>> mGenericComponents;
  std::shared_ptr<RenderComponent> mRenderComponent;
  std::tuple<b2BodyDef, b2FixtureDef, b2PolygonShape> mBodyDef;
  bool hasPhysicsComponent{false};
  std::shared_ptr<CounterComponent> mCounter;
};
#endif