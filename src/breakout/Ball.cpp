#include <base/RemoveOnCollideComponent.hpp>
#include "breakout/Ball.hpp"
#include "box2d/box2d.h"

Ball::Ball(Level& level, float x, float y, float dx, float dy) : GameObject(level, x, y, 30, 30, BallTag) {
  renderer_ = std::make_shared<TextureRenderComponent>(*this);
  setRenderComponent(renderer_);
  setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, b2_dynamicBody, false, 0.0f, 1.0, 1.0));
  physicsComponent()->setVx(dx);
  physicsComponent()->setVy(dy);
  auto texture = ResourceManager::getInstance().getTexture("2DBreakout/Graphics/ballGrey.png");
  renderer_->setTexture(texture);
//  auto collisionWithBlockHook = [&](Level &level, std::shared_ptr<GameObject> obj) {
//    if (health > 0) {
//      health--;
//      //Texture updates
//      if (blockData.block_Type == BlockType::HardBlock)
//      {
//        if (health == 2) {
//          texture = ResourceManager::getInstance().getTexture(getResourcePath("2DBreakout/Graphics") / "element_grey_health_2_rectangle.png");
//        } else if (health == 1) {
//          texture = ResourceManager::getInstance().getTexture(getResourcePath("2DBreakout/Graphics") / "element_grey_health_1_rectangle.png");
//        }
//        renderer_->setTexture(texture);
//      }
//    }
//  };

}

void Ball::stop() { physicsComponent()->setVx(0); physicsComponent()->setVy(0);}
