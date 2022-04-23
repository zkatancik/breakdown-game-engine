#ifndef RECTANGLE_RENDER_COMP_HPP
#define RECTANGLE_RENDER_COMP_HPP

#include <SDL.h>

#include <memory>
#include <vector>

#include "base/RenderComponent.hpp"

/**
 * @brief Component for rendering a texture.
 */
class RectangleRenderComponent : public RenderComponent {
 public:
  RectangleRenderComponent(int red, int green, int blue,
                           GameObject &gameObject);

  inline void setFlip(bool flip) { flip_ = flip; }

  inline void setRect(const SDL_Rect &rect) { rect_ = rect; }

  void render(SDL_Renderer *renderer) const;

 private:
  SDL_Rect rect_{0, 0, 0, 0};
  int red_;
  int green_;
  int blue_;
  bool flip_{false};
};

#endif  // TEXTURE_RENDER_COMP_HPP