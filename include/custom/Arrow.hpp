#ifndef ARROW_HPP
#define ARROW_HPP

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
class Arrow : public GameObject {
 public:
  /**
   * @brief Construct a new Arrow object
   *
   * @param level level information
   * @param x x-pos
   * @param y y-pos
   * @param w width
   * @param h height
   * @param vx x-velocity
   * @param vy y-velocity
   */
  explicit Arrow(Level& level, float x, float y, float w, float h, float vx,
                 float vy, float radius);

  void update() override;
};

#endif