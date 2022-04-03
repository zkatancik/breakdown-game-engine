#include "breakout/Paddle.hpp"

#include "base/ResourceManager.hpp"


Paddle::Paddle(Level& level, float x, float y, float w, float h, float speed) : GameObject(level, x, y, w, h, PaddleTag) {
  mRenderer = std::make_shared<TextureRenderComponent>(*this);
  setRenderComponent(mRenderer);
  mRenderer->setTexture(ResourceManager::getInstance().getTexture("paddleRed.png"));
  addGenericComponent(std::make_shared<InputBreakoutComponent>(*this, speed));
}
