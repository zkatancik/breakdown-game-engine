#ifndef GRID_RENDER_PREVIEW_COMPONENT
#define GRID_RENDER_PREVIEW_COMPONENT

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
#include "custom/LevelData.hpp"

class GridRenderPreviewComponent : public RenderComponent {
 public:
  GridRenderPreviewComponent(
      GameObject& gameObject, std::vector<std::vector<SDL_Rect>>& gridRects,
      std::vector<std::vector<std::shared_ptr<GameObject>>> gridObjs,
      std::string currentlySelected)
      : RenderComponent(gameObject),
        mGridRects(gridRects),
        mGridObjs(gridObjs),
        mCurrentlySelected(currentlySelected){};

  virtual void render(SDL_Renderer* renderer) const override {
    SDL_Rect mousePos;
    mousePos.w = 1;
    mousePos.h = 1;
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xFF);
    for (int ii = 0; ii < mGridRects.size(); ++ii) {
      for (int jj = 0; jj < mGridRects[ii].size(); ++jj) {
        SDL_Rect drawRect = mGridRects[ii][jj];
        std::shared_ptr<GameObject> rectObj = mGridObjs[ii][jj];
        if (SDL_HasIntersection(&drawRect, &mousePos)) {
          if (mCurrentlySelected == "ERASE") {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
            SDL_RenderDrawRect(renderer, &drawRect);
          } else {
            std::shared_ptr<RenderComponent> textComp =
                rectObj->renderComponent();
            textComp->setTexture(
                ResourceManager::getInstance().getTexture(mCurrentlySelected));
          }
        } else {
          std::shared_ptr<RenderComponent> textComp =
              rectObj->renderComponent();
          textComp->setTexture(ResourceManager::getInstance().getTexture(
              "TD2D/Sprites/Tiles/Empty.png"));
        }
      }
    }
  }

  inline void setCurrentlySelected(std::string currentlySelected) {
    mCurrentlySelected = currentlySelected;
  }

 private:
  std::vector<std::vector<SDL_Rect>> mGridRects;
  std::vector<std::vector<std::shared_ptr<GameObject>>> mGridObjs;
  std::string mCurrentlySelected{"TD2D/Sprites/Tiles/Empty.png"};
};

#endif