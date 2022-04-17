#ifndef GRID_RENDER_PREVIEW_COMPONENT
#define GRID_RENDER_PREVIEW_COMPONENT

#include <SDL.h>

#include <iostream>
#include <utility>
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
      std::string  currentlySelected) : RenderComponent(gameObject),
        mGridRects(gridRects),
        mCurrentlySelected(std::move(currentlySelected)) {
    mTextureView = std::make_shared<TextureRenderComponent>(gameObject);
    mTextureView->setTexture(ResourceManager::getInstance().getTexture(mCurrentlySelected));
    mTextureView->setRenderMode(TextureRenderComponent::CUSTOM_WIDTH);
    mTextureView->setCustomW(mGridRects[0][0].w);
    mTextureView->setCustomH(mGridRects[0][0].h);
  };

  virtual void render(SDL_Renderer* renderer) const override {
    SDL_Rect mousePos;
    mousePos.w = 1;
    mousePos.h = 1;
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xFF);
    for (size_t ii = 0; ii < mGridRects.size(); ++ii) {
      for (size_t jj = 0; jj < mGridRects[ii].size(); ++jj) {
        SDL_Rect drawRect = mGridRects[ii][jj];
        if (SDL_HasIntersection(&drawRect, &mousePos)) {
          if (mCurrentlySelected == "ERASE") {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
            SDL_RenderDrawRect(renderer, &drawRect);
          } else {
            mTextureView->setTexture(ResourceManager::getInstance().getTexture(mCurrentlySelected));
            mTextureView->setOffSetX(drawRect.x - int(getGameObject().x()));
            mTextureView->setOffSetY(drawRect.y - int(getGameObject().y()));
            mTextureView->render(renderer);
          }
        } else {
          mTextureView->setTexture(ResourceManager::getInstance().getTexture(
              "TD2D/Sprites/Tiles/Empty.png"));
          mTextureView->setOffSetX(drawRect.x - int(getGameObject().x()));
          mTextureView->setOffSetY(drawRect.y - int(getGameObject().y()));
          mTextureView->render(renderer);
        }
      }
    }
  }

  inline void setCurrentlySelected(std::string currentlySelected) {
    mCurrentlySelected = currentlySelected;
  }

 private:
  std::vector<std::vector<SDL_Rect>> mGridRects;
  std::string mCurrentlySelected{"TD2D/Sprites/Tiles/Empty.png"};
  std::shared_ptr<TextureRenderComponent> mTextureView;
};

#endif