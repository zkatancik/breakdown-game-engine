#include "breakout/Paddle.hpp"

Paddle::Paddle(Level& level, float sw, float sh, float width, float speed)
    : GameObject(level, sw / 2 - (width / 2), sh - 50, width, 24, BreakoutPaddleTag) {
  mRenderer = std::make_shared<TextureRenderComponent>(*this);
  setRenderComponent(mRenderer);
  mRenderer->setTexture(ResourceManager::getInstance().getTexture(
      "2DBreakout/Graphics/paddleRed.png"));
  setPhysicsComponent(std::make_shared<PhysicsComponent>(
      *this, b2_kinematicBody, false, 0.f, 10.f, 1.f, 1.f));
  addGenericComponent(std::make_shared<InputBreakoutComponent>(*this, speed));
  addGenericComponent(std::make_shared<PerformHookOnCollideComponent>(
      *this, BreakoutBallTag, [&](Level&, const std::shared_ptr<GameObject>&) {
        Mix_PlayChannel(0,
                        ResourceManager::getInstance().getChunk(
                            "2DBreakout/SFX/PaddleBorderHit_SFX.mp3"),
                        0);
      }));
}
