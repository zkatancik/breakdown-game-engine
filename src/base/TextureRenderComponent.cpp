#include <assert.h>

#include <utility>
#include "base/GameObject.hpp"
#include "base/TextureRenderComponent.hpp"

TextureRenderComponent::TextureRenderComponent(GameObject &gameObject) : RenderComponent(gameObject) {}

void TextureRenderComponent::render(SDL_Renderer *renderer) const
{
  for (const auto& comp : prevComponents) {
    comp->render(renderer);
  }
  assert(texture_ != nullptr);
  const GameObject &gameObject = getGameObject();
  SDL_Rect fillRect = {int(gameObject.x()) + xOffset_,
                       int(gameObject.y()) + yOffset_,
                       0, 0};
  switch (renderMode_) {
    case WHOLE_WIDTH:
      fillRect.w = int(gameObject.w());
      fillRect.h = int(gameObject.h());
      break;
    case QUERY:
      SDL_QueryTexture(texture_, nullptr, nullptr, &fillRect.w, &fillRect.h);
      break;
  }

  SDL_RenderCopyEx(renderer, texture_, SDL_RectEmpty(&crop_) ? nullptr : &crop_, &fillRect, 0, nullptr,
                   flip_ ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
TextureRenderComponent::TextureRenderComponent(GameObject &gameObject,
                                               std::vector<std::shared_ptr<TextureRenderComponent>>  otherRenderComponents) :
                                               RenderComponent(gameObject),
                                               prevComponents(std::move(otherRenderComponents))  {}