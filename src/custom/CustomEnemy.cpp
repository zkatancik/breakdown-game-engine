#include <box2d/b2_body.h>
#include "custom/CustomEnemy.hpp"
#include "custom/Tag.hpp"
#include "base/ResourceManager.hpp"
#include "base/RemoveOnCollideComponent.hpp"
#include "base/PhysicsManager.hpp"
#include "base/HealthComponent.hpp"


/**
 * A separate component for updating the sprite sheet for the CustomEnemy.
 */
class CustomEnemyUpdateSpriteSheetComponent : public GenericComponent {
 public:
  CustomEnemyUpdateSpriteSheetComponent(GameObject& gameObject, const std::string& spritePath,
                                              const std::shared_ptr<TextureRenderComponent>& textureRenderComponent) :
                                              GenericComponent(gameObject), mSpritePath(spritePath),
                                              mTRenderComponent(textureRenderComponent) {
    mCounterComponent = std::make_shared<CyclicCounterComponent>(gameObject, 10, true);
    gameObject.addGenericComponent(mCounterComponent);
 }

 bool checkDirection() {
    return PhysicsManager::getInstance().hasStarted() && getGameObject().physicsComponent()->vx() <= 0;
  }

 void update(Level& level) override {
    std::string path = "TD2D/Sprites/Enemies/cpix_enemies/" + mSpritePath;
    path += (std::to_string(mCounterComponent->getCounter() + 1) + ".png");

    SDL_Texture* texture = ResourceManager::getInstance().getTexture(path);
    mTRenderComponent->setTexture(texture);
    mTRenderComponent->setFlip(checkDirection());
  }

 private:
  std::string mSpritePath;
  std::shared_ptr<TextureRenderComponent> mTRenderComponent;
  std::shared_ptr<CyclicCounterComponent> mCounterComponent;

};

CustomEnemy::CustomEnemy(Level& level, float tl_x, float tl_y, float w, float h,
                         std::string spritePath, TdLevelItem enemyItem, int health,
                         const std::function<void(void)>& callBackAtDeath)
    : GameObject(level, tl_x, tl_y, w, h, TdEnemyTag) {

  enemyItem_ = enemyItem;
  
  renderer_ = std::make_shared<TextureRenderComponent>(*this);
  setRenderComponent(renderer_);

  setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, b2BodyType::b2_dynamicBody, false));

  
  addGenericComponent(std::make_shared<RemoveOnCollideComponent>(*this, TdBulletTag));

  addGenericComponent(std::make_shared<CustomEnemyUpdateSpriteSheetComponent>(*this, spritePath, renderer_));

  // Health component for the enemy
  auto healthComponent = std::make_shared<HealthComponent>(*this, health);
  healthComponent->setCallbackAtDeath(callBackAtDeath);
  healthComponent->addHealthModifier(TdBulletTag, -1);
  addGenericComponent(healthComponent);
  addGenericComponent(std::make_shared<RemoveOnCollideComponent>(*this, TdBulletTag));
}

CustomEnemy::~CustomEnemy() {
  genericComponents().clear();
}

