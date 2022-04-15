#include "custom/PeriodicRockThrowComponent.hpp"

#include <SDL2/SDL_timer.h>

#include "base/Level.hpp"
#include "base/TinyMath.hpp"
#include "custom/Rock.hpp"
#include "custom/Tag.hpp"

PeriodicRockThrowComponent::PeriodicRockThrowComponent(GameObject& gameObject,
                                                       float radius,
                                                       float speed,
                                                       Uint32 cooldown)
    : mRadius(radius),
      mSpeed(speed),
      mCooldownDelay(cooldown),
      mNextThrowTime(0),
      GenericComponent(gameObject) {}

void PeriodicRockThrowComponent::update(Level& level) {
  if (!SDL_TICKS_PASSED(SDL_GetTicks(), mNextThrowTime)) {
    // Tower fired too recently, still cooling down
    return;
  }
  // Tower ready to fire again
  // Get target
  const auto& gameObject = getGameObject();
  const Vector2D<float> towerPos = {gameObject.x(), gameObject.y()};
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
  const Vector2D<float> closestEnemyPos = {closestEnemy.get()->x(),
                                           closestEnemy.get()->y()};
  const Vector2D<float> rockVelocity =
      (Normalize(closestEnemyPos - towerPos)) * mSpeed;
  auto rock = std::make_shared<Rock>(
      level, gameObject.x() + 0.3 * (gameObject.w()) / 2,
      gameObject.y() + gameObject.h() / 3, gameObject.w() / 3,
      gameObject.h() / 3, rockVelocity.x, rockVelocity.y);
  level.addObject(rock);

  // Need to cool down before next time it fires
  mNextThrowTime = SDL_GetTicks() + mCooldownDelay;
}
