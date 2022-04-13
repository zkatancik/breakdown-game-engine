#include "base/TextComponent.hpp"

#include <utility>

TextComponent::TextComponent(
    GameObject &gameObject, std::string engtext, int fontSize,
    std::string fontPath,
    std::shared_ptr<TextureRenderComponent> renderComponent, Language language,
    std::vector<int> color)
    : GenericComponent(gameObject),
      mRenderComponent(std::move(renderComponent)),
      mText(std::move(engtext)),
      mFontPath(std::move(fontPath)),
      mLanguage(language),
      mFontSize(fontSize),
      mColor(color) {
  changeLanguage(Language::ENGLISH);
}
void TextComponent::changeLanguage(Language language) { mLanguage = language; }
void TextComponent::update(Level &level) {
  auto translationText =
      ResourceManager::getInstance().getTranslation(mText, mLanguage);
  auto textTexture = ResourceManager::getInstance().getTextTexture(
      translationText, mFontPath,
      {static_cast<Uint8>(mColor[0]), static_cast<Uint8>(mColor[1]),
       static_cast<Uint8>(mColor[2]), static_cast<Uint8>(mColor[3])},
      mFontSize);
  mRenderComponent->setTexture(textTexture);
}
