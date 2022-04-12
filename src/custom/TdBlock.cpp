#include "custom/TdBlock.hpp"

#include <box2d/b2_body.h>

#include "base/RemoveOnCollideComponent.hpp"
#include "base/ResourceManager.hpp"
#include "base/TextureRenderComponent.hpp"

using namespace std;

// TdBlock::TdBlock(Level& level, float x, float y, TdBlockData bd,
//                  Vector2D<int> bs)
//     : GameObject(level, x, y, bs.x, bs.y, TdNormalBlockTag) {
//   init(x, y, bd, bs);
// }

// void TdBlock::init(int xCoord, int yCoord, TdBlockData bd, Vector2D<int> bs)
// {
//   Dest.x = xCoord;
//   Dest.y = yCoord;
//   Dest.w = bs.x;
//   Dest.h = bs.y;

//   blockData = bd;

//   texture_ = getBlockTexture(blockData.blockNumber);
//   setPhysicsComponent(std::make_shared<PhysicsComponent>(
//       *this, b2BodyType::b2_staticBody, false));

//   addGenericComponent(
//       std::make_shared<RemoveOnCollideComponent>(*this, TdBulletTag));
//   auto render = std::make_shared<TextureRenderComponent>(*this);
//   render->setTexture(texture_);
//   setRenderComponent(render);
// }
