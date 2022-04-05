#include "base/CenterTextComponent.hpp"

#include <utility>
CenterTextComponent::CenterTextComponent(GameObject &gameObject,
                                         std::shared_ptr<TextureRenderComponent> textRenderComponent) : GenericComponent(gameObject),
                                         mTextRenderComponent(std::move(textRenderComponent)) {}

void CenterTextComponent::update(Level &level) {
  int textW, textH;
  SDL_QueryTexture(mTextRenderComponent->GetTexture(), nullptr, nullptr, &textW, &textH);
  mTextRenderComponent->setOffSetX(int((getGameObject().w() - textW) / 2));
  mTextRenderComponent->setOffSetY(int(30));
}

