#ifndef LEVEL_EDIT_BUTTON_HPP
#define LEVEL_EDIT_BUTTON_HPP

#include <base/Tag.hpp>

#include "base/CenterTextComponent.hpp"
#include "base/InputManager.hpp"
#include "base/RectangleRenderComponent.hpp"
#include "base/SelectableComponent.hpp"
#include "base/TextComponent.hpp"
#include "breakout/Mouse.hpp"
#include "breakout/Tag.hpp"

/**
 * @brief A class representing a clickable UI Text Button.
 */
class LevelEditButton : public GameObject {
 public:
  LevelEditButton(Level& level, float x, float y, float w, float h,
                  float xOffSet, float yOffSet, std::string path,
                  std::string soundPath, std::function<void(void)> selectHook);

  std::shared_ptr<RectangleRenderComponent> getButtonRenderer() const {
    return buttonRenderer;
  }

  std::shared_ptr<TextureRenderComponent> getItemRenderer() const {
    return itemRenderer;
  }

 private:
  std::shared_ptr<RectangleRenderComponent> buttonRenderer;
  std::shared_ptr<TextureRenderComponent> itemRenderer;
  std::vector<std::shared_ptr<TextureRenderComponent>> prevComponents{};
};

#endif