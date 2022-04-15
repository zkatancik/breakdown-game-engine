#ifndef BULLET_HPP
#define BULLET_HPP

#include "base/ConstantVelocityComponent.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"
#include "base/RemoveOnCollideComponent.hpp"
#include "base/ResourceManager.hpp"
#include "base/TextureRenderComponent.hpp"
#include "custom/Tag.hpp"

/**
 * @brief A bullet that towers can launch.
 */
class Bullet : public GameObject {
 public:
  /**
   * @brief Construct a new Bullet object
   *
   * @param level level information
   * @param x x-pos
   * @param y y-pos
   * @param w width
   * @param h height
   * @param vx x-velocity
   * @param vy y-velocity
   */
  explicit Bullet(Level& level, float x, float y, float w, float h, float vx,
                  float vy);

  void update() override;
};

#endif