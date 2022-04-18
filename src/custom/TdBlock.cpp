#include "custom/TdBlock.hpp"

#include <box2d/b2_body.h>

#include "base/RemoveOnCollideComponent.hpp"
#include "base/PerformHookOnCollideComponent.hpp"
#include "base/ResourceManager.hpp"
#include "base/TextureRenderComponent.hpp"

using namespace std;

TdBlock::TdBlock(Level& level, float x, float y, TdBlockData bd,
                 Vector2D<int> bs, int tag)
    : GameObject(level, x, y, bs.x, bs.y, tag) {
  init(x, y, bd, bs);
}

void TdBlock::init(int xCoord, int yCoord, TdBlockData bd, Vector2D<int> bs) {
  Dest.x = xCoord;
  Dest.y = yCoord;
  Dest.w = bs.x;
  Dest.h = bs.y;

  blockData = bd;

  texture_ = getBlockTexture();
  auto render = std::make_shared<TextureRenderComponent>(*this);
  render->setTexture(texture_);
  setRenderComponent(render);

  // Add physics to blocks- static sensor
  setPhysicsComponent(std::make_shared<PhysicsComponent>(
      *this, b2BodyType::b2_staticBody, true));
}

SDL_Texture* TdBlock::getBlockTexture() {
  std::string filename = "";
  switch (blockData.levelItemType) {
    case TdLevelItem::PLAINBLOCK:
      filename = "Empty.png";
      return ResourceManager::getInstance().getTexture(
        (std::filesystem::path("TD2D/Sprites/Tiles/") / filename).string());
    case TdLevelItem::PATHBLOCK0:
    case TdLevelItem::PATHBLOCK1:
    case TdLevelItem::PATHBLOCK2:
    case TdLevelItem::PATHBLOCK3:
    case TdLevelItem::PATHBLOCK4:
    case TdLevelItem::PATHBLOCK5:
    case TdLevelItem::PATHBLOCK6:
    case TdLevelItem::PATHBLOCK7:
    case TdLevelItem::PATHBLOCK8:
    case TdLevelItem::PATHBLOCK9:
    case TdLevelItem::PATHBLOCKA:
      filename = "Road" + blockData.blockNumber + ".png";
      return ResourceManager::getInstance().getTexture(
        (std::filesystem::path("TD2D/Sprites/Tiles/") / filename).string());
    case TdLevelItem::PLACETOWER:
      filename = "BuildingPlace.png";
      return ResourceManager::getInstance().getTexture(
        (std::filesystem::path("TD2D/Sprites/Towers/") / filename).string());
    case TdLevelItem::START:
      filename = "SpawnPointGizmo.png";
      return ResourceManager::getInstance().getTexture(
        (std::filesystem::path("TD2D/Sprites/Gizmos/") / filename).string());
    case TdLevelItem::END:
      filename = "CapturePointGizmo.png";
      return ResourceManager::getInstance().getTexture(
        (std::filesystem::path("TD2D/Sprites/Gizmos/") / filename).string());
    default:
      std::cerr << "Error- getBlockTexture of unsupported block type!"
                << std::endl;
      return nullptr;
  }
}
