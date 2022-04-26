#ifndef ARROW_TOWER_HPP
#define ARROW_TOWER_HPP

#include <SDL2/SDL_types.h>

#include <memory>

#include "base/GameObject.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/TinyMath.hpp"
#include "custom/MagicBlastComponent.hpp"

/**
 * @brief Enum to select how a tower targets enemies
 *
 */
enum class ArrowTargetingPreference { FIRST, LAST, CLOSE, STRONG };

/**
 * @brief A Tower which launches rocks at nearby enemies within a radius and
 * with cooldown between firings.
 */
class ArrowTower : public GameObject {
 public:
  /**
   * @brief Construct a new Rock Thrower Tower object
   *
   * @param level Level information
   * @param x the location of the Block to renders' x screen position in
   * pixels
   * @param y the location of the Block to render's y screen position in
   * pixels
   * @param bs block size
   */
  ArrowTower(Level& level, float x, float y, Vector2D<int> bs);

  /**
   * @brief Get a short description for this tower.
   *
   * @return const std::string& the description
   */
  inline const std::string& getDescription() const { return description; }

  /**
   * @brief Get the current targeting preference
   */
  inline ArrowTargetingPreference getTargetPref() const { return targetPref; }

  /**
   * @brief Set the new targeting preference.
   *
   * @param newPref new value
   */
  inline void setTargetPref(ArrowTargetingPreference newPref) {
    targetPref = newPref;
  }

 private:
  std::shared_ptr<TextureRenderComponent> renderer_;
  const float RADIUS{300.0};
  const float SPEED{300.0};
  const Uint32 COOLDOWN{400};
  ArrowTargetingPreference targetPref{ArrowTargetingPreference::FIRST};
  const std::string description = "Arrow Tower";
};

#endif
