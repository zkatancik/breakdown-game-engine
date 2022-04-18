#include "custom/CustomLevelEditButton.hpp"

CustomLevelEditButton::CustomLevelEditButton(Level& level, float x, float y, float w,
                                 float h, float xOffSet, float yOffSet,
                                 std::string path, std::string soundPath,
                                 std::function<void(void)> selectHook,
                                 bool customWidth)
    : GameObject(level, x, y, w, h, BaseButtonTag) {
  buttonRenderer = std::make_shared<RectangleRenderComponent>(255, 0, 0, *this);
  buttonRenderer->setFlip(true);

  // Set event handlers for the SelectableComponent
  auto mHoverChangeFocus = [&]() { buttonRenderer->setFlip(false); };
  auto mNotSelectChangeFocus = [&]() { buttonRenderer->setFlip(true); };

  auto addedSoundWithSelectHook = [selectHook = std::move(selectHook),
                                   soundPath] {
    Mix_PlayChannel(1, ResourceManager::getInstance().getChunk(soundPath), 0);
    selectHook();
  };
  itemRenderer = std::make_shared<TextureRenderComponent>(
      *this, std::vector({buttonRenderer}));

  if (!customWidth) {
    itemRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  } else {
    itemRenderer->setRenderMode(
        TextureRenderComponent::RenderMode::CUSTOM_WIDTH);
    itemRenderer->setCustomH(h - 10);
    itemRenderer->setCustomW(w - 10);
  }

  setRenderComponent(itemRenderer);

  itemRenderer->setTexture(ResourceManager::getInstance().getTexture(path));

  itemRenderer->setOffSetY(int(yOffSet));
  itemRenderer->setOffSetX(int(xOffSet));

  auto selectableComponent = std::make_shared<SelectableComponent>(
      *this, addedSoundWithSelectHook, mHoverChangeFocus,
      mNotSelectChangeFocus);
  addGenericComponent(selectableComponent);
}
