#ifndef PERIODIC_ROCK_THROW_COMPONENT_HPP
#define PERIODIC_ROCK_THROW_COMPONENT_HPP

#include <SDL2/SDL_types.h>

#include "base/GameObject.hpp"
#include "base/GenericComponent.hpp"

/**
 * @brief Component which launches a rock at the closest enemy. Has a
 * configurable cooldown delay (SDL ticks) between throws.
 */
class PeriodicRockThrowComponent : public GenericComponent {
 public:
  PeriodicRockThrowComponent(GameObject &gameObject, float radius, float speed,
                             Uint32 cooldown);

  void update(Level &level) override;

 private:
  const Uint32 mCooldownDelay;
  Uint32 mNextThrowTime;
  const float mRadius;
  const float mSpeed;
};

#endif