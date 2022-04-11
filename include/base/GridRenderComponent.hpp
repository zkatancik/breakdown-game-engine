#ifndef GRID_RENDER_COMPONENT
#define GRID_RENDER_COMPONENT

#include <SDL.h>

#include <iostream>
#include <vector>

#include "base/GameObject.hpp"
#include "base/Level.hpp"
#include "base/RenderComponent.hpp"
#include "base/ResourceManager.hpp"
#include "base/SelectableComponent.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/TinyMath.hpp"

class GridRenderComponent : public RenderComponent {
 public:
  GridRenderComponent(GameObject& gameObject, std::vector<std::vector<SDL_Rect>>& gridRects)
      : RenderComponent(gameObject),
      mGridRects(gridRects) {};

  virtual void render(SDL_Renderer* renderer) const override {
    SDL_Rect mousePos;
    mousePos.w = 1;
    mousePos.h = 1;
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xFF);
    for (int ii = 0; ii < mGridRects.size(); ++ii) {
      for (int jj = 0; jj < mGridRects[ii].size(); ++jj) {
        SDL_Rect drawRect = mGridRects[ii][jj];
        if (SDL_HasIntersection(&drawRect, &mousePos)) {
          SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        } else {
          SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xFF);
        }
        SDL_RenderDrawRect(renderer, &drawRect);
      }
    }
  }

 private:
  std::vector<std::vector<SDL_Rect>> mGridRects;
};

#endif