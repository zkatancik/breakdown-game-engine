#ifndef PATROL_ZOMBIE_HPP
#define PATROL_ZOMBIE_HPP

#include "base/MoveTowardsComponent.hpp"
#include "custom/CustomEnemy.hpp"

/**
 * @brief A class representing the zombie enemy.
 * NonHostileEnemy can move around and jump, as well as update and render himself.
 */
class NonHostileEnemy : public CustomEnemy {
 public:
  /**
   * @brief Construct a new default NonHostileEnemy object.
   * @param level Level data
   * @param tl_x top left x coordinate
   * @param tl_y top left y coordinate
   * @param w width of the zombie
   * @param h height of the zombie
   * @param checkpoints checkpoints where the zombie patrols
   */
  explicit NonHostileEnemy(Level& level, float tl_x, float tl_y, float w, float h,
               std::string spritePath, TdLevelItem enemyItem,
               Vector2D<int> targetPosition);

#ifdef _TEST
  inline const int getXStep() const { return xVelocity; }
#endif

 private:
  std::shared_ptr<MoveTowardsComponent> mMoveTowards;
};
#endif
