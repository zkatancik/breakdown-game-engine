#include "editor/LevelEditButton.hpp"

LevelEditButton::LevelEditButton(Level& level, float x, float y, float w,
                                 float h, float xOffSet, float yOffSet,
                                 std::string path, std::string soundPath,
                                 std::function<void(void)> selectHook)
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

  itemRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);

  setRenderComponent(itemRenderer);

  itemRenderer->setTexture(ResourceManager::getInstance().getTexture(path));

  itemRenderer->setOffSetY(int(yOffSet));
  itemRenderer->setOffSetX(int(xOffSet));

  auto selectableComponent = std::make_shared<SelectableComponent>(
      *this, addedSoundWithSelectHook, mHoverChangeFocus,
      mNotSelectChangeFocus);
  addGenericComponent(selectableComponent);
}

//
// LevelEditButton::LevelEditButton() {}
//
// LevelEditButton::~LevelEditButton() {}
//
// void LevelEditButton::startUp(std::string imagePath, int x, int y, int w,
//                              int h) {
//  texture = ResourceManager::getInstance().getTexture(imagePath);
//
//  texture_dest.w = w;
//  texture_dest.h = h;
//  texture_dest.x = x;
//  texture_dest.y = y;
//
//  texture_outline.w = w + 10;
//  texture_outline.h = h + 10;
//  texture_outline.x = x - 5;
//  texture_outline.y = y - 5;
//
//  originalYPos = y;
//  clickFactor = y + CLICK_FACTOR_MOVEMENT;
//}
//
// void LevelEditButton::shutDown() {}
//
// void LevelEditButton::isClicked() {
//  isSelected = false;
//
//  // LevelEditButton Click sound.
//  Mix_PlayChannel(
//      1, ResourceManager::getInstance().getChunk(BUTTON_CLICK_SOUND), 0);
//}
//
// void LevelEditButton::update(Mouse *mouse) {
//  if (SDL_HasIntersection(&texture_dest, &mouse->point)) {
//    isSelected = true;
//    texture_dest.y = clickFactor;
//  } else {
//    isSelected = false;
//    texture_dest.y = originalYPos;
//  }
//}
//
// void LevelEditButton::render(SDL_Renderer *renderer) {
//  if (isSelected) {
//    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//    SDL_RenderFillRect(renderer, &texture_outline);
//    SDL_RenderDrawRect(renderer, &texture_outline);
//    SDL_RenderCopy(renderer, texture, NULL, &texture_dest);
//  } else {
//    SDL_RenderCopy(renderer, texture, NULL, &texture_dest);
//  }
//}
//
// bool LevelEditButton::IsSelected() const { return isSelected; }
