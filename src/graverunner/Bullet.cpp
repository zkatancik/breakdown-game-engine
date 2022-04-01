#include "graverunner/Bullet.hpp"

Bullet::Bullet(Level& level) : GameObject(level) {
  auto renderer = std::make_shared<TextureRenderComponent>(*this);
  renderer->setTexture(ResourceManager::getInstance().getTexture("graveyardtiles/png/Tiles/Bone2.png"));
  setRenderComponent(renderer);
  addGenericComponent(std::make_shared<RemoveOnCollideComponent>(*this, ZombieTag));

}
void Bullet::startUp(float x, float y, float w, float h, bool isFacingLeft) {
  GameObject::startUp(x, y, w, h, BulletTag);
  setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::DYNAMIC_SOLID));
  addGenericComponent(std::make_shared<JmpConstantVelocityComponent>(*this, (isFacingLeft ? -1. : 1.) * velocity, 0));
}
void Bullet::update() {
  GameObject::update();
}

