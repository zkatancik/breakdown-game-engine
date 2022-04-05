#include <box2d/b2_body.h>
#include "graverunner/BaseEnemy.hpp"

BaseEnemy::BaseEnemy(Level& level, float tl_x, float tl_y, float w, float h,
                     std::vector<std::pair<float, float>>& checkpoints,
                     std::shared_ptr<Jack> j)
    : GameObject(level, tl_x, tl_y, w, h, ZombieTag) {
  renderer_ = std::make_shared<TextureRenderComponent>(*this);
  setRenderComponent(renderer_);
  setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, b2BodyType::b2_dynamicBody, false));
  counter_ = std::make_shared<CyclicCounterComponent>(*this, 10, true);
  addGenericComponent(counter_);
  addGenericComponent(std::make_shared<RemoveOnCollideComponent>(*this, BulletTag));
}

BaseEnemy::~BaseEnemy() {
  genericComponents().clear();
}

void BaseEnemy::update() {
  std::string path = "zombies/male/Walk";
  path += (std::to_string(counter_->getCounter() + 1) + ".png");

  SDL_Texture* texture = ResourceManager::getInstance().getTexture(path);
  renderer_->setTexture(texture);
  renderer_->setFlip(checkDirection());
  GameObject::update();
}

bool BaseEnemy::checkDirection() {
  return PhysicsManager::getInstance().hasStarted() && physicsComponent()->vx() <= 0;
}