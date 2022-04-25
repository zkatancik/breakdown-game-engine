
#include "custom/MagicTower.hpp"

#include "base/ResourceManager.hpp"
#include "custom/Tag.hpp"

MagicTower::MagicTower(Level &level, float x, float y, Vector2D<int> bs)
    : GameObject(level, x, y, bs.x, bs.y, TdMagicTowerTag) {
  renderer_ = std::make_shared<TextureRenderComponent>(*this);
  setRenderComponent(renderer_);
  renderer_->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/Towers/cpix_towers/aoe_tower_1.png"));
  auto magicComponent = std::make_shared<MagicBlastComponent>(
      *this, RADIUS, SPEED, COOLDOWN, BLASTS, renderer_);
  addGenericComponent(magicComponent);
}
