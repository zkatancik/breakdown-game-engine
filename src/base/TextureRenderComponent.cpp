#include <assert.h>
#include "base/GameObject.hpp"
#include "base/TextureRenderComponent.hpp"

TextureRenderComponent::TextureRenderComponent(GameObject &gameObject) : RenderComponent(gameObject) {}

void TextureRenderComponent::render(SDL_Renderer *renderer) const
{
  assert(texture_ != nullptr);
  const GameObject &gameObject = getGameObject();
  SDL_Rect fillRect = {int(gameObject.x()), int(gameObject.y()), int(gameObject.w()), int(gameObject.h())};
  SDL_RenderCopyEx(renderer, texture_, nullptr, &fillRect, 0, nullptr,
                   flip_ ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}