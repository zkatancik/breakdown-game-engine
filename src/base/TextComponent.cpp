#include "base/TextComponent.hpp"

#include <utility>


TextComponent::TextComponent(GameObject &gameObject,
                             std::string engtext,
                             int fontSize,
                             std::string fontPath,
                             std::shared_ptr<TextureRenderComponent> renderComponent)
    : GenericComponent(gameObject), mRenderComponent(std::move(renderComponent)), mText(std::move(engtext)), mFontPath(std::move(fontPath)),
    mFontSize(fontSize) {
  changeLanguage(Language::ENGLISH);
}
void TextComponent::changeLanguage(Language language) {
  auto translationText = ResourceManager::getInstance().getTranslation(mText, language);
  auto textTexture = ResourceManager::getInstance().getTextTexture(translationText,
                                                                   mFontPath, {255, 255, 255, 0}, mFontSize);
  mRenderComponent->setTexture(textTexture);
}
