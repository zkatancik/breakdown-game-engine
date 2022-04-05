#include "base/SelectableComponent.hpp"

#include <utility>

#include "base/Level.hpp"

SelectableComponent::SelectableComponent(GameObject& gameObject) : GenericComponent(gameObject),
                                                                   mSelectHook([&] () {}),
                                                                   mHoverHook([&] () {}),
                                                                   mNotSelectHook([&] () {})
                                                                   {}

SelectableComponent::SelectableComponent(GameObject &gameObject, std::function<void(void)> onSelectHook) : GenericComponent(gameObject),
mSelectHook(std::move(onSelectHook)), mHoverHook([&] () {}), mNotSelectHook([&] () {}) {}

SelectableComponent::SelectableComponent(GameObject& gameObject, std::function<void(void)> onSelectHook,
                                         std::function<void(void)> onHoverHook) : GenericComponent(gameObject),
                                         mSelectHook(std::move(onSelectHook)), mHoverHook(std::move(onHoverHook)), mNotSelectHook([&] () {}) {}

SelectableComponent::SelectableComponent(GameObject &gameObject,
                                         std::function<void(void)> onSelectHook,
                                         std::function<void(void)> onHoverHook,
                                         std::function<void(void)> NotSelectHook) : GenericComponent(gameObject),
                                         mSelectHook(std::move(onSelectHook)), mHoverHook(std::move(onHoverHook)),
                                         mNotSelectHook(std::move(NotSelectHook)){}

void SelectableComponent::update(Level &level) {
  bool isLeftKeyPressed = InputManager::getInstance().isMouseKeyPressed(SDL_BUTTON_LEFT);
  int mouseLocX = 0;
  int mouseLocY = 0;
  SDL_GetMouseState(&mouseLocX, &mouseLocY);
  if (getGameObject().isOverlapping(float(mouseLocX), float(mouseLocY))) {
    mHoverHook();
    if (isLeftKeyPressed) {
      mSelectHook();
    }
  }
  else
    mNotSelectHook();
}



