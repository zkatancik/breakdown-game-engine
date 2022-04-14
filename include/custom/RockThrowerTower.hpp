#ifndef ROCK_THROWER_TOWER_HPP
#define ROCK_THROWER_TOWER_HPP

#include "base/GameObject.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/TinyMath.hpp"

class RockThrowerTower : public GameObject {
 public:
  /**
   * @brief Construct a new Rock Thrower Tower object
   *
   * @param level Level information
   * @param x the location of the Block to renders' x screen position in pixels
   * @param y the location of the Block to render's y screen position in pixels
   * @param bs block size
   */
  RockThrowerTower(Level &level, float x, float y, Vector2D<int> bs);

 private:
  std::shared_ptr<TextureRenderComponent> renderer_;
};

#endif
