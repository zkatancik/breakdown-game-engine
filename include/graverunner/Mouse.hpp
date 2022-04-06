#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "base/SDL_DEBUG.hpp"
#include "base/GameObject.hpp"
#include "base/ResourceManager.hpp"
#include "graverunner/Tag.hpp"
#include "base/TextureRenderComponent.hpp"

/**
 * @brief A class representing a mouse cursor controllable by the user.
 */
class Mouse : public GameObject {
 public:
  Mouse(Level& level) : GameObject(level, 1, 1, 35, 61, MouseTag) {
    auto renderComponent = std::make_shared<TextureRenderComponent>(*this);
    renderComponent->setTexture(ResourceManager::getInstance().getTexture("Graverunner/mouse/mouse.png"));
    setRenderComponent(renderComponent);
    SDL_ShowCursor(false);
  }


  void update() override {
    int x, y;
    SDL_GetMouseState(&x, &y);
    setX(float(x));
    setY(float(y));
    GameObject::update();
  }
};

#endif