#include "custom/TdBlock.hpp"

#include <box2d/b2_body.h>

#include "base/RemoveOnCollideComponent.hpp"
#include "base/ResourceManager.hpp"
#include "base/TextureRenderComponent.hpp"

using namespace std;

TdBlock::TdBlock(Level& level, float x, float y, TdBlockData bd,
                 Vector2D<int> bs)
    : GameObject(level, x, y, bs.x, bs.y, TdPlainBlockTag) {
  init(x, y, bd, bs);
}

void TdBlock::init(int xCoord, int yCoord, TdBlockData bd, Vector2D<int> bs) {
  Dest.x = xCoord;
  Dest.y = yCoord;
  Dest.w = bs.x;
  Dest.h = bs.y;

  blockData = bd;

  texture_ = getBlockTexture(blockData.block_Type);
  auto render = std::make_shared<TextureRenderComponent>(*this);
  render->setTexture(texture_);
  setRenderComponent(render);
}

SDL_Texture* TdBlock::getBlockTexture(TdBlockType type) {
  std::string filename = "";
  switch (type) {
    case TdBlockType::Plain:
      filename = "Empty.png";
      break;
    case TdBlockType::Path:
      filename = "Road1.png";
      break;
    default:
      std::cerr << "Error- getBlockTexture of unsupported block type!"
                << std::endl;
      return nullptr;
  }
  return ResourceManager::getInstance().getTexture(
      (std::filesystem::path("TD2D/Sprites/Tiles/") / filename).string());
}
