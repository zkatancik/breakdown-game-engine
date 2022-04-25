#include "custom/MagicBlastComponent.hpp"

#include <SDL2/SDL_timer.h>

#include "base/Level.hpp"
#include "base/TinyMath.hpp"
#include "custom/Tag.hpp"

MagicBlastComponent::MagicBlastComponent(
    GameObject& gameObject, float radius, float speed, Uint32 cooldown,
    Uint32 blasts,
    const std::shared_ptr<TextureRenderComponent>& textureRenderComponent)
    : GenericComponent(gameObject),
      mRadius(radius),
      mSpeed(speed),
      mCooldownDelay(cooldown),
      mBlasts(blasts),
      mNextThrowTime(0),
      mTRenderComponent(textureRenderComponent) {
  mCounterComponent =
      std::make_shared<CyclicCounterComponent>(gameObject, 16, false);
  gameObject.addGenericComponent(mCounterComponent);
}

void MagicBlastComponent::update(Level& level) {
  if (!SDL_TICKS_PASSED(SDL_GetTicks(), mNextThrowTime)) {
    // Tower fired too recently, still cooling down
    // mCounterComponent->setCounter(0);
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
    std::string path = "TD2D/Sprites/Towers/cpix_towers/aoe_tower_16.png";
    SDL_Texture* texture = ResourceManager::getInstance().getTexture(path);
    mTRenderComponent->setTexture(texture);
    mCounterComponent->setCounter(0);
    return;
  }

  std::vector<std::shared_ptr<MagicBall>> blasts;

  std::vector<std::vector<float>> level1dirs;
  std::vector<float> up{0, 1};
  std::vector<float> down{0, -1};
  std::vector<float> right{1, 0};
  std::vector<float> left{-1, 0};
  level1dirs.push_back(up);
  level1dirs.push_back(down);
  level1dirs.push_back(right);
  level1dirs.push_back(left);

  std::vector<std::vector<float>> level3dirs;
  std::vector<float> down_left{-1, -1};
  std::vector<float> up_left{-1, 1};
  std::vector<float> down_right{1, -1};
  std::vector<float> up_right{1, 1};
  level3dirs.push_back(down_left);
  level3dirs.push_back(up_left);
  level3dirs.push_back(down_right);
  level3dirs.push_back(up_right);

  for (int i = 0; i < mBlasts; i++) {
    Vector2D<int> magicBallVelocity = Vector2D(1, 1);
    magicBallVelocity.x = mSpeed * level1dirs[i][0];
    magicBallVelocity.y = mSpeed * level1dirs[i][1];
    auto magicBall = std::make_shared<MagicBall>(
        level, gameObject.x() + 20 + level1dirs[i][0],
        gameObject.y() + 20 + level1dirs[i][1], gameObject.w() / 3,
        gameObject.h() / 3, magicBallVelocity.x, magicBallVelocity.y, mRadius);
    blasts.push_back(magicBall);
  }

  if (mCounterComponent->getCounter() == 15) {
    std::string path = "TD2D/Sprites/Towers/cpix_towers/aoe_tower_";
    path += (std::to_string(mCounterComponent->getCounter() + 1) + ".png");

    SDL_Texture* texture = ResourceManager::getInstance().getTexture(path);
    mTRenderComponent->setTexture(texture);

    for (int i = 0; i < mBlasts; i++) {
      level.addObject(blasts[i]);
    }
    mCounterComponent->setCounter(0);

    // Need to cool down before next time it fires
    mNextThrowTime = SDL_GetTicks() + mCooldownDelay;
  } else {
    std::string path = "TD2D/Sprites/Towers/cpix_towers/aoe_tower_";
    path += (std::to_string(mCounterComponent->getCounter() + 1) + ".png");
    SDL_Texture* texture = ResourceManager::getInstance().getTexture(path);
    mTRenderComponent->setTexture(texture);
  }
}
