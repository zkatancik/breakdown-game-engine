#include "custom/ArrowBarrageComponent.hpp"

#include <SDL2/SDL_timer.h>

#include "base/Level.hpp"
#include "base/TinyMath.hpp"
#include "custom/Arrow.hpp"
#include "custom/Tag.hpp"

ArrowBarrageComponent::ArrowBarrageComponent(
    GameObject& gameObject, float radius, float speed, Uint32 cooldown,
    const std::shared_ptr<TextureRenderComponent>& textureRenderComponent)
    : GenericComponent(gameObject),
      mRadius(radius),
      mSpeed(speed),
      mCooldownDelay(cooldown),
      mNextThrowTime(0),
      mTRenderComponent(textureRenderComponent) {
  mCounterComponent =
      std::make_shared<CyclicCounterComponent>(gameObject, 7, true);
  gameObject.addGenericComponent(mCounterComponent);
}

void ArrowBarrageComponent::update(Level& level) {
  if (!SDL_TICKS_PASSED(SDL_GetTicks(), mNextThrowTime)) {
    // Tower fired too recently, still cooling down
    mCounterComponent->setCounter(0);
    return;
  }
  // Tower ready to fire again
  // Get target
  const auto& gameObject = getGameObject();
  const Vector2D<float> towerPos = {gameObject.x(), gameObject.y()};
  float minSquaredDist = mRadius * mRadius;
  std::shared_ptr<GameObject> closestEnemyLeft = nullptr;
  std::shared_ptr<GameObject> closestEnemyRight = nullptr;
  for (const auto& gameobj : level.getGameObjects()) {
    const GameObject* candidateEnemy = gameobj.get();
    if (candidateEnemy->tag() == TdEnemyTag) {
      const Vector2D<float> enemyPos = {candidateEnemy->x(),
                                        candidateEnemy->y()};
      const float curSquaredDist = towerPos.squaredDistance(enemyPos);
      if (curSquaredDist < minSquaredDist && enemyPos.x < towerPos.x) {
        minSquaredDist = curSquaredDist;
        closestEnemyLeft = gameobj;
      }
      if (curSquaredDist < minSquaredDist && enemyPos.x > towerPos.x) {
        minSquaredDist = curSquaredDist;
        closestEnemyRight = gameobj;
      }
    }
  }

  // Shoot at target
  if (closestEnemyLeft == nullptr && closestEnemyRight == nullptr) {
    // No targets in range
    std::string path = "TD2D/Sprites/Towers/cpix_towers/arrow_tower_1.png";
    SDL_Texture* texture = ResourceManager::getInstance().getTexture(path);
    mTRenderComponent->setTexture(texture);
    mCounterComponent->setCounter(0);
    return;
  }
  Vector2D<float> closestEnemyPosLeft;
  Vector2D<float> closestEnemyPosRight;
  if (closestEnemyLeft != nullptr) {
    closestEnemyPosLeft = {closestEnemyLeft->x(), closestEnemyLeft->y()};
  }
  if (closestEnemyRight != nullptr) {
    closestEnemyPosRight = {closestEnemyRight->x(), closestEnemyRight->y()};
  }

  std::shared_ptr<Arrow> arrowLeft;
  std::shared_ptr<Arrow> arrowRight;
  if (closestEnemyLeft != nullptr) {
    const Vector2D<float> arrowVelocity =
        (Normalize(closestEnemyPosLeft - towerPos)) * mSpeed;
    arrowLeft = std::make_shared<Arrow>(
        level, gameObject.x() + 10, gameObject.y(), gameObject.w() / 2,
        gameObject.h() / 6, arrowVelocity.x, arrowVelocity.y, mRadius);
  }
  if (closestEnemyRight != nullptr) {
    const Vector2D<float> arrowVelocity2 =
        (Normalize(closestEnemyPosRight - towerPos)) * mSpeed;
    arrowRight = std::make_shared<Arrow>(
        level, gameObject.x() + 10, gameObject.y(), gameObject.w() / 2,
        gameObject.h() / 6, arrowVelocity2.x, arrowVelocity2.y, mRadius);
  }

  if (mCounterComponent->getCounter() == 6) {
    std::string path = "TD2D/Sprites/Towers/cpix_towers/arrow_tower_1.png";

    SDL_Texture* texture = ResourceManager::getInstance().getTexture(path);
    mTRenderComponent->setTexture(texture);
    if (closestEnemyLeft != nullptr) {
      level.addObject(arrowLeft);
    }
    if (closestEnemyRight != nullptr) {
      level.addObject(arrowRight);
    }

    mCounterComponent->setCounter(0);

    // Need to cool down before next time it fires
    mNextThrowTime = SDL_GetTicks() + mCooldownDelay;
  } else {
    std::string path = "TD2D/Sprites/Towers/cpix_towers/arrow_tower_";
    path += (std::to_string(mCounterComponent->getCounter() + 1) + ".png");

    SDL_Texture* texture = ResourceManager::getInstance().getTexture(path);
    mTRenderComponent->setTexture(texture);
  }
}
