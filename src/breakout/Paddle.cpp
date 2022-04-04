#include "breakout/Paddle.hpp"
#include <limits>
#include "base/ResourceManager.hpp"


Paddle::Paddle(Level& level, float sw, float sh, float width, float speed) : GameObject(level, sw / 2 - (width / 2), sh - 50, width, 24, PaddleTag) {
  mRenderer = std::make_shared<TextureRenderComponent>(*this);
  setRenderComponent(mRenderer);
  mRenderer->setTexture(ResourceManager::getInstance().getTexture(getResourcePath("2DBreakout/Graphics") / "paddleRed.png"));
  setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::DYNAMIC_SOLID, 0.0f));
  addGenericComponent(std::make_shared<InputBreakoutComponent>(*this, speed));
}
