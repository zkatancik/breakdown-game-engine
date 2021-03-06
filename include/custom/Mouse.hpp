#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "base/GameObject.hpp"
#include "base/ResourceManager.hpp"
#include "base/SDL_DEBUG.hpp"
#include "base/Tag.hpp"
#include "base/TextureRenderComponent.hpp"

/**
 * @brief A class representing a mouse cursor controllable by the user.
 */
class Mouse : public GameObject {
 public:
  /**
   * @brief Construct a new Mouse object
   *
   * @param level the level that this mouse belongs to
   */
  Mouse(Level& level) : GameObject(level, 1, 1, 48, 48, BaseMouseTag) {
    auto renderComponent = std::make_shared<TextureRenderComponent>(*this);
    renderComponent->setTexture(ResourceManager::getInstance().getTexture(
        "TD2D/Sprites/GUI/Cursors/Cursor.png"));
    setRenderComponent(renderComponent);
    SDL_ShowCursor(false);
  }

  /**
   * @brief Updates the state of this mouse with SDL
   */
  void update() override {
    int x, y;
    SDL_GetMouseState(&x, &y);
    setX(float(x));
    setY(float(y));
    GameObject::update();
  }
};

#endif