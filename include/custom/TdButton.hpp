#ifndef TD_BUTTON_HPP
#define TD_BUTTON_HPP

#include <SDL.h>

#include <functional>

#include "base/TextComponent.hpp"
#include "custom/Mouse.hpp"
#include "custom/Tag.hpp"

/**
 * @brief A class representing a clickable UI Text Button.
 */
class TdButton : public GameObject {
 public:
  /**
   * @brief Construct a new Td Button object
   *
   * @param level the level that this button belongs to
   * @param x x coordinate
   * @param y y coordinate
   * @param w width
   * @param h height
   * @param text string to display in button
   * @param selectHook hook called when button is selected
   * @param fontSize text size of the button label
   */
  TdButton(Level& level, float x, float y, float w, float h,
           const std::string& text, std::function<void(void)> selectHook,
           int fontSize = 64);

  /**
   * @brief Get the Texture Renderer object
   *
   * @return std::shared_ptr<TextureRenderComponent>
   */
  std::shared_ptr<TextureRenderComponent> getTextureRenderer() const {
    return buttonRenderer;
  }

 private:
  int mFontSize{64};
  const std::string mButtonFont = "TD2D/Fonts/ds-coptic.ttf";
  std::shared_ptr<TextureRenderComponent> buttonRenderer;
  std::shared_ptr<TextureRenderComponent> textRenderer;
  std::shared_ptr<TextComponent> textComponent;
  SDL_Rect mCropNotFocused{0, 0, 0, 0};
  SDL_Rect mCropFocused{0, 0, 0, 0};
};

#endif