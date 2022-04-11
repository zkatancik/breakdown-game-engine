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
  GridRenderComponent(Level& level, GameObject& gameObject, float xSize,
                      float ySize, int xsz, int ysz)
      : RenderComponent(gameObject),
        mLevel(level),
        mXSize(xSize),
        mYSize(ySize),
        mXsz(xsz),
        mYsz(ysz) {
    for (int ii = 0; ii < mXsz; ++ii) {
      gridRects.push_back(std::vector<SDL_Rect>());
      gridObjs.push_back(std::vector<std::shared_ptr<GameObject>>());
      for (int jj = 0; jj < mYsz; ++jj) {
        SDL_Rect drawRect = {int(gameObject.x() + ii * mXSize),
                             int(gameObject.y() + jj * mYSize), int(mXSize),
                             int(mYSize)};
        std::shared_ptr<GameObject> rectObj = std::make_shared<GameObject>(
            mLevel, int(gameObject.x() + ii * mXSize),
            int(gameObject.y() + jj * mYSize), int(mXSize), int(mYSize), 88);

        mItemRenderer = std::make_shared<TextureRenderComponent>(*rectObj);

        mItemRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);

        rectObj->setRenderComponent(mItemRenderer);

        // mItemRenderer->setTexture(nullptr);

        auto mHoverChangeFocus = [&]() {
          mItemRenderer->setTexture(ResourceManager::getInstance().getTexture(
              mCurrentlySelectedPath));
        };
        auto mNotSelectChangeFocus = [&]() {
          mItemRenderer->setTexture(nullptr);
        };

        auto addedSoundWithSelectHook = [&]() {
          Mix_PlayChannel(
              1, ResourceManager::getInstance().getChunk(mSoundPath), 0);
          std::cout << getGridCoords() << std::endl;
        };

        auto selectableComponent = std::make_shared<SelectableComponent>(
            *rectObj, addedSoundWithSelectHook, mHoverChangeFocus,
            mNotSelectChangeFocus);

        std::cout << selectableComponent << std::endl;

        rectObj->addGenericComponent(selectableComponent);

        mLevel.addObject(rectObj);
        gridRects[ii].push_back(drawRect);
        gridObjs[ii].push_back(rectObj);
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

  inline void setCurrentlySelectedPath(std::string currentlySelectedPath) {
    mCurrentlySelectedPath = currentlySelectedPath;
  }

 private:
  Level& mLevel;
  const float mXSize, mYSize;
  const int mXsz, mYsz;
  std::string mSoundPath = "2DBreakout/SFX/ButtonClick_SFX.wav";

  std::vector<std::vector<SDL_Rect>> gridRects;
  std::vector<std::vector<std::shared_ptr<GameObject>>> gridObjs;
  std::shared_ptr<TextureRenderComponent> mItemRenderer;
  std::string mCurrentlySelectedPath{nullptr};
};

#endif