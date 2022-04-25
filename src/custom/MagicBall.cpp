#include "custom/MagicBall.hpp"

#include <box2d/b2_body.h>

#include "base/ConstantVelocityComponent.hpp"
#include "base/DespawnOnRadiusComponent.hpp"
#include "base/PhysicsComponent.hpp"
#include "base/RemoveOnCollideComponent.hpp"
#include "base/ResourceManager.hpp"
#include "base/TextureRenderComponent.hpp"
#include "custom/Tag.hpp"

MagicBall::MagicBall(Level& level, float x, float y, float w, float h, float vx,
                     float vy, float radius)
    : GameObject(level, x, y, w, h, TdBulletTag) {
  auto renderer = std::make_shared<TextureRenderComponent>(*this);
  renderer->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/Bullets/Bullets.png"));
  renderer->setCrop({43, 300, 25, 25});
  setRenderComponent(renderer);
  setPhysicsComponent(std::make_shared<PhysicsComponent>(
      *this, b2BodyType::b2_dynamicBody, false));
  addGenericComponent(
      std::make_shared<ConstantVelocityComponent>(*this, vx, vy));
  addGenericComponent(std::make_shared<DespawnOnRadius>(*this, x, y, radius));
}

void MagicBall::update() { GameObject::update(); }
