#ifndef TEXTURE_RENDER_COMP_HPP
#define TEXTURE_RENDER_COMP_HPP

#include <SDL.h>
#include "base/RenderComponent.hpp"
#include <vector>
#include <memory>

/**
 * @brief Component for rendering a texture.
 */
class TextureRenderComponent : public RenderComponent
{

public:
  enum RenderMode {
    WHOLE_WIDTH,
    QUERY
  };


  explicit TextureRenderComponent(GameObject &gameObject);
  TextureRenderComponent(GameObject &gameObject,
                         std::vector<std::shared_ptr<TextureRenderComponent>> otherRenderComponents);
  inline void setTexture(SDL_Texture *texture) { texture_ = texture; }
  inline void setFlip(bool flip) { flip_ = flip; }
  inline void setCrop(SDL_Rect crop) {crop_ = crop;}
  inline void setOffSetX(int x) {xOffset_ = x;}
  inline void setOffSetY(int y) {yOffset_ = y;}
  inline void setRenderMode(RenderMode mode) {renderMode_ = mode;}

  inline const std::vector<std::shared_ptr<TextureRenderComponent>> &GetPrevComponents() const {
    return prevComponents;
  };
  void render(SDL_Renderer *renderer) const;

private:
  SDL_Texture *texture_{nullptr};
  SDL_Rect crop_{0, 0, 0, 0};
  bool flip_{false};
  int xOffset_{0};
  int yOffset_{0};
  RenderMode renderMode_{WHOLE_WIDTH};

  std::vector<std::shared_ptr<TextureRenderComponent>> prevComponents{};
};

#endif // TEXTURE_RENDER_COMP_HPP