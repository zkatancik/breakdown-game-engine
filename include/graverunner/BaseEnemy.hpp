#ifndef ZOMBIE_MALE_HPP
#define ZOMBIE_MALE_HPP

#include "SDL.h"
#include "base/ActionState.hpp"
#include "base/CyclicCounterComponent.hpp"
#include "base/GameObject.hpp"
#include "InputGravComponent.hpp"
#include "base/PatrolComponent.hpp"
#include "base/FollowComponent.hpp"
#include "base/RemoveOnCollideComponent.hpp"
#include "base/TextureRenderComponent.hpp"
#include "graverunner/Tag.hpp"
#include "base/ResourceManager.hpp"

/**
 * @brief A class representing the enemy.
 * BaseEnemy can update and render himself.
 */
class BaseEnemy : public GameObject {
 public:
  /**
   * @brief Construct a new default BaseEnemy object.
   */
  explicit BaseEnemy(Level& level);

  /**
   * @brief Initialize this ZombieMale object, sets the location on screen.
   *
   * @param tl_x top left x coordinate
   * @param tl_y top left y coordinate
   * @param w width of the zombie
   * @param h height of the zombie
   * @param checkpoints checkpoints where the zombie patrols
   */
  void startUp(float tl_x, float tl_y, float w, float h,
               std::vector<std::pair<float, float>>& checkpoints, std::shared_ptr<Jack> j);
 
  /**
   * @brief Removes the genericComponents of the ZombieMale
   */
  void shutDown();

  void update() override;

  bool checkDirection();

#ifdef _TEST
  inline const int getXStep() const { return xVelocity; }
#endif

  const int xVelocity = 100;

  std::shared_ptr<TextureRenderComponent> renderer_;
  std::shared_ptr<CyclicCounterComponent> counter_;
};
#endif
