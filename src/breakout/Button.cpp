#include <breakout/Tag.hpp>
#include "breakout/Button.hpp"
#include "base/InputManager.hpp"

Button::Button(Level& level, float x, float y, float w, float h, Color color, const std::string& text,
               const std::function<void(void)>& selectHook) : GameObject(level, x, y, w, h, ButtonTag), mEnglishText(text) {
  // Load sprite sheet for the buttons
  buttonRenderer = std::make_shared<TextureRenderComponent>(*this);
  buttonRenderer->setTexture(ResourceManager::getInstance().getTexture("2DBreakout/Graphics/buttonSpriteSheet.png"));
  // Set crops from the sprite sheet.
  switch (color) {
    case RED:
      mCropNotFocused = {510, 860, 513, 177};
      mCropFocused = {57, 860, 513, 177};
      break;
    case GREEN:
      mCropNotFocused = {635, 1122, 513, 177};
      mCropFocused = {57, 1122, 513, 177};
    default:
      break;
  }
  // Set event handlers for the SelectableComponent
  auto mHoverChangeFocus = [&] () {buttonRenderer->setCrop(mCropFocused);};
  auto mNotSelectChangeFocus = [&] () {buttonRenderer->setCrop(mCropNotFocused);};


  textRenderer = std::make_shared<TextureRenderComponent>(*this, std::vector({buttonRenderer}));
  textRenderer->setOffSetX(30);
  textRenderer->setOffSetY(30);
  textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  changeLanguage(Language::ENGLISH);

  setRenderComponent(textRenderer);

  auto selectableComponent = std::make_shared<SelectableComponent>(*this, selectHook, mHoverChangeFocus, mNotSelectChangeFocus);
  addGenericComponent(selectableComponent);
}

void Button::changeLanguage(Language language) {
  auto translationText = ResourceManager::getInstance().getTranslation(mEnglishText, language);
  auto textTexture = ResourceManager::getInstance().getTextTexture(translationText,
                                                                   mButtonFont, {255, 255, 255, 0}, mFontSize);
  textRenderer->setTexture(textTexture);
}
