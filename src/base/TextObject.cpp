#include <base/ResourceManager.hpp>
#include "base/TextObject.hpp"

TextObject::TextObject(Level &level, float x, float y, int fontSize, const std::string& text, Language language) : GameObject(level),
                                                                                                                   mEnglishText(text), mFontSize(fontSize){
  auto renderComponent = std::make_shared<TextureRenderComponent>(*this);
  setRenderComponent(renderComponent);
  changeLanguage(language);
}
void TextObject::changeLanguage(Language language) {
  auto translationText = ResourceManager::getInstance().getTranslation(mEnglishText, language);
  auto textTexture = ResourceManager::getInstance().getTextTexture(translationText,
                                                                   mButtonFont, {255, 255, 255, 0}, mFontSize);
  mRenderer->setTexture(textTexture);
}
