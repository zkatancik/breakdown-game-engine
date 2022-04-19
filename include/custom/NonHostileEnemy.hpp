#ifndef PATROL_ZOMBIE_HPP
#define PATROL_ZOMBIE_HPP

#include "base/MoveTowardsComponent.hpp"
#include "base/PatrolComponent.hpp"
#include "base/RandomWalkComponent.hpp"
#include "custom/CustomEnemy.hpp"

/**
 * @brief A class representing a non hostile enemy, capable of moving along a
 * path (follows checkpoints).
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
  explicit NonHostileEnemy(
      Level& level, float tl_x, float tl_y, float w, float h,
      TdLevelItem enemyItem, Vector2D<int> targetPosition,
      const std::vector<std::vector<TdBlockData>>& levelGrid,
      std::vector<Vector2D<int>> possiblePath,
      const std::function<void(void)>& callbackAtDeath);

#ifdef _TEST
  inline const int getXStep() const { return xVelocity; }
#endif

 private:
  std::shared_ptr<RandomWalkComponent> mRandomWalk;
  std::shared_ptr<MoveTowardsComponent> mMoveTowards;
  std::shared_ptr<PatrolComponent> mPatrol;
};
#endif
