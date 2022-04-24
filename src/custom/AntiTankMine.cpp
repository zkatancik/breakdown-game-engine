#include "custom/AntiTankMine.hpp"

#include <utility>

#include "base/ResourceManager.hpp"
#include "custom/PeriodicRockThrowComponent.hpp"
#include "custom/Tag.hpp"
#include "base/Level.hpp"
#include "base/RemoveOnCollideComponent.hpp"
#include "base/PerformHookOnCollideComponent.hpp"
#include "base/CounterComponent.hpp"
#include "box2d/box2d.h"

/**
 * A component exclusive to AntiTankMine, which uses a counter to animate its explosion, and then removes itself from the level
 */
class ExplodeAndRemoveComponent : public GenericComponent {
 public:
  ExplodeAndRemoveComponent(GameObject& gameObject, std::shared_ptr<TextureRenderComponent> renderer) : GenericComponent(gameObject),
  mRenderer(std::move(renderer)) {
    mCounter = std::make_shared<CounterComponent>(gameObject, 0, 8);
    gameObject.addGenericComponent(mCounter);
  };

  void update(Level& level) override {
    std::string path = "TD2D/Sprites/Towers/cpix_towers/";
    if (mCounter->getCounter() == 8)
      level.removeObject(getGameObject().shared_from_this());
    else {
      path += std::to_string(mCounter->getCounter() + 54) + ".png";
      SDL_Texture *texture = ResourceManager::getInstance().getTexture(path);
      mRenderer->setTexture(texture);
    }
  }
 private:
  std::shared_ptr<TextureRenderComponent> mRenderer;
  std::shared_ptr<CounterComponent> mCounter;
};


AntiTankMine::AntiTankMine(Level &level, float x, float y, Vector2D<int> bs)
    : GameObject(level, x, y, bs.x, bs.y, TdAntiTankTowerTag) {
  renderer_ = std::make_shared<TextureRenderComponent>(*this);
  setRenderComponent(renderer_);
  setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, b2BodyType::b2_dynamicBody, true));
  renderer_->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/Towers/cpix_towers/40.png"));
  // Explode on collision with an enemy
  auto performHookOnCollideComponent =
      std::make_shared<PerformHookOnCollideComponent>(*this,
                                                      TdEnemyTag,
                                                       [&] (Level& level, const std::shared_ptr<GameObject>& gameObject) {
        if (!mHasExploded) {
          Mix_PlayChannel(1, ResourceManager::getInstance().getChunk("TD2D/Audio/Explosions/Explosion1.mp3"),
                          0);
          addGenericComponent(std::make_shared<ExplodeAndRemoveComponent>(*this, renderer_));
          mHasExploded = true;
        }
  });
  addGenericComponent(performHookOnCollideComponent);
}
