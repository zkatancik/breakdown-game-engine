#include <base/RemoveOnCollideComponent.hpp>
#include "breakout/Ball.hpp"

Ball::Ball(Level& level, float x, float y, float dx, float dy) : GameObject(level, x, y, 30, 30, BallTag) {
  renderer_ = std::make_shared<TextureRenderComponent>(*this);
  setRenderComponent(renderer_);
  setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::DYNAMIC_SOLID, 0.0f));
  addGenericComponent(std::make_shared<RemoveOnCollideComponent>(*this, LevelBoundaryTag));
  physicsComponent()->setVx(dx);
  physicsComponent()->setVy(dy);
  auto texture = ResourceManager::getInstance().getTexture("2DBreakout/Graphics/ballGrey.png");
  renderer_->setTexture(texture);
}

void Ball::stop() { physicsComponent()->setVx(0); physicsComponent()->setVy(0);}
