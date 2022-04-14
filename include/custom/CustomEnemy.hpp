#ifndef ZOMBIE_MALE_HPP
#define ZOMBIE_MALE_HPP

#include "SDL.h"
#include "base/ActionState.hpp"
#include "base/CyclicCounterComponent.hpp"
#include "base/GameObject.hpp"
#include "base/PatrolComponent.hpp"
#include "base/FollowComponent.hpp"
#include "base/RemoveOnCollideComponent.hpp"
#include "base/TextureRenderComponent.hpp"
#include "custom/Tag.hpp"
#include "custom/LevelData.hpp"
#include "base/ResourceManager.hpp"

/**
 * @brief A class representing the enemy.
 * Base CustomEnemy can update and render itself.
 */
class CustomEnemy : public GameObject {
 public:

  /**
   * @brief Initialize this CustomEnemy object, sets the location on screen.
   *
   * @param tl_x top left x coordinate
   * @param tl_y top left y coordinate
   * @param w width of the zombie
   * @param h height of the zombie
   * @param checkpoints checkpoints where this enemy patrols
   */
  explicit CustomEnemy(Level& level, float tl_x, float tl_y, float w, float h,
                     std::string spritePath, TdLevelItem enemyItem);

  /**
   * @brief Destroy this Base CustomEnemy object
   */
  ~CustomEnemy();

  void update() override;

  bool checkDirection();

#ifdef _TEST
  inline const int getXStep() const { return xVelocity; }
#endif

  const int xVelocity = 100;

  TdLevelItem enemyItem_{TdLevelItem::NONE};

  std::string spritePath_;

  std::shared_ptr<TextureRenderComponent> renderer_;
  std::shared_ptr<CyclicCounterComponent> counter_;
};
#endif