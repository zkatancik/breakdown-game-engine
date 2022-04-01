#include "graverunner/Block.hpp"

#include "base/TextureRenderComponent.hpp"
#include "base/ResourceManager.hpp"
#include "base/RemoveOnCollideComponent.hpp"

using namespace std;

void Block::startUp(int x, int y, BlockData bd, int h, Vector2D<int> bs) {
  init(x, y, bd, h, bs);
  // TODO this tag num should be different / an enum of some sort
}

void Block::shutDown() {}

void Block::init(int xCoord, int yCoord, BlockData bd, int h,
                 Vector2D<int> bs) {
  Dest.x = xCoord;
  Dest.y = yCoord;
  Dest.w = bs.x;
  Dest.h = bs.y;

  blockData = bd;
  health = h;

  if (blockData.block_Type == BlockType::Key) {
    texture_ = ResourceManager::getInstance().getTexture("key.png");
    GameObject::startUp(xCoord, yCoord, bs.x, bs.y, KeyTag);
    setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SENSOR));
  } else if (blockData.block_Type == BlockType::Exit) {
    texture_ = ResourceManager::getInstance().getTexture("exit.png");
    GameObject::startUp(xCoord, yCoord, bs.x, bs.y, ExitTag);
    setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SENSOR));
  } else if (blockData.block_Type == BlockType::PlainBlock) {
    texture_ = getBlockTexture(blockData.blockNumber);
    GameObject::startUp(xCoord, yCoord, bs.x, bs.y, NormalBlockTag);
    setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SOLID));
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
