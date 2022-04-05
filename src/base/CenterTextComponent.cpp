#include "base/CenterTextComponent.hpp"

#include <utility>
CenterTextComponent::CenterTextComponent(
    GameObject &gameObject,
    std::shared_ptr<TextureRenderComponent> textRenderComponent, int x, int y)
    : GenericComponent(gameObject),
      mTextRenderComponent(std::move(textRenderComponent)),
      mGameObject(&gameObject),
      mX(x),
      mY(y) {}

void CenterTextComponent::update(Level &level) {
  int textW, textH;
  SDL_QueryTexture(mTextRenderComponent->GetTexture(), nullptr, nullptr, &textW,
                   &textH);
  mTextRenderComponent->setOffSetX(int((getGameObject().w() - textW) / 2));
  mTextRenderComponent->setOffSetY(int(30));
  mGameObject->setW(textW + 70);
  mGameObject->setH(textH + 70);
  int newX = (mX / 2) - (mGameObject->w() / 2);
  mGameObject->setX(newX);
}
