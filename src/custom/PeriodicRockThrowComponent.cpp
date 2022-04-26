#include "custom/PeriodicRockThrowComponent.hpp"

#include <SDL2/SDL_timer.h>

#include "base/Level.hpp"
#include "base/TinyMath.hpp"
#include "custom/Rock.hpp"
#include "custom/Tag.hpp"

PeriodicRockThrowComponent::PeriodicRockThrowComponent(
    GameObject& gameObject, float radius, float speed, Uint32 cooldown,
    RockThrowingPreference targetPref,
    const std::shared_ptr<TextureRenderComponent>& textureRenderComponent)
    : GenericComponent(gameObject),
      mRadius(radius),
      mSpeed(speed),
      mCooldownDelay(cooldown),
      mNextThrowTime(0),
      mTRenderComponent(textureRenderComponent),
      mTargetPref(targetPref) {
  mCounterComponent =
      std::make_shared<CyclicCounterComponent>(gameObject, 7, false);
  gameObject.addGenericComponent(mCounterComponent);
}

void PeriodicRockThrowComponent::update(Level& level) {
  if (!SDL_TICKS_PASSED(SDL_GetTicks(), mNextThrowTime)) {
    // Tower fired too recently, still cooling down
    mCounterComponent->setCounter(0);
    return;
  }
  // Tower ready to fire again
  // Get target

  int highTargetNum = 1000000;
  int lowTargetNum = -1;
  int lowHealthNum = -1;

  const auto& gameObject = getGameObject();
  const Vector2D<float> towerPos = {gameObject.x(), gameObject.y()};
  float minSquaredDist = mRadius * mRadius;
  std::shared_ptr<GameObject> targetedEnemy = nullptr;
  for (const auto& gameobj : level.getGameObjects()) {
    const GameObject* candidateEnemy = gameobj.get();
    if (candidateEnemy->tag() == TdEnemyTag) {
      const CustomEnemy* enemy =
          dynamic_cast<const CustomEnemy*>(candidateEnemy);
      const Vector2D<float> enemyPos = {candidateEnemy->x(),
                                        candidateEnemy->y()};
      const float curSquaredDist = towerPos.squaredDistance(enemyPos);
      if (curSquaredDist < minSquaredDist) {
        int targetNum = enemy->getCount();
        int healthNum = enemy->getHealth();
        if (mTargetPref == RockThrowingPreference::STRONG) {
          if (healthNum > lowHealthNum) {
            lowHealthNum = healthNum;
            targetedEnemy = gameobj;
          }
        } else if (mTargetPref == RockThrowingPreference::LAST) {
          if (targetNum > lowTargetNum) {
            lowTargetNum = targetNum;
            targetedEnemy = gameobj;
          }
        } else if (mTargetPref == RockThrowingPreference::CLOSE) {
          minSquaredDist = curSquaredDist;
          targetedEnemy = gameobj;
        } else {
          if (targetNum < highTargetNum) {
            highTargetNum = targetNum;
            targetedEnemy = gameobj;
          }
        }
      }
    }
  }

  // Shoot at target
  if (targetedEnemy == nullptr) {
    // No targets in range
    std::string path = "TD2D/Sprites/Towers/cpix_towers/stone_throw_1.png";
    SDL_Texture* texture = ResourceManager::getInstance().getTexture(path);
    mTRenderComponent->setTexture(texture);
    mCounterComponent->setCounter(0);
    return;
  }
  const Vector2D<float> targetedEnemyPos = {targetedEnemy->x(),
                                            targetedEnemy->y()};
  const Vector2D<float> rockVelocity =
      (Normalize(targetedEnemyPos - towerPos)) * mSpeed;
  auto rock = std::make_shared<Rock>(
      level, gameObject.x() + 0.3 * (gameObject.w()) / 2, gameObject.y(),
      gameObject.w() / 3, gameObject.h() / 3, rockVelocity.x, rockVelocity.y);

  if (mCounterComponent->getCounter() == 6) {
    std::string path = "TD2D/Sprites/Towers/cpix_towers/stone_throw_6.png";

    SDL_Texture* texture = ResourceManager::getInstance().getTexture(path);
    mTRenderComponent->setTexture(texture);

    level.addObject(rock);
    mCounterComponent->setCounter(0);

    // Need to cool down before next time it fires
    mNextThrowTime = SDL_GetTicks() + mCooldownDelay;
  } else {
    std::string path = "TD2D/Sprites/Towers/cpix_towers/stone_throw_";
    path += (std::to_string(mCounterComponent->getCounter() + 1) + ".png");

    SDL_Texture* texture = ResourceManager::getInstance().getTexture(path);
    mTRenderComponent->setTexture(texture);
  }
}
