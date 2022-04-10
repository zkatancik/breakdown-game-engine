#include "base/RectangleRenderComponent.hpp"

#include <assert.h>

#include <utility>

#include "base/GameObject.hpp"
#include "base/TextureRenderComponent.hpp"

RectangleRenderComponent::RectangleRenderComponent(int red, int green, int blue,
                                                   GameObject &gameObject)
    : RenderComponent(gameObject), red_(red), green_(green), blue_(blue) {
  rect_.w = int(gameObject.w());
  rect_.h = int(gameObject.h());
  rect_.x = int(gameObject.x());
  rect_.y = int(gameObject.y());
}

void RectangleRenderComponent::render(SDL_Renderer *renderer) const {
  SDL_SetRenderDrawColor(renderer, red_, green_, blue_, 255);
  if (!flip_) {
    SDL_RenderFillRect(renderer, &rect_);
    SDL_RenderDrawRect(renderer, &rect_);
  }
}