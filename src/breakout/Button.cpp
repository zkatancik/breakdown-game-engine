#include <breakout/Tag.hpp>
#include "breakout/Button.hpp"
#include "base/TextObject.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/InputManager.hpp"

Button::Button(Level& level, float x, float y, float w, float h, const std::string& text,
               const std::function<void(void)>& selectHook) : GameObject(level, x, y, w, h, ButtonTag),
               mText(std::make_shared<TextObject>(level, x + 30, y + 30, 64, text, Language::ENGLISH)){
  auto renderComponent = std::make_shared<TextureRenderComponent>(*this);
  renderComponent->setTexture(ResourceManager::getInstance().getTexture("buttonSpriteSheet.png"));
  level.addObject(mText);
  auto selectableComponent = std::make_shared<SelectableComponent>(*this, selectHook);
  addGenericComponent(selectableComponent);
}
