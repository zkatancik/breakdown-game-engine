#ifndef ARROW_BARRAGE_COMPONENT_HPP
#define ARROW_BARRAGE_COMPONENT_HPP

#include <SDL2/SDL_types.h>

#include "base/CyclicCounterComponent.hpp"
#include "base/GameObject.hpp"
#include "base/GenericComponent.hpp"
#include "base/TextureRenderComponent.hpp"
#include "custom/ArrowTower.hpp"
#include "custom/CustomEnemy.hpp"

/**
 * @brief Component which launches a rock at the closest enemy. Has a
 * configurable cooldown delay (SDL ticks) between throws.
 */
class ArrowBarrageComponent : public GenericComponent {
 public:
  /**
   * @brief Construct a new Periodic Rock Throw Component object
   *
   * @param gameObject the object this component belongs to
   * @param radius the range (around the game object) that this component
   * searches for targets
   * @param speed the speed of the rocks thrown
   * @param cooldown the minimum delay (SDL ticks) between firings
   */
  ArrowBarrageComponent(
      GameObject &gameObject, float radius, float speed, Uint32 cooldown,
      ArrowTargetingPreference targetPref,
      const std::shared_ptr<TextureRenderComponent> &textureRenderComponent);

  /**
   * @brief Updates this component, meaning checks for enemies within radius and
   * fires at the closest one. No-op if time since last rock thrown > cooldown.
   *
   * @param level
   */
  void update(Level &level) override;

 private:
  const float mRadius;
  const float mSpeed;
  const Uint32 mCooldownDelay;
  Uint32 mNextThrowTime;
  std::shared_ptr<CyclicCounterComponent> mCounterComponent;
  std::shared_ptr<TextureRenderComponent> mTRenderComponent;
  ArrowTargetingPreference mTargetPref{ArrowTargetingPreference::CLOSE};
};

#endif