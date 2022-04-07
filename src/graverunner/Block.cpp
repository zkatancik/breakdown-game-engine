#include <box2d/b2_body.h>
#include "graverunner/Block.hpp"

#include "base/TextureRenderComponent.hpp"
#include "base/ResourceManager.hpp"
#include "base/RemoveOnCollideComponent.hpp"

using namespace std;

Block::Block(Level& level, float x, float y, BlockData bd, int h,
             Vector2D<int> bs)
    : GameObject(level, x, y, bs.x, bs.y, NormalBlockTag) {
  init(x, y, bd, h, bs);
}

void Block::init(int xCoord, int yCoord, BlockData bd, int h,
                 Vector2D<int> bs) {
  Dest.x = xCoord;
  Dest.y = yCoord;
  Dest.w = bs.x;
  Dest.h = bs.y;

  blockData = bd;
  health = h;

  if (blockData.block_Type == BlockType::Key) {
    texture_ = ResourceManager::getInstance().getTexture("Graverunner/key.png");
    setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, b2BodyType::b2_staticBody, true));
  } else if (blockData.block_Type == BlockType::Exit) {
    texture_ = ResourceManager::getInstance().getTexture("Graverunner/exit.png");
    setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, b2BodyType::b2_staticBody, true));
  } else if (blockData.block_Type == BlockType::PlainBlock) {
    texture_ = getBlockTexture(blockData.blockNumber);
    setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, b2BodyType::b2_staticBody, false));
  }

  addGenericComponent(std::make_shared<RemoveOnCollideComponent>(*this, BulletTag));
  auto render = std::make_shared<TextureRenderComponent>(*this);
  render->setTexture(texture_);
  setRenderComponent(render);
}

bool Block::reduceHealth() {
  if (health > 0) {
    health--;
  }

  return (health == 0);
}
