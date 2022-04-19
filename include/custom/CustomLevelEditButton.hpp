#ifndef TD_LEVEL_EDIT_BUTTON_HPP
#define TD_LEVEL_EDIT_BUTTON_HPP

#include <base/Tag.hpp>

#include "base/CenterTextComponent.hpp"
#include "base/InputManager.hpp"
#include "base/RectangleRenderComponent.hpp"
#include "base/SelectableComponent.hpp"
#include "base/TextComponent.hpp"
#include "custom/Mouse.hpp"
#include "custom/Tag.hpp"

/**
 * @brief A class representing a clickable UI Text Button in the Tower Defense
 * game.
 */
class CustomLevelEditButton : public GameObject {
 public:
  /**
   * @brief Construct a new Custom Level Edit Button object.
   *
   * @param level level information
   * @param x button position
   * @param y button position
   * @param w button width
   * @param h button height
   * @param xOffSet x offset of text within button
   * @param yOffSet y offset of text within button
   * @param path filepath to button texture
   * @param soundPath filepath to on-click sound
   * @param selectHook hook called when button is clicked
   * @param customWidth true if should use a custom width, overriding autosizing
   * around texture/text
   */
  CustomLevelEditButton(Level& level, float x, float y, float w, float h,
                        float xOffSet, float yOffSet, std::string path,
                        std::string soundPath,
                        std::function<void(void)> selectHook,
                        bool customWidth = false);

  /**
   * @brief Get the button texture renderer as a RectangleRenderComponent.
   *
   * @return std::shared_ptr<RectangleRenderComponent> the renderer
   */
  std::shared_ptr<RectangleRenderComponent> getButtonRenderer() const {
    return buttonRenderer;
  }

  /**
   * @brief Get the button texture renderer as a TextureRenderComponent.
   *
   * @return std::shared_ptr<TextureRenderComponent>
   */
  std::shared_ptr<TextureRenderComponent> getItemRenderer() const {
    return itemRenderer;
  }

 private:
  std::shared_ptr<RectangleRenderComponent> buttonRenderer;
  std::shared_ptr<TextureRenderComponent> itemRenderer;
  std::vector<std::shared_ptr<TextureRenderComponent>> prevComponents{};
};

#endif