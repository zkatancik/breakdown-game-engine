#include <box2d/b2_body.h>
#include <functional>
#include "custom/CustomEnemy.hpp"
#include "custom/Tag.hpp"
#include "base/ResourceManager.hpp"
#include "base/RemoveOnCollideComponent.hpp"
#include "base/PhysicsManager.hpp"
#include "base/HealthComponent.hpp"
#include "custom/LevelData.hpp"

/**
 * A separate component for updating the sprite sheet for the CustomEnemy.
 */
class CustomEnemyUpdateSpriteSheetComponent : public GenericComponent {
 public:
  CustomEnemyUpdateSpriteSheetComponent(
      GameObject& gameObject, const std::string& spritePath,
      const std::shared_ptr<TextureRenderComponent>& textureRenderComponent)
      : GenericComponent(gameObject),
        mSpritePath(spritePath),
        mTRenderComponent(textureRenderComponent) {
    mCounterComponent =
        std::make_shared<CyclicCounterComponent>(gameObject, 10, true);
    gameObject.addGenericComponent(mCounterComponent);
  }

  bool checkDirection() {
    return PhysicsManager::getInstance().hasStarted() &&
           getGameObject().physicsComponent()->vx() <= 0;
  }

 void update(Level& level) override {
    std::string path = mSpritePath;
    path += (std::to_string(mCounterComponent->getCounter() + 1) + ".png");

    SDL_Texture* texture = ResourceManager::getInstance().getTexture(path);
    mTRenderComponent->setTexture(texture);
    mTRenderComponent->setFlip(checkDirection());
  }

 private:
  std::string mSpritePath;
  std::shared_ptr<TextureRenderComponent> mTRenderComponent;
  std::shared_ptr<CyclicCounterComponent> mCounterComponent;
};

CustomEnemy::CustomEnemy(Level& level, float tl_x, float tl_y, float w, float h,
                         TdLevelItem enemyItem,
                         const std::function<void(void)>& callBackAtDeath,
                         int count)
    : GameObject(level, tl_x, tl_y, w, h, TdEnemyTag) {
  enemyItem_ = enemyItem;
  mCount = count;

  // Add the texture render component, along with the health bar rendering
  // components
  healthBarR_ = std::make_shared<RectangleRenderComponent>(255, 0, 0, *this);
  healthBarG_ = std::make_shared<RectangleRenderComponent>(0, 255, 0, *this);
  std::vector otherRenderComps = {healthBarR_, healthBarG_};
  renderer_ = std::make_shared<TextureRenderComponent>(*this, otherRenderComps);
  setRenderComponent(renderer_);

  setPhysicsComponent(std::make_shared<PhysicsComponent>(
      *this, b2BodyType::b2_kinematicBody, false));

  addGenericComponent(
      std::make_shared<RemoveOnCollideComponent>(*this, TdBulletTag));

  addGenericComponent(std::make_shared<CustomEnemyUpdateSpriteSheetComponent>(
      *this, getEnemySpritePath(enemyItem_), renderer_));

  // Health component for the enemy
  int health;
  switch (enemyItem) {
    case TdLevelItem::SCORPIONS:
      health = 5;
      break;

    case TdLevelItem::WIZARD:
      health = 8;
      break;

    case TdLevelItem::OGRE:
      health = 10;
      break;

    case TdLevelItem::HELMETSWORDSMAN:
      health = 5;
      break;

    case TdLevelItem::HELMETOGRE:
      health = 12;
      break;

    case TdLevelItem::SWORDCAT:
      health = 12;
      break;

    case TdLevelItem::ETCAT:
      health = 14;
      break;

    case TdLevelItem::MOONOGRE:
      health = 10;
      break;

    case TdLevelItem::ETSHURIKEN:
      health = 4;
      break;

    case TdLevelItem::HELMETOGRESWORDSMAN:
      health = 15;
      break;

    default:
      break;
  }
  auto healthComponent = std::make_shared<HealthComponent>(*this, health);
  healthComponent->setCallbackAtDeath(callBackAtDeath);

  // A lambda function which moves the health bar with the enemy
  // and updates it when health decreases
  auto redrawHealthBarLambda = [this, health](int curHealth) {
    int totalBarWidth = this->w();
    SDL_Rect healthRect = {(int)(this->x()), (int)(this->y()) - 5,
                           (int)totalBarWidth, 5};
    healthBarR_->setRect(healthRect);
    float greenWidth = ((float)curHealth) / health;
    healthRect = {(int)(this->x()), (int)(this->y()) - 5,
                  (int)(greenWidth * totalBarWidth), 5};
    healthBarG_->setRect(healthRect);
  };
  healthComponent->setCallbackAtUpdate(redrawHealthBarLambda);
  healthComponent->addHealthModifier(TdBulletTag, -1);
  healthComponent->addHealthModifier(TdAntiTankTowerTag, -10000000);
  addGenericComponent(healthComponent);
  addGenericComponent(
      std::make_shared<RemoveOnCollideComponent>(*this, TdBulletTag));
}

CustomEnemy::~CustomEnemy() { genericComponents().clear(); }
