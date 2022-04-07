#include <box2d/b2_body.h>
#include "graverunner/Bullet.hpp"
#include "graverunner/Tag.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/RemoveOnCollideComponent.hpp"
#include "base/ConstantVelocityComponent.hpp"
#include "base/PhysicsComponent.hpp"
#include "base/ResourceManager.hpp"

Bullet::Bullet(Level& level, float x, float y, float w, float h,
               bool isFacingLeft)
    : GameObject(level, x, y, w, h, BulletTag) {
  auto renderer = std::make_shared<TextureRenderComponent>(*this);
  renderer->setTexture(ResourceManager::getInstance().getTexture("Graverunner/graveyardtiles/png/Tiles/Bone2.png"));
  setRenderComponent(renderer);
  addGenericComponent(std::make_shared<RemoveOnCollideComponent>(*this, ZombieTag));
  setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, b2BodyType::b2_dynamicBody, false));
  addGenericComponent(std::make_shared<JmpConstantVelocityComponent>(*this, (isFacingLeft ? -1. : 1.) * velocity, 0));
}

void Bullet::update() {
  GameObject::update();
}

