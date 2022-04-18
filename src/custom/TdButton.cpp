#include "custom/TdButton.hpp"

#include <custom/Tag.hpp>

#include "base/CenterTextComponent.hpp"
#include "base/InputManager.hpp"
#include "base/SelectableComponent.hpp"

TdButton::TdButton(Level& level, float x, float y, float w, float h,
                   const std::string& text,
                   std::function<void(void)> selectHook, int fontSize)
    : GameObject(level, x, y, w, h, BaseButtonTag) {
  // Load sprite sheet for the buttons
  buttonRenderer = std::make_shared<TextureRenderComponent>(*this);
  buttonRenderer->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/GUI/Menu/buttons.png"));
  // Set crops from the sprite sheet.

  mCropNotFocused = {528, 850, 1580, 510};
  mCropFocused = {528, 1543, 1580, 510};

  // Set event handlers for the SelectableComponent
  auto mHoverChangeFocus = [&]() { buttonRenderer->setCrop(mCropFocused); };
  auto mNotSelectChangeFocus = [&]() {
    buttonRenderer->setCrop(mCropNotFocused);
  };

  auto addedSoundWithSelectHook = [selectHook = std::move(selectHook)] {
    Mix_PlayChannel(
        1,
        ResourceManager::getInstance().getChunk("TD2D/Audio/Common/Click1.mp3"),
        0);
    selectHook();
  };
  textRenderer = std::make_shared<TextureRenderComponent>(
      *this, std::vector({buttonRenderer}));

  textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);

  setRenderComponent(textRenderer);

  textComponent = std::make_shared<TextComponent>(*this, text, fontSize,
                                                  mButtonFont, textRenderer);
  addGenericComponent(textComponent);

  addGenericComponent(std::make_shared<CenterTextComponent>(
      *this, textRenderer, this->x(), this->y()));

  textRenderer->setOffSetY(int(30));

  auto selectableComponent = std::make_shared<SelectableComponent>(
      *this, addedSoundWithSelectHook, mHoverChangeFocus,
      mNotSelectChangeFocus);
  addGenericComponent(selectableComponent);
}