#ifndef INPUT_BREAKOUT_COMPONENT_HPP
#define INPUT_BREAKOUT_COMPONENT_HPP

#include "base/ActionState.hpp"
#include "base/GameObject.hpp"
#include "base/GenericComponent.hpp"
#include "base/InputManager.hpp"
#include "base/PhysicsComponent.hpp"
#include "base/ResourceManager.hpp"
#include "base/PhysicsManager.hpp"
#include "breakout/Tag.hpp"

/**
 * @brief Input component for Paddle in the Breakout Game.
 */
class InputBreakoutComponent: public GenericComponent {
 public:

  InputBreakoutComponent(GameObject & gameObject, float speed):
  GenericComponent(gameObject),
  mSpeed(speed)
  {
  }

  void update(Level & level) override
  {
    if (!PhysicsManager::getInstance().hasStarted())
      return;
    bool left = InputManager::getInstance().isKeyDown(SDLK_LEFT);
    bool right = InputManager::getInstance().isKeyDown(SDLK_RIGHT);

    GameObject & gameObject = getGameObject();

    std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();

    if (left && !right) {
      pc->setVx(-mSpeed);
    } else if (!left && right) {
      pc->setVx(mSpeed);
    } else {
      pc->setVx(0.0f);
    }
  }

 private:
  float mSpeed;
};


#endif