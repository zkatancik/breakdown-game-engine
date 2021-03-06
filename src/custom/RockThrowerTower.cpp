
#include "custom/RockThrowerTower.hpp"

#include "base/ResourceManager.hpp"
#include "custom/PeriodicRockThrowComponent.hpp"
#include "custom/Tag.hpp"

RockThrowerTower::RockThrowerTower(Level &level, float x, float y,
                                   Vector2D<int> bs)
    : GameObject(level, x, y, bs.x, bs.y, TdRockThrowerTowerTag) {
  renderer_ = std::make_shared<TextureRenderComponent>(*this);
  setRenderComponent(renderer_);
  renderer_->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/Towers/cpix_towers/stone_throw_1.png"));
  auto throwerComponent = std::make_shared<PeriodicRockThrowComponent>(
      *this, RADIUS, SPEED, COOLDOWN, RockThrowingPreference::FIRST, renderer_);
  addGenericComponent(throwerComponent);
}

RockThrowingPreference RockThrowerTower::getTargetPref() {
  return getGenericComponent<PeriodicRockThrowComponent>()->getTargetPref();
}

void RockThrowerTower::setTargetPref(RockThrowingPreference newPref) {
  getGenericComponent<PeriodicRockThrowComponent>()->setTargetPref(newPref);
}