#include <box2d/b2_body.h>
#include "custom/CustomEnemy.hpp"
#include "custom/Tag.hpp"
#include "base/ResourceManager.hpp"
#include "base/RemoveOnCollideComponent.hpp"
#include "base/PhysicsManager.hpp"

CustomEnemy::CustomEnemy(Level& level, float tl_x, float tl_y, float w, float h,
                      std::string spritePath, TdLevelItem enemyItem)
    : GameObject(level, tl_x, tl_y, w, h, TdEnemyTag) {

  spritePath_ = spritePath;
  enemyItem_ = enemyItem;
  
  renderer_ = std::make_shared<TextureRenderComponent>(*this);
  setRenderComponent(renderer_);

  setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, b2BodyType::b2_dynamicBody, false));
  
  counter_ = std::make_shared<CyclicCounterComponent>(*this, 10, true);
  addGenericComponent(counter_);
  
  addGenericComponent(std::make_shared<RemoveOnCollideComponent>(*this, TdBulletTag));
}

CustomEnemy::~CustomEnemy() {
  genericComponents().clear();
}

void CustomEnemy::update() {
  std::string path = "TD2D/Sprites/Enemies/cpix_enemies/" + spritePath_;
  path += (std::to_string(counter_->getCounter() + 1) + ".png");

  SDL_Texture* texture = ResourceManager::getInstance().getTexture(path);
  renderer_->setTexture(texture);
  renderer_->setFlip(checkDirection());
  GameObject::update();
}

bool CustomEnemy::checkDirection() {
  return PhysicsManager::getInstance().hasStarted() && physicsComponent()->vx() <= 0;
}