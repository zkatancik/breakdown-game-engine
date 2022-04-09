#include <box2d/b2_body.h>
#include "graverunner/Block.hpp"

#include "base/TextureRenderComponent.hpp"
#include "base/ResourceManager.hpp"
#include "base/RemoveOnCollideComponent.hpp"

using namespace std;

Block::Block(Level& level, float x, float y, BlockData bd, Vector2D<int> bs)
    : GameObject(level, x, y, bs.x, bs.y, NormalBlockTag) {
  init(x, y, bd, bs);
}

void Block::init(int xCoord, int yCoord, BlockData bd, Vector2D<int> bs) {
  Dest.x = xCoord;
  Dest.y = yCoord;
  Dest.w = bs.x;
  Dest.h = bs.y;

  blockData = bd;

  texture_ = getBlockTexture(blockData.blockNumber);
  setPhysicsComponent(std::make_shared<PhysicsComponent>(
      *this, b2BodyType::b2_staticBody, false));

  addGenericComponent(
      std::make_shared<RemoveOnCollideComponent>(*this, BulletTag));
  auto render = std::make_shared<TextureRenderComponent>(*this);
  render->setTexture(texture_);
  setRenderComponent(render);
}
