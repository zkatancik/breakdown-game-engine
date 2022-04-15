#ifndef PERIODIC_ROCK_THROW_COMPONENT_HPP
#define PERIODIC_ROCK_THROW_COMPONENT_HPP

#include <SDL2/SDL_types.h>
#include "base/GenericComponent.hpp"

/**
 * @brief Component which launches a rock at the closest enemy. Has a
 * configurable cooldown delay (SDL ticks) between throws.
 */
class PeriodicRockThrowComponent : public GenericComponent {
 public:
  PeriodicRockThrowComponent(GameObject &gameObject, float radius,
                             Uint32 cooldown);

  void update(Level &level) override;

 private:
  Uint32 mCooldownDelay;
  Uint32 mNextThrowTime;
  float mRadius;
};

#endif