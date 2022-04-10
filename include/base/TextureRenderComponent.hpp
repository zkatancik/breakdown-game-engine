#ifndef TEXTURE_RENDER_COMP_HPP
#define TEXTURE_RENDER_COMP_HPP

#include <SDL.h>

#include <memory>
#include <vector>

#include "base/RectangleRenderComponent.hpp"
#include "base/RenderComponent.hpp"

/**
 * @brief Component for rendering a texture.
 */
class TextureRenderComponent : public RenderComponent {
 public:
  enum RenderMode {
    WHOLE_WIDTH,
    QUERY,
    CUSTOM_WIDTH,
  };

  explicit TextureRenderComponent(GameObject &gameObject);
  TextureRenderComponent(GameObject &gameObject,
                         std::vector<std::shared_ptr<TextureRenderComponent>>
                             otherRenderComponents);
  TextureRenderComponent(GameObject &gameObject,
                         std::vector<std::shared_ptr<RectangleRenderComponent>>
                             otherRectComponents);
  inline void setTexture(SDL_Texture *texture) { texture_ = texture; }
  SDL_Texture *GetTexture() const { return texture_; }
  inline void setFlip(bool flip) { flip_ = flip; }
  inline void setCrop(SDL_Rect crop) { crop_ = crop; }
  inline void setOffSetX(int x) { xOffset_ = x; }
  inline void setOffSetY(int y) { yOffset_ = y; }
  inline void setCustomW(int w) { customW_ = w; };
  inline void setCustomH(int h) { customH_ = h; };
  inline void setRenderMode(RenderMode mode) { renderMode_ = mode; }

  inline const std::vector<std::shared_ptr<TextureRenderComponent>>
      &GetPrevComponents() const {
    return prevComponents;
  };
  void render(SDL_Renderer *renderer) const;

 private:
  SDL_Texture *texture_{nullptr};
  SDL_Rect crop_{0, 0, 0, 0};
  bool flip_{false};
  int xOffset_{0};
  int yOffset_{0};
  int customH_{0};
  int customW_{0};
  RenderMode renderMode_{WHOLE_WIDTH};

  std::vector<std::shared_ptr<TextureRenderComponent>> prevComponents{};
  std::vector<std::shared_ptr<RectangleRenderComponent>> prevRects{};
};

#endif  // TEXTURE_RENDER_COMP_HPP