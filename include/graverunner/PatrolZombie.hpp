#ifndef PATROL_ZOMBIE_HPP
#define PATROL_ZOMBIE_HPP

#include "base/PatrolComponent.hpp"
#include "graverunner/BaseEnemy.hpp"

/**
 * @brief A class representing the zombie enemy.
 * PatrolZombie can move around and jump, as well as update and render himself.
 */
class PatrolZombie : public BaseEnemy {
 public:
  /**
   * @brief Construct a new default PatrolZombie object.
   */
  explicit PatrolZombie(Level& level);

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

#ifdef _TEST
  inline const int getXStep() const { return xVelocity; }
#endif
 private:
  
  std::shared_ptr<PatrolComponent> mPatrol;
  
};
#endif
