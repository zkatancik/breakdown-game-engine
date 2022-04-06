#ifndef ZOMBIE_MALE_HPP
#define ZOMBIE_MALE_HPP

#include <vector>
#include "base/GameObject.hpp"
#include "base/Level.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/CyclicCounterComponent.hpp"
#include "graverunner/Jack.hpp"

/**
 * @brief A class representing the enemy.
 * BaseEnemy can update and render itself.
 */
class BaseEnemy : public GameObject {
 public:
  /**
   * @brief Construct a new default BaseEnemy object.
   */
  explicit BaseEnemy(Level& level);

  /**
   * @brief Initialize this BaseEnemy object, sets the location on screen.
   *
   * @param tl_x top left x coordinate
   * @param tl_y top left y coordinate
   * @param w width of the zombie
   * @param h height of the zombie
   * @param checkpoints checkpoints where this enemy patrols
   * @param j pointer to Jack for interactions
   */
  explicit BaseEnemy(Level& level, float tl_x, float tl_y, float w, float h,
                     std::vector<std::pair<float, float>>& checkpoints,
                     std::shared_ptr<Jack> j);

  /**
   * @brief Destroy this Base Enemy object
   */
  ~BaseEnemy();

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
