
#include "custom/ArrowTower.hpp"

#include "base/ResourceManager.hpp"
#include "custom/ArrowBarrageComponent.hpp"
#include "custom/Tag.hpp"

ArrowTower::ArrowTower(Level &level, float x, float y, Vector2D<int> bs)
    : GameObject(level, x, y, bs.x, bs.y, TdArrowTowerTag) {
  renderer_ = std::make_shared<TextureRenderComponent>(*this);
  setRenderComponent(renderer_);
  renderer_->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/Towers/cpix_towers/arrow_tower_1.png"));
  auto throwerComponent = std::make_shared<ArrowBarrageComponent>(
      *this, RADIUS, SPEED, COOLDOWN, ArrowTargetingPreference::FIRST,
      renderer_);
  addGenericComponent(throwerComponent);
}

ArrowTargetingPreference ArrowTower::getTargetPref() {
  return getGenericComponent<ArrowBarrageComponent>()->getTargetPref();
}

void ArrowTower::setTargetPref(ArrowTargetingPreference newPref) {
  getGenericComponent<ArrowBarrageComponent>()->setTargetPref(newPref);
}