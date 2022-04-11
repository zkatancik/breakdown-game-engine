#include "breakout/Block.hpp"

BreakoutBlock::BreakoutBlock(Level &level, float x, float y, BreakoutBlockData bd, int h) :
            GameObject(level, x, y, 64, 32, BreakoutBlockTag),
            blockData(bd) {
  //auto texture = ResourceManager::getInstance().getTexture(
  //    (filesystem::path("2DBreakout/Graphics") / filesystem::path(colorMap[color])).u8string());

  auto texture = getBlockTexture(blockData.blockNumber);

  renderer_ = std::make_shared<TextureRenderComponent>(*this);
  renderer_->setTexture(texture);
  setRenderComponent(renderer_);
  setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, b2_staticBody, false, 0.0f, 10.0));
  // Health component. Only gets added if it's not a wall.
  healthComponent_ = std::make_shared<HealthComponent>(*this, h);
  if (blockData.block_Type != Wall) {
    healthComponent_->addHealthModifier(BreakoutBallTag, -1);

  }
  addGenericComponent(healthComponent_);
  // Play audio on collision
  addGenericComponent(
      std::make_shared<PerformHookOnCollideComponent>(*this, BreakoutBallTag, [&] (Level&, const std::shared_ptr<GameObject>&) {
        switch(blockData.block_Type) {
          case PlainBlock:
            Mix_PlayChannel(1, ResourceManager::getInstance().getChunk("2DBreakout/SFX/BrickHit_SFX.mp3"), 0);
            break;
          case Wall:
            Mix_PlayChannel(1, ResourceManager::getInstance().getChunk("2DBreakout/SFX/WallBrickHit_SFX.wav"), 0);
            break;
          case HardBlock:
            Mix_PlayChannel(1, ResourceManager::getInstance().getChunk("2DBreakout/SFX/BrickCrack_SFX.wav"), 0);
            break;
          case NoBlock:
            break;
        }}));
  // Update texture of Hard block based on its health
  addGenericComponent(
      std::make_shared<PerformHookOnCollideComponent>(*this, BreakoutBallTag, [&] (Level&, const std::shared_ptr<GameObject>&) {
        if (blockData.block_Type == HardBlock) {
          switch (healthComponent_->getHealth()) {
            case 2:
              renderer_->setTexture(ResourceManager::getInstance().getTexture(
                  "2DBreakout/Graphics/element_grey_health_2_rectangle.png"
                  ));
              break;
            case 1:
              renderer_->setTexture(
                  ResourceManager::getInstance().getTexture(
                      "2DBreakout/Graphics/element_grey_health_1_rectangle.png"
                  ));
              break;
            default:
              break;
          }
        }

      }));
}