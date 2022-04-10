#ifndef INPUT_GRAV_COMPONENT_HPP
#define INPUT_GRAV_COMPONENT_HPP

#include "base/ActionState.hpp"
#include "base/GameObject.hpp"
#include "base/GenericComponent.hpp"
#include "base/InputManager.hpp"
#include "base/PhysicsComponent.hpp"
#include "base/ResourceManager.hpp"
#include "base/PhysicsManager.hpp"
#include "graverunner/Tag.hpp"
#include "graverunner/Bullet.hpp"

/**
 * @brief Input component with gravity. Moves a game object when the
 * user presses the left, right, or up arrow keys on their keyboard.
 * Configurable step-size ie. speed.
 *
 * Move right means add horizontal speed, move left means subtract.
 * Jump speed is added, so is gravity.
 */
class InputGravComponent: public GenericComponent {
 public:

  InputGravComponent(GameObject & gameObject, float speed, float jump, float gravity):
  GenericComponent(gameObject),
  mSpeed(speed),
  mJump(jump),
  mGravity(gravity)
  {
  }

  virtual void update(Level & level) override
  {
    if (!PhysicsManager::getInstance().hasStarted() || curActionState == ActionState::DEAD)
      return;
    bool left = InputManager::getInstance().isKeyDown(SDLK_LEFT);
    bool right = InputManager::getInstance().isKeyDown(SDLK_RIGHT);
    bool jump = InputManager::getInstance().isKeyPressed(SDLK_UP);
    bool fire = InputManager::getInstance().isKeyPressed(SDLK_SPACE);
    bool down = InputManager::getInstance().isKeyDown(SDLK_DOWN);

    GameObject & gameObject = getGameObject();

    if (fire) {
      auto bullet = std::make_shared<Bullet>(
          level,
          gameObject.x() + (isFacingLeft ? 0.3 : 0.8) * (gameObject.w()) / 2,
          gameObject.y() + gameObject.h() / 3, gameObject.w() / 3,
          gameObject.h() / 3, isFacingLeft);
      level.addObject(bullet);
    }

    std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();
    pc->addFy(mGravity);

    if (left && !right) {
      pc->setVx(-mSpeed);
      isFacingLeft = true;
      if (curActionState == IDLE) {
        curActionState = WALK;
      }
    } else if (!left && right) {
      pc->setVx(mSpeed);
      isFacingLeft = false;
      if (curActionState == IDLE) {
        curActionState = WALK;
      }
    } else {
      pc->setVx(0.0f);
      if (pc->vy() == 0)
        curActionState = IDLE;
    }

    if (jump || down) {
      bool onGround = false;

      const float inset = gameObject.w() * PhysicsManager::GAME_TO_PHYSICS_SCALE;

      std::vector<std::shared_ptr<GameObject>> objects;
      if (PhysicsManager::getInstance().getCollisions(gameObject.x() + inset, gameObject.y() + gameObject.h(),
                                                      gameObject.w() - 2 * inset, 1.0f, objects)) {
        for (auto obj: objects) {
          if (obj->tag() == GraveRunnerNormalBlockTag) {
            onGround = true;
          }
        }
      }

      if (onGround && jump) {
        pc->setVy(-mJump);
        curActionState = JUMP;
        Mix_PlayChannel(
            0, ResourceManager::getInstance().getChunk("Graverunner/2DPlatformer_SFX/PaddleBorderHit_SFX.mp3"), 0);
      }
      else if (onGround && down && (left ^ right)) {
        curActionState = SLIDE;
        Mix_PlayChannel(
            0, ResourceManager::getInstance().getChunk("Graverunner/2DPlatformer_SFX/PaddleBorderHit_SFX.mp3"), 0);
      }
    }
  }

  void collision(Level & level, std::shared_ptr<GameObject> obj) override {
    if (obj->tag() == GraveRunnerZombieTag) {
      if (curActionState != ActionState::SLIDE) {
        curActionState = ActionState::DEAD;
        Mix_PlayChannel(
            1, ResourceManager::getInstance().getChunk("Graverunner/2DPlatformer_SFX/die_sound.mp3"), 0);
      }
      else
        level.removeObject(obj);
    }
  }

  inline ActionState getCurActionState() { return curActionState; }
  inline bool getIsFacingLeft() const { return isFacingLeft; }

 private:

  float mSpeed;
  float mJump;
  float mGravity;

  // Tracks the different poses for rendering
  ActionState curActionState{IDLE};
  // false means is facing right
  bool isFacingLeft{false};

};


#endif  // INPUT_GRAV_COMPONENT_HPP