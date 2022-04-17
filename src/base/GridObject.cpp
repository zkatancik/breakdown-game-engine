#include "base/GridObject.hpp"

#include <utility>

#include "base/GenericComponent.hpp"
#include "base/Tag.hpp"

//! \brief A Generic component that handles updates for the Grid
class GridComponent : public GenericComponent {
 public:
  GridComponent(GameObject& gameObject,
                std::vector<std::vector<SDL_Rect>>& rectGrid,
                std::function<void(int, int)> callback)
      : GenericComponent(gameObject),
        mGrid(rectGrid),
        mCallBack(std::move(callback)){};

  std::pair<int, int> getMouseGridCoords() {
    SDL_Rect mousePos;
    mousePos.w = 1;
    mousePos.h = 1;
    std::pair<int, int> gridCoords{-1, -1};
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    for (int ii = 0; ii < mGrid.size(); ++ii) {
      for (int jj = 0; jj < mGrid[ii].size(); ++jj) {
        SDL_Rect drawRect = mGrid[ii][jj];
        if (SDL_HasIntersection(&drawRect, &mousePos)) {
          gridCoords.first = jj;
          gridCoords.second = ii;
        }
      }
    }
    return gridCoords;
  }

  void update(Level& level) override {
    std::pair<int, int> mouseGridLocation = getMouseGridCoords();
    bool isLeftMousePressed =
        InputManager::getInstance().isMouseKeyPressed(SDL_BUTTON_LEFT);
    if (isLeftMousePressed && mouseGridLocation.first != -1 &&
        mouseGridLocation.second != -1) {
      mCallBack(mouseGridLocation.first, mouseGridLocation.second);
    }
  }

 private:
  std::function<void(int, int)> mCallBack;
  std::vector<std::vector<SDL_Rect>> mGrid;
};

GridObject::GridObject(Level& level, float xPos, float yPos, int numX, int numY,
                       int xsz, int ysz,
                       std::function<void(int, int)> gridCallBack,
                       std::string currentlySelected)
    : GameObject(level, xPos, yPos, numX * xsz, numY * ysz, BaseGridTag) {
  for (int ii = 0; ii < numX; ++ii) {
    gridRects.push_back(std::vector<SDL_Rect>());
    for (int jj = 0; jj < numY; ++jj) {
      SDL_Rect drawRect = {int(x() + ii * xsz), int(y() + jj * ysz), int(xsz),
                           int(ysz)};
      gridRects[ii].push_back(drawRect);


//      auto itemRenderer = std::make_shared<TextureRenderComponent>(*rectObj);
//      itemRenderer->setRenderMode(
//          TextureRenderComponent::RenderMode::CUSTOM_WIDTH);
//      itemRenderer->setCustomW(64);
//      itemRenderer->setCustomH(64);
//      rectObj->setRenderComponent(itemRenderer);
//      level.addObject(rectObj);
//
//      gridObjs[ii].push_back(rectObj);
      // }
    }
  }
  auto gridComponent =
      std::make_shared<GridComponent>(*this, gridRects, gridCallBack);
  addGenericComponent(gridComponent);
  mGridRenderComponent = std::make_shared<GridRenderPreviewComponent>(*this, gridRects, currentlySelected);
  setRenderComponent(mGridRenderComponent);
}

void GridObject::setCurrentlySelected(std::string currentlySelected) {
  mGridRenderComponent->setCurrentlySelected(currentlySelected);
}
