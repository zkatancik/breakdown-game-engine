#include "base/TextComponent.hpp"

#include <utility>


TextComponent::TextComponent(GameObject &gameObject,
                             std::string engtext,
                             int fontSize,
                             std::string fontPath,
                             std::shared_ptr<TextureRenderComponent> renderComponent,
                             Language language)
    : GenericComponent(gameObject), mRenderComponent(std::move(renderComponent)), mText(std::move(engtext)), mFontPath(std::move(fontPath)),
      mLanguage(language), mFontSize(fontSize) {
  changeLanguage(Language::ENGLISH);
}
void TextComponent::changeLanguage(Language language) {
  mLanguage = language;
}
void TextComponent::update(Level &level) {
  auto translationText = ResourceManager::getInstance().getTranslation(mText, mLanguage);
  auto textTexture = ResourceManager::getInstance().getTextTexture(translationText,
                                                                   mFontPath, {255, 255, 255, 0}, mFontSize);
  mRenderComponent->setTexture(textTexture);
}
