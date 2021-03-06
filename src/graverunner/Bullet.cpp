#include "graverunner/Bullet.hpp"

#include <box2d/b2_body.h>

#include "base/ConstantVelocityComponent.hpp"
#include "base/PhysicsComponent.hpp"
#include "base/RemoveOnCollideComponent.hpp"
#include "base/ResourceManager.hpp"
#include "base/TextureRenderComponent.hpp"
#include "graverunner/Tag.hpp"

Bullet::Bullet(Level& level, float x, float y, float w, float h,
               bool isFacingLeft)
    : GameObject(level, x, y, w, h, GraveRunnerBulletTag) {
  auto renderer = std::make_shared<TextureRenderComponent>(*this);
  renderer->setTexture(ResourceManager::getInstance().getTexture(
      "Graverunner/graveyardtiles/png/Tiles/Bone2.png"));
  setRenderComponent(renderer);
  addGenericComponent(
      std::make_shared<RemoveOnCollideComponent>(*this, GraveRunnerZombieTag));
  setPhysicsComponent(std::make_shared<PhysicsComponent>(
      *this, b2BodyType::b2_dynamicBody, false));
  addGenericComponent(std::make_shared<ConstantVelocityComponent>(
      *this, (isFacingLeft ? -1. : 1.) * velocity, 0));
}

void Bullet::update() { GameObject::update(); }
