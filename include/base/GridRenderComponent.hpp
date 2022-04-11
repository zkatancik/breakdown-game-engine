#ifndef GRID_RENDER_COMPONENT
#define GRID_RENDER_COMPONENT

#include <SDL.h>

#include <iostream>
#include <vector>

#include "base/GameObject.hpp"
#include "base/RenderComponent.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/TinyMath.hpp"

class GridRenderComponent : public RenderComponent {
 public:
  GridRenderComponent(GameObject& gameObject, float xSize, float ySize, int xsz,
                      int ysz)
      : RenderComponent(gameObject),
        mXSize(xSize),
        mYSize(ySize),
        mXsz(xsz),
        mYsz(ysz) {
    for (int ii = 0; ii < mXsz; ++ii) {
      gridRects.push_back(std::vector<SDL_Rect>());
      for (int jj = 0; jj < mYsz; ++jj) {
        SDL_Rect drawRect = {int(gameObject.x() + ii * mXSize),
                             int(gameObject.y() + jj * mYSize), int(mXSize),
                             int(mYSize)};
        gridRects[ii].push_back(drawRect);
      }
    }
    // item = std::make_shared<GameObject>(*this, 0, 0, width, height, 44);
    // itemRenderer = std::make_shared<TextureRenderComponent>(*item);
    // itemRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
    // background->setRenderComponent(itemRenderer);
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
          // itemRenderer->setTexture(ResourceManager::getInstance().getTexture(
          //     "Graverunner/graveyardtiles/menubg.jpg"));

          // addObject(item);
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

  inline void setCurrentlySelectedPath(std::string currentlySelectedPath) {
    mCurrentlySelectedPath = currentlySelectedPath;
  }

 private:
  const float mXSize, mYSize;
  const int mXsz, mYsz;

  std::vector<std::vector<SDL_Rect>> gridRects;
  // std::shared_ptr<TextureRenderComponent> itemRenderer;
  // std::make_shared<GameObject> item;
  std::string mCurrentlySelectedPath;
};

#endif