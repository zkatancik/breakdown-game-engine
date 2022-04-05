#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <functional>
#include <base/GameObject.hpp>
#include "base/ResourceManager.hpp"
#include "base/Level.hpp"
#include "base/SelectableComponent.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/TextComponent.hpp"

/**
 * @brief A class representing a clickable UI Text Button in Breakout
 */
class Button : public GameObject {
 public:
  enum Color {
    RED,
    GREEN
  };

  Button(Level& level, float x, float y, float w, float h, Color color, const std::string& text,
         const std::function<void(void)>& selectHook);

  void changeLanguage(Language language);


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