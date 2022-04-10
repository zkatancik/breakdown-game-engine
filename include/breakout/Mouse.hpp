#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "base/SDL_DEBUG.hpp"
#include "base/GameObject.hpp"
#include "base/ResourceManager.hpp"
#include "breakout/Tag.hpp"
#include "base/TextureRenderComponent.hpp"

/**
 * @brief A class representing a mouse cursor controllable by the user.
 */
class Mouse : public GameObject {
 public:
  explicit Mouse(Level& level) : GameObject(level, 1, 1, 35, 35, BaseMouseTag) {
    updateMouseLocation();
    auto renderComponent = std::make_shared<TextureRenderComponent>(*this);
    renderComponent->setTexture(ResourceManager::getInstance().getTexture("2DBreakout/Graphics/mouse.png"));
    setRenderComponent(renderComponent);
    SDL_ShowCursor(false);
  }

  void update() override {
    updateMouseLocation();
    GameObject::update();
  }
 private:
  void updateMouseLocation() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    setX(float(x));
    setY(float(y));
  }
};

#endif