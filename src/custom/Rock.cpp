#include "custom/Rock.hpp"

#include <box2d/b2_body.h>

#include "base/ConstantVelocityComponent.hpp"
#include "base/PhysicsComponent.hpp"
#include "base/RemoveOnCollideComponent.hpp"
#include "base/ResourceManager.hpp"
#include "base/TextureRenderComponent.hpp"
#include "custom/Tag.hpp"

Rock::Rock(Level& level, float x, float y, float w, float h, float vx, float vy)
    : GameObject(level, x, y, w, h, TdBulletTag) {
  auto renderer = std::make_shared<TextureRenderComponent>(*this);
  renderer->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/Bullets/Bullets.png"));
  renderer->setCrop({209, 152, 38, 24});
  setRenderComponent(renderer);
  addGenericComponent(
      std::make_shared<RemoveOnCollideComponent>(*this, TdEnemyTag));
  setPhysicsComponent(std::make_shared<PhysicsComponent>(
      *this, b2BodyType::b2_dynamicBody, false));
  addGenericComponent(
      std::make_shared<ConstantVelocityComponent>(*this, vx, vy));
}

void Rock::update() { GameObject::update(); }
