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
  TdButton(Level& level, float x, float y, float w, float h,
           const std::string& text, std::function<void(void)> selectHook);

  std::shared_ptr<TextureRenderComponent> getTextureRenderer() const {
    return buttonRenderer;
  }

 private:
  int mFontSize{64};
  const std::string mButtonFont = "Graverunner/fonts/GADAQUALI.ttf";
  std::shared_ptr<TextureRenderComponent> buttonRenderer;
  std::shared_ptr<TextureRenderComponent> textRenderer;
  std::shared_ptr<TextComponent> textComponent;
  SDL_Rect mCropNotFocused{0, 0, 0, 0};
  SDL_Rect mCropFocused{0, 0, 0, 0};
};

#endif