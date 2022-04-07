#include "graverunner/Jack.hpp"
#include "graverunner/Tag.hpp"
#include <box2d/b2_body.h>

Jack::Jack(Level& level, float tl_x, float tl_y, float w, float h) : GameObject(level, tl_x, tl_y, w, h, JackTag) {
  numCollectedKeys = 0;
  renderer_ = std::make_shared<TextureRenderComponent>(*this);
  setRenderComponent(renderer_);
  counter_ = std::make_shared<CyclicCounterComponent>(*this, 10, true);
  addGenericComponent(counter_);
  input_grav_ = std::make_shared<InputGravComponent>(*this, xVelocity, jumpVelocity, mGravityForce);
  addGenericComponent(input_grav_);
  addGenericComponent(std::make_shared<PerformHookOnCollideComponent>(
      *this, KeyTag, [&](Level &level, std::shared_ptr<GameObject> obj) {
        numCollectedKeys++;
        Mix_PlayChannel(
            0, ResourceManager::getInstance().getChunk("Graverunner/2DPlatformer_SFX/BrickHit_SFX.mp3"), 0);
      }));
  addGenericComponent(std::make_shared<RemoveOnCollideComponent>(*this, KeyTag));
//  addGenericComponent(std::make_shared<PerformHookOnCollideComponent>(
//      *this, ZombieTag, [&](Level &level, std::shared_ptr<GameObject> obj) {
//
//      }));
  addGenericComponent(std::make_shared<PerformHookOnCollideComponent>(
      *this, ExitTag, [&](Level &level, std::shared_ptr<GameObject> obj) {}));
  addGenericComponent(
      std::make_shared<RemoveOnCollideComponent>(*this, ExitTag));
  setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, b2BodyType::b2_dynamicBody, false));
}

void Jack::update() {
  std::string path = "Graverunner/jack/";
  switch (input_grav_->getCurActionState()) {
    case IDLE:
      path += "Idle";
      break;
    case WALK:
      path += "Walk";
      break;
    case JUMP:
      path += "Jump";
      break;
    case SLIDE:
      path += "slide_scaled/Slide";
      break;
    case DEAD:
      path += "Dead";
    default:
      break;
  }
  path += (std::to_string(counter_->getCounter() + 1) + ".png");  

  SDL_Texture *texture = ResourceManager::getInstance().getTexture(path);
  renderer_->setTexture(texture);
  renderer_->setFlip(input_grav_->getIsFacingLeft());
  GameObject::update();
}
