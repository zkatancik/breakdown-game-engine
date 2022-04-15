
#include "custom/RockThrowerTower.hpp"

#include "base/ResourceManager.hpp"
#include "custom/PeriodicRockThrowComponent.hpp"
#include "custom/Tag.hpp"

RockThrowerTower::RockThrowerTower(Level &level, float x, float y,
                                   Vector2D<int> bs)
    : GameObject(level, x, y, bs.x, bs.y, TdRockThrowerTowerTag) {
  renderer_ = std::make_shared<TextureRenderComponent>(*this);
  setRenderComponent(renderer_);
  renderer_.get()->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/Towers/cpix_towers/3.png"));
  auto throwerComponent =
      std::make_shared<PeriodicRockThrowComponent>(*this, 100, 500);
  addGenericComponent(throwerComponent);
}
