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
  CustomEnemyUpdateSpriteSheetComponent(GameObject& gameObject, const std::string& spritePath,
                                              const std::shared_ptr<TextureRenderComponent>& textureRenderComponent) :
                                              GenericComponent(gameObject), mSpritePath(spritePath),
                                              mTRenderComponent(textureRenderComponent) {
    mCounterComponent = std::make_shared<CyclicCounterComponent>(gameObject, 10, true);
    gameObject.addGenericComponent(mCounterComponent);
 }

 bool checkDirection() {
    return PhysicsManager::getInstance().hasStarted() && getGameObject().physicsComponent()->vx() <= 0;
  }

 void update(Level& level) override {

    std::string path = "TD2D/Sprites/Enemies/cpix_enemies/" + mSpritePath;
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

std::string getEnemySpritePath(const TdLevelItem enemyItem) {
  std::string returnPath = "";
  switch (enemyItem)
  {
    case TdLevelItem::SCORPIONS:
      returnPath = "1/1_enemies_1_run_";
      break;

    case TdLevelItem::WIZARD:
      returnPath = "2/2_enemies_1_run_";
      break;

    case TdLevelItem::OGRE:
      returnPath = "3/3_enemies_1_run_";
      break;

    case TdLevelItem::HELMETSWORDSMAN:
      returnPath = "4/4_enemies_1_run_";
      break;

    case TdLevelItem::HELMETOGRE:
      returnPath = "5/5_enemies_1_run_";
      break;

    case TdLevelItem::SWORDCAT:
      returnPath = "6/6_enemies_1_run_";
      break;

    case TdLevelItem::ETCAT:
      returnPath = "7/7_enemies_1_run_";
      break;

    case TdLevelItem::MOONOGRE:
      returnPath = "8/8_enemies_1_run_";
      break;

    case TdLevelItem::ETSHURIKEN:
      returnPath = "9/9_enemies_1_run_";
      break;

    case TdLevelItem::HELMETOGRESWORDSMAN:
      returnPath = "10/10_enemies_1_run_";
      break;

    default:
      break;
  }

  return returnPath;
}

CustomEnemy::CustomEnemy(Level& level, float tl_x, float tl_y, float w, float h,
                         TdLevelItem enemyItem, int health,
                         const std::function<void(void)>& callBackAtDeath)
    : GameObject(level, tl_x, tl_y, w, h, TdEnemyTag) {

  enemyItem_ = enemyItem;

  // Add the texture render component, along with the health bar rendering components
  healthBarR_ = std::make_shared<RectangleRenderComponent>(255, 0, 0, *this);
  healthBarG_ = std::make_shared<RectangleRenderComponent>(0, 255, 0, *this);
  std::vector otherRenderComps = {healthBarR_, healthBarG_};
  renderer_ = std::make_shared<TextureRenderComponent>(*this, otherRenderComps);
  setRenderComponent(renderer_);

  setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, b2BodyType::b2_kinematicBody, false));
  
  addGenericComponent(std::make_shared<RemoveOnCollideComponent>(*this, TdBulletTag));

  addGenericComponent(std::make_shared<CustomEnemyUpdateSpriteSheetComponent>(*this, getEnemySpritePath(enemyItem_), renderer_));

  // Health component for the enemy
  auto healthComponent = std::make_shared<HealthComponent>(*this, health);
  healthComponent->setCallbackAtDeath(callBackAtDeath);

  // A lambda function which moves the health bar with the enemy
  // and updates it when health decreases
  auto redrawHealthBarLambda = [this, health](int curHealth) {
    int totalBarWidth = this->w();
    SDL_Rect healthRect = {(int)(this->x()), (int)(this->y()) - 5,
                           (int)totalBarWidth, 5};
    healthBarR_->setRect(healthRect);
    float greenWidth = ((float) curHealth) / health;
    healthRect = {(int)(this->x()), (int)(this->y()) - 5,
                          (int)(greenWidth * totalBarWidth) , 5};
    healthBarG_->setRect(healthRect);
  };
  healthComponent->setCallbackAtUpdate(redrawHealthBarLambda);
  healthComponent->addHealthModifier(TdBulletTag, -1);
  addGenericComponent(healthComponent);
  addGenericComponent(std::make_shared<RemoveOnCollideComponent>(*this, TdBulletTag));
}

CustomEnemy::~CustomEnemy() {
  genericComponents().clear();
}
