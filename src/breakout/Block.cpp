#include "breakout/Block.hpp"

Block::Block(Level &level, float x, float y, int color, BlockData bd, int h) :
            GameObject(level, x, y, 64, 32, BlockTag),
            blockData(bd), health(h) {
  auto texture = ResourceManager::getInstance().getTexture(getResourcePath("2DBreakout/Graphics") / colorMap[color]);
  renderer_ = std::make_shared<TextureRenderComponent>(*this);
  renderer_->setTexture(texture);
  setRenderComponent(renderer_);
  setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, b2_staticBody, false, 0.0f, 10.0));
  // Reduce health when colliding with ball
//  auto collisionWithBallHook = [&](Level &level, std::shared_ptr<GameObject> obj) {
//    if (obj->tag() == BallTag) {
//      if (health > 0) {
//        health--;
//        //Texture updates
//        if (blockData.block_Type == BlockType::HardBlock)
//        {
//          if (health == 2) {
//            texture = ResourceManager::getInstance().getTexture(getResourcePath("2DBreakout/Graphics") / "element_grey_health_2_rectangle.png");
//          } else if (health == 1) {
//            texture = ResourceManager::getInstance().getTexture(getResourcePath("2DBreakout/Graphics") / "element_grey_health_1_rectangle.png");
//          }
//          renderer_->setTexture(texture);
//        }
//      }
//      level.removeObject(shared_from_this());
//    }
//  };
//  addGenericComponent(std::make_shared<PerformHookOnCollideComponent>(*this, BallTag, collisionWithBallHook));
}