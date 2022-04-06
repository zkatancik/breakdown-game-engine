#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "graverunner/Mouse.hpp"
#include "graverunner/Tag.hpp"
#include "base/TextComponent.hpp"

/**
 * @brief A class representing a clickable UI Text Button.
 */
class Button : public GameObject {
 public:
  enum Color { RED, GREEN };

  Button(Level& level, float x, float y, float w, float h, Color color,
         const std::string& text, std::function<void(void)> selectHook);
  std::shared_ptr<TextureRenderComponent> getTextureRenderer() const {
    return buttonRenderer;
  }

 private:
  int mFontSize{64};
  const std::string mButtonFont = "2DBreakout/Fonts/Gageda.ttf";
  std::shared_ptr<TextureRenderComponent> buttonRenderer;
  std::shared_ptr<TextureRenderComponent> textRenderer;
  std::shared_ptr<TextComponent> textComponent;
  SDL_Rect mCropNotFocused{0, 0, 0, 0};
  SDL_Rect mCropFocused{0, 0, 0, 0};
};




#endif