#include "graverunner/ExitBlock.hpp"

#include <box2d/b2_body.h>

#include "base/RemoveOnCollideComponent.hpp"
#include "base/ResourceManager.hpp"
#include "base/TextureRenderComponent.hpp"
#include "graverunner/Tag.hpp"

using namespace std;

ExitBlock::ExitBlock(Level& level, float x, float y, Vector2D<int> dims)
    : GameObject(level, x, y, dims.x, dims.y, ExitTag) {
  SDL_Texture* texture =
      ResourceManager::getInstance().getTexture("Graverunner/exit.png");
  setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, b2BodyType::b2_staticBody, true));

  addGenericComponent(
      std::make_shared<RemoveOnCollideComponent>(*this, BulletTag));
  auto render = std::make_shared<TextureRenderComponent>(*this);
  render->setTexture(texture);
  setRenderComponent(render);
}
