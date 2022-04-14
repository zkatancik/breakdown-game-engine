#ifndef BASE_RENDER_COMPONENT
#define BASE_RENDER_COMPONENT

#include <SDL.h>

#include "base/Component.hpp"

//! \brief A component that handles rendering.
class RenderComponent : public Component {
 public:
  RenderComponent(GameObject &gameObject);

  /**
   * @copydoc Component::render
   */
  virtual void render(SDL_Renderer *renderer) const = 0;  //!< Do the render.
  virtual void setTexture(SDL_Texture *texture){};
};

#endif
