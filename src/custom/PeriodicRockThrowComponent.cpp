#include "custom/PeriodicRockThrowComponent.hpp"
#include "base/Level.hpp"
#include "base/TinyMath.hpp"
#include "custom/Tag.hpp"
#include <SDL2/SDL_timer.h>

PeriodicRockThrowComponent::PeriodicRockThrowComponent(GameObject& gameObject,
                                                       float radius,
                                                       Uint32 cooldown)
    : mCooldownDelay(cooldown),
      mNextThrowTime(0),
      mRadius(radius),
      GenericComponent(gameObject) {}

void PeriodicRockThrowComponent::update(Level& level) {
  if (!SDL_TICKS_PASSED(SDL_GetTicks(), mNextThrowTime)) {
    // Tower fired too recently, still cooling down
    return;
  }
  // Tower ready to fire again
  // Get target
  const Vector2D<float> towerPos = {getGameObject().x(), getGameObject().y()};
  float minSquaredDist = mRadius * mRadius;
  std::shared_ptr<GameObject> closestEnemy = nullptr;
  for (const auto& gameobj : level.getGameObjects()) {
    const GameObject* candidateEnemy = gameobj.get();
    if (candidateEnemy->tag() == TdEnemyTag) {
      const Vector2D<float> enemyPos = {candidateEnemy->x(),
                                        candidateEnemy->y()};
      const float curSquaredDist = towerPos.squaredDistance(enemyPos);
      if (curSquaredDist < minSquaredDist) {
        minSquaredDist = curSquaredDist;
        closestEnemy = gameobj;
      }
    }
  }

  // Shoot at target
  if (closestEnemy == nullptr) {
    // No targets in range
    return;
  }
  std::cerr << "bang!" << std::endl;
  mNextThrowTime = SDL_GetTicks() + mCooldownDelay;
}
