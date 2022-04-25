#ifndef MAGIC_BALL_HPP
#define MAGIC_BALL_HPP

#include "base/ConstantVelocityComponent.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"
#include "base/RemoveOnCollideComponent.hpp"
#include "base/ResourceManager.hpp"
#include "base/TextureRenderComponent.hpp"
#include "custom/Tag.hpp"

/**
 * @brief A rock that towers can launch.
 */
class MagicBall : public GameObject {
 public:
  /**
   * @brief Construct a new MagicBall object
   *
   * @param level level information
   * @param x x-pos
   * @param y y-pos
   * @param w width
   * @param h height
   * @param vx x-velocity
   * @param vy y-velocity
   */
  explicit MagicBall(Level& level, float x, float y, float w, float h, float vx,
                     float vy, float radius);

  void update() override;
};

#endif