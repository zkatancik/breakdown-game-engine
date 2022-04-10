#include <base/RemoveOnCollideComponent.hpp>
#include "breakout/Ball.hpp"
#include "box2d/box2d.h"

Ball::Ball(Level& level, float x, float y, float dx, float dy) : GameObject(level, x, y, 30, 30, BreakoutBallTag) {
  renderer_ = std::make_shared<TextureRenderComponent>(*this);
  setRenderComponent(renderer_);
  setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, b2_dynamicBody, false, 0.0f, 1.0, 1.0));
  physicsComponent()->setVx(dx);
  physicsComponent()->setVy(dy);
  auto texture = ResourceManager::getInstance().getTexture("2DBreakout/Graphics/ballGrey.png");
  renderer_->setTexture(texture);
}

void Ball::stop() { physicsComponent()->setVx(0); physicsComponent()->setVy(0);}
