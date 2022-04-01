#ifndef JACK_HPP
#define JACK_HPP

#include "SDL.h"
#include "base/ActionState.hpp"
#include "base/CyclicCounterComponent.hpp"
#include "base/GameObject.hpp"
#include "InputGravComponent.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/TinyMath.hpp"
#include "graverunner/Tag.hpp"
#include "base/PerformHookOnCollideComponent.hpp"
#include "base/RemoveOnCollideComponent.hpp"
#include "base/ResourceManager.hpp"

/**
 * @brief A class representing the hero / main character of our Platformer game.
 * Jack can move around and jump, as well as update and render himself.
 */
class Jack : public GameObject {
 public:
  /**
   * @brief Construct a new default Jack object.
   */
  explicit Jack(Level& level);

  /**
   * @brief Initialize this Jack object, sets the location on screen.
   *
   * @param tl_x top left x coordinate
   * @param tl_y top left y coordinate
   * @param w width of Jack
   * @param h height of Jack
   */
  void startUp(float tl_x, float tl_y, float w, float h);

  /**
   * @brief Cleans up this Jack object to be destroyed.
   */
  void shutDown();


  void update() override;

  bool isAlive() const { return !(input_grav_->getCurActionState() == ActionState::DEAD && counter_->getCounter() == 9); }

  inline unsigned int GetNumCollectedKeys() const { return numCollectedKeys; }

#ifdef _TEST
  inline const int getXStep() const { return xVelocity; }
  inline const int getGravityStep() const { return gravityVelocity; }
  inline const int getJumpStep() const { return jumpVelocity; }
#endif

 private:
  unsigned int numCollectedKeys{0};

 private:

  const int xVelocity = 500;

  const int mGravityForce = 50000;

  const int jumpVelocity = 1000;

  std::shared_ptr<TextureRenderComponent> renderer_;
  std::shared_ptr<CyclicCounterComponent> counter_;
  std::shared_ptr<InputGravComponent> input_grav_;
};
#endif  // JACK_HPP
