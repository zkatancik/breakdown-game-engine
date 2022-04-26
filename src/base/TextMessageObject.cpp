#include "base/TextMessageObject.hpp"

TextMessageObject::TextMessageObject(Level &level,
                                     const std::string &message,
                                     float x,
                                     float y,
                                     const std::string &fontFile,
                                     int fontSize) : GameObject(level, x, y, 0, 0, BaseTextTag) {
  auto textRenderer = std::make_shared<TextureRenderComponent>(*this);

  textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  setRenderComponent(textRenderer);
  auto textComponent = std::make_shared<TextComponent>(*this, message, fontSize, fontFile, textRenderer);
  addGenericComponent(textComponent);
}

void TextMessageObject::changeText(const std::string &newText) {
  getGenericComponent<TextComponent>()->SetMText(newText);
}
