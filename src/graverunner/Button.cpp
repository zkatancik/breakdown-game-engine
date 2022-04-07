#include "graverunner/Button.hpp"

#include <graverunner/Tag.hpp>

#include "base/CenterTextComponent.hpp"
#include "base/InputManager.hpp"
#include "base/SelectableComponent.hpp"

Button::Button(Level& level, float x, float y, float w, float h,
               const std::string& text, std::function<void(void)> selectHook)
    : GameObject(level, x, y, w, h, ButtonTag) {
  // Load sprite sheet for the buttons
  buttonRenderer = std::make_shared<TextureRenderComponent>(*this);
  buttonRenderer->setTexture(ResourceManager::getInstance().getTexture(
      "Graverunner/buttons/buttonSpriteSheet.png"));
  // Set crop from the sprite sheet.
  mCropNotFocused = {408, 179, 784, 295};
  mCropFocused = {408, 541, 784, 295};

  // Set event handlers for the SelectableComponent
  auto mHoverChangeFocus = [&]() { buttonRenderer->setCrop(mCropFocused); };
  auto mNotSelectChangeFocus = [&]() {
    buttonRenderer->setCrop(mCropNotFocused);
  };

  auto addedSoundWithSelectHook = [selectHook = std::move(selectHook)] {
    Mix_PlayChannel(1,
                    ResourceManager::getInstance().getChunk(
                        "Graverunner/2DPlatformer_SFX/"
                        "mixkit-video-game-mystery-alert-234.wav"),
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

  textRenderer->setOffSetY(int(60));

  auto selectableComponent = std::make_shared<SelectableComponent>(
      *this, addedSoundWithSelectHook, mHoverChangeFocus,
      mNotSelectChangeFocus);
  addGenericComponent(selectableComponent);
}