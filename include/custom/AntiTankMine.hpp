#ifndef ANTI_TANK_MINE_CUSTOM_HPP
#define ANTI_TANK_MINE_CUSTOM_HPP

#include <SDL2/SDL_types.h>

#include <memory>

#include "base/GameObject.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/TinyMath.hpp"

/**
 * @brief A type of placable that explodes once any enemy is in range. The mine is destroyed in the explosion as well.
 */
class AntiTankMine : public GameObject {
 public:
  /**
   * @brief Construct a new Anti-tank mine.
   *
   * @param level Level information
   * @param x the location of the Block to renders' x screen position in pixels
   * @param y the location of the Block to render's y screen position in pixels
   * @param bs block size
   */
  AntiTankMine(Level &level, float x, float y, Vector2D<int> bs);

 private:
  std::shared_ptr<TextureRenderComponent> renderer_;
  bool mHasExploded{false};
};

#endif