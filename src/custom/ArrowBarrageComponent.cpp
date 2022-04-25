#include "custom/ArrowBarrageComponent.hpp"

#include <SDL2/SDL_timer.h>

#include "base/Level.hpp"
#include "base/TinyMath.hpp"
#include "custom/Arrow.hpp"
#include "custom/Tag.hpp"

ArrowBarrageComponent::ArrowBarrageComponent(
    GameObject& gameObject, float radius, float speed, Uint32 cooldown,
    ArrowTargetingPreference targetPref,
    const std::shared_ptr<TextureRenderComponent>& textureRenderComponent)
    : GenericComponent(gameObject),
      mRadius(radius),
      mSpeed(speed),
      mCooldownDelay(cooldown),
      mNextThrowTime(0),
      mTRenderComponent(textureRenderComponent),
      mTargetPref(targetPref) {
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
  int leftHighTargetNum = 1000000;
  int leftLowTargetNum = -1;
  int rightHighTargetNum = 1000000;
  int rightLowTargetNum = -1;
  int leftLowHealthNum = -1;
  int rightLowHealthNum = -1;

  const auto& gameObject = getGameObject();
  const Vector2D<float> towerPos = {gameObject.x(), gameObject.y()};
  float minSquaredDist = mRadius * mRadius;
  std::shared_ptr<GameObject> targetedEnemyLeft = nullptr;
  std::shared_ptr<GameObject> targetedEnemyRight = nullptr;
  for (const auto& gameobj : level.getGameObjects()) {
    const GameObject* candidateEnemy = gameobj.get();
    if (candidateEnemy->tag() == TdEnemyTag) {
      const CustomEnemy* enemy =
          dynamic_cast<const CustomEnemy*>(candidateEnemy);

      const Vector2D<float> enemyPos = {candidateEnemy->x(),
                                        candidateEnemy->y()};
      const float curSquaredDist = towerPos.squaredDistance(enemyPos);
      if (curSquaredDist < minSquaredDist && enemyPos.x < towerPos.x) {
        int leftTargetNum = enemy->getCount();
        int leftHealthNum = enemy->getHealth();
        if (mTargetPref == ArrowTargetingPreference::STRONG) {
          if (leftHealthNum > leftLowHealthNum) {
            leftLowHealthNum = leftHealthNum;
            targetedEnemyLeft = gameobj;
          }
        } else if (mTargetPref == ArrowTargetingPreference::LAST) {
          if (leftTargetNum > leftLowTargetNum) {
            leftLowTargetNum = leftTargetNum;
            targetedEnemyLeft = gameobj;
          }
        } else if (mTargetPref == ArrowTargetingPreference::CLOSE) {
          minSquaredDist = curSquaredDist;
          targetedEnemyLeft = gameobj;
        } else {
          if (leftTargetNum < leftHighTargetNum) {
            leftHighTargetNum = leftTargetNum;
            targetedEnemyLeft = gameobj;
          }
        }
      }
      if (curSquaredDist < minSquaredDist && enemyPos.x > towerPos.x) {
        int rightTargetNum = enemy->getCount();
        int rightHealthNum = enemy->getHealth();
        if (mTargetPref == ArrowTargetingPreference::STRONG) {
          if (rightHealthNum > rightLowHealthNum) {
            rightLowHealthNum = rightHealthNum;
            targetedEnemyRight = gameobj;
          }
        } else if (mTargetPref == ArrowTargetingPreference::LAST) {
          if (rightTargetNum > rightLowTargetNum) {
            rightLowTargetNum = rightTargetNum;
            targetedEnemyRight = gameobj;
          }
        } else if (mTargetPref == ArrowTargetingPreference::CLOSE) {
          minSquaredDist = curSquaredDist;
          targetedEnemyRight = gameobj;
        } else {
          if (rightTargetNum < rightHighTargetNum) {
            rightHighTargetNum = rightTargetNum;
            targetedEnemyRight = gameobj;
          }
        }
      }
    }
  }

  // Shoot at target
  if (targetedEnemyLeft == nullptr && targetedEnemyRight == nullptr) {
    // No targets in range
    std::string path = "TD2D/Sprites/Towers/cpix_towers/arrow_tower_1.png";
    SDL_Texture* texture = ResourceManager::getInstance().getTexture(path);
    mTRenderComponent->setTexture(texture);
    mCounterComponent->setCounter(0);
    return;
  }
  Vector2D<float> targetedEnemyPosLeft;
  Vector2D<float> targetedEnemyPosRight;
  if (targetedEnemyLeft != nullptr) {
    targetedEnemyPosLeft = {targetedEnemyLeft->x(), targetedEnemyLeft->y()};
  }
  if (targetedEnemyRight != nullptr) {
    targetedEnemyPosRight = {targetedEnemyRight->x(), targetedEnemyRight->y()};
  }

  std::shared_ptr<Arrow> arrowLeft;
  std::shared_ptr<Arrow> arrowRight;
  if (targetedEnemyLeft != nullptr) {
    const Vector2D<float> arrowVelocityLeft =
        (Normalize(targetedEnemyPosLeft - towerPos)) * mSpeed;
    arrowLeft = std::make_shared<Arrow>(
        level, gameObject.x() + 10, gameObject.y(), gameObject.w() / 2,
        gameObject.h() / 6, arrowVelocityLeft.x, arrowVelocityLeft.y, mRadius);
  }
  if (targetedEnemyRight != nullptr) {
    const Vector2D<float> arrowVelocityRight =
        (Normalize(targetedEnemyPosRight - towerPos)) * mSpeed;
    arrowRight = std::make_shared<Arrow>(
        level, gameObject.x() + 10, gameObject.y(), gameObject.w() / 2,
        gameObject.h() / 6, arrowVelocityRight.x, arrowVelocityRight.y,
        mRadius);
  }

  if (mCounterComponent->getCounter() == 6) {
    std::string path = "TD2D/Sprites/Towers/cpix_towers/arrow_tower_1.png";

    SDL_Texture* texture = ResourceManager::getInstance().getTexture(path);
    mTRenderComponent->setTexture(texture);
    if (targetedEnemyLeft != nullptr) {
      level.addObject(arrowLeft);
    }
    if (targetedEnemyRight != nullptr) {
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
