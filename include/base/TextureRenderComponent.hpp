#ifndef TEXTURE_RENDER_COMP_HPP
#define TEXTURE_RENDER_COMP_HPP

#include <SDL.h>
#include "base/RenderComponent.hpp"

/**
 * @brief Component for rendering a texture.
 */
class TextureRenderComponent : public RenderComponent
{

public:
  TextureRenderComponent(GameObject &gameObject);
  inline void setTexture(SDL_Texture *texture) { texture_ = texture; }
  inline void setFlip(bool flip) { flip_ = flip; }
  void render(SDL_Renderer *renderer) const;

private:
  SDL_Texture *texture_{nullptr};
  bool flip_{false};
};

#endif // TEXTURE_RENDER_COMP_HPP