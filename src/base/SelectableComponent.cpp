#include "base/SelectableComponent.hpp"

#include <utility>

#include "base/Level.hpp"

SelectableComponent::SelectableComponent(GameObject& gameObject) : GenericComponent(gameObject),
                                                                   mSelectHook([&] (Level& level) {}),
                                                                   mHoverHook([&] (Level& level) {}) {}

SelectableComponent::SelectableComponent(GameObject &gameObject, std::function<void(void)> onSelectHook) : GenericComponent(gameObject),
mSelectHook(onSelectHook), mHoverHook([&] (Level& level) {}) {}

SelectableComponent::SelectableComponent(GameObject& gameObject, std::function<void(void)> onSelectHook,
                                         std::function<void(void)> onHoverHook) : GenericComponent(gameObject),
                                         mSelectHook(onSelectHook), mHoverHook(onHoverHook) {}

void SelectableComponent::update(Level &level) {
  bool isLeftKeyPressed = InputManager::getInstance().isMouseKeyPressed(SDL_BUTTON_LEFT);
  int mouseLocX = 0;
  int mouseLocY = 0;
  SDL_GetMouseState(&mouseLocX, &mouseLocY);
  if (isOverlapping(float(mouseLocX), float(mouseLocY))) {
    mHoverHook(level);
    if (isLeftKeyPressed) {
      mSelectHook(level);
    }
  }
}


