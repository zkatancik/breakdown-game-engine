#include "graverunner/BaseEnemy.hpp"

BaseEnemy::BaseEnemy(Level &level): GameObject(level) {
  renderer_ = std::make_shared<TextureRenderComponent>(*this);
  setRenderComponent(renderer_);
}

void BaseEnemy::startUp(float tl_x, float tl_y, float w, float h,
                         std::vector<std::pair<float, float>>& checkpoints, std::shared_ptr<Jack> j) {
  GameObject::startUp(tl_x, tl_y, w, h, ZombieTag);
  setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::DYNAMIC_SOLID));
  counter_ = std::make_shared<CyclicCounterComponent>(*this, 10, true);
  addGenericComponent(counter_);
  addGenericComponent(std::make_shared<RemoveOnCollideComponent>(*this, BulletTag));
}

void BaseEnemy::shutDown() {
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