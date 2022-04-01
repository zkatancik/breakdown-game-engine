#ifndef GRID_RENDER_COMPONENT
#define GRID_RENDER_COMPONENT

#include <SDL.h>

#include <iostream>
#include <vector>

#include "base/GameObject.hpp"
#include "base/RenderComponent.hpp"
#include "base/TinyMath.hpp"

class GridRenderComponent : public RenderComponent {
 public:
  GridRenderComponent(GameObject& gameObject, float size, int xsz, int ysz)
      : RenderComponent(gameObject), mSize(size), mXsz(xsz), mYsz(ysz) {
    for (int ii = 0; ii < mXsz; ++ii) {
      gridRects.push_back(std::vector<SDL_Rect>());
      for (int jj = 0; jj < mYsz; ++jj) {
        SDL_Rect drawRect = {int(gameObject.x() + ii * mSize),
                             int(gameObject.y() + jj * mSize), int(mSize),
                             int(mSize)};
        gridRects[ii].push_back(drawRect);
      }
    }
  }

  virtual void render(SDL_Renderer* renderer) const override {
    SDL_Rect mousePos;
    mousePos.w = 1;
    mousePos.h = 1;
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xFF);
    for (int ii = 0; ii < mXsz; ++ii) {
      for (int jj = 0; jj < mYsz; ++jj) {
        SDL_Rect drawRect = gridRects[ii][jj];
        if (SDL_HasIntersection(&drawRect, &mousePos)) {
          // EditorUIManager::getInstance().getPathMap();
          SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

        } else {
          SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xFF);
        }
        SDL_RenderDrawRect(renderer, &drawRect);
      }
    }
  }

  virtual inline Vector2D<int> getGridCoords() {
    SDL_Rect mousePos;
    mousePos.w = 1;
    mousePos.h = 1;
    Vector2D<int> gridCoords{-1, -1};
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    for (int ii = 0; ii < mXsz; ++ii) {
      for (int jj = 0; jj < mYsz; ++jj) {
        SDL_Rect drawRect = gridRects[ii][jj];
        if (SDL_HasIntersection(&drawRect, &mousePos)) {
          gridCoords.x = jj;
          gridCoords.y = ii;
        }
      }
    }
    return gridCoords;
  }

 private:
  const float mSize;
  const int mXsz, mYsz;

  std::vector<std::vector<SDL_Rect>> gridRects;
};

#endif