#include "breakout/Button.hpp"

#include <breakout/Tag.hpp>

#include "base/CenterTextComponent.hpp"
#include "base/InputManager.hpp"

Button::Button(Level& level, float x, float y, float w, float h, Color color,
               const std::string& text, std::function<void(void)> selectHook)
    : GameObject(level, x, y, w, h, ButtonTag) {
  // Load sprite sheet for the buttons
  buttonRenderer = std::make_shared<TextureRenderComponent>(*this);
  buttonRenderer->setTexture(ResourceManager::getInstance().getTexture(
      "2DBreakout/Graphics/buttonSpriteSheet.png"));
  // Set crops from the sprite sheet.
  switch (color) {
    case RED:
      mCropNotFocused = {635, 860, 513, 177};
      mCropFocused = {57, 860, 513, 177};
      break;
    case GREEN:
      mCropNotFocused = {635, 1122, 513, 177};
      mCropFocused = {57, 1122, 513, 177};
    default:
      break;
  }
  // Set event handlers for the SelectableComponent
  auto mHoverChangeFocus = [&]() { buttonRenderer->setCrop(mCropFocused); };
  auto mNotSelectChangeFocus = [&]() {
    buttonRenderer->setCrop(mCropNotFocused);
  };

  auto addedSoundWithSelectHook = [selectHook = std::move(selectHook)] {
    Mix_PlayChannel(1,
                    ResourceManager::getInstance().getChunk(
                        "2DBreakout/SFX/ButtonClick_SFX.wav"),
                    0);
    selectHook();
  };
  textRenderer = std::make_shared<TextureRenderComponent>(
      *this, std::vector({buttonRenderer}));

  textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);

  setRenderComponent(textRenderer);

  textComponent = std::make_shared<TextComponent>(*this, text, mFontSize,
                                                  mButtonFont, textRenderer);
  addGenericComponent(textComponent);

  addGenericComponent(std::make_shared<CenterTextComponent>(
      *this, textRenderer, this->x(), this->y()));

  auto selectableComponent = std::make_shared<SelectableComponent>(
      *this, addedSoundWithSelectHook, mHoverChangeFocus,
      mNotSelectChangeFocus);
  addGenericComponent(selectableComponent);
}