#include "graverunner/Jack.hpp"


Jack::Jack(Level &level) : GameObject(level) {
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
            0, ResourceManager::getInstance().getChunk("BrickHit_SFX.mp3"), 0);
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
}

void Jack::startUp(float tl_x, float tl_y, float w, float h) {
  numCollectedKeys = 0;

  GameObject::startUp(tl_x, tl_y, w, h, JackTag);
  setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::DYNAMIC_SOLID));
}

void Jack::shutDown() {}

void Jack::update() {
  std::string path = "jack/";
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
