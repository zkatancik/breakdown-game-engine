#include "base/GridObject.hpp"

#include <utility>

#include "base/GenericComponent.hpp"
#include "base/Tag.hpp"

//! \brief A Generic component that handles updates for the Grid
class GridComponent : public GenericComponent {
 public:
  GridComponent(GameObject& gameObject,
                std::vector<std::vector<SDL_Rect>>& rectGrid)
      : GenericComponent(gameObject),
        mGrid(rectGrid){};

  std::tuple<int, int, int, int> getMouseGridCoords() {
    SDL_Rect mousePos;
    mousePos.w = 1;
    mousePos.h = 1;
    std::tuple<int, int, int, int> gridCoords{-1, -1, -1, -1};
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    for (size_t ii = 0; ii < mGrid.size(); ++ii) {
      for (size_t jj = 0; jj < mGrid[ii].size(); ++jj) {
        SDL_Rect drawRect = mGrid[ii][jj];
        if (SDL_HasIntersection(&drawRect, &mousePos)) {
          std::get<0>(gridCoords) = jj;
          std::get<1>(gridCoords) = ii;
        }
      }
    }

    std::get<2>(gridCoords) = mousePos.x;
    std::get<3>(gridCoords) = mousePos.y;

    return gridCoords;
  }

  void update(Level& level) override {
    std::tuple<int, int, int, int> mouseGridLocation = getMouseGridCoords();
    bool isLeftMousePressed =
        InputManager::getInstance().isMouseKeyPressed(SDL_BUTTON_LEFT);
    if (isLeftMousePressed && std::get<0>(mouseGridLocation) != -1 &&
        std::get<1>(mouseGridLocation) != -1) {
      mCallBack(std::get<1>(mouseGridLocation), std::get<0>(mouseGridLocation),
                std::get<3>(mouseGridLocation), std::get<2>(mouseGridLocation));
    }
  }

  void setGridCallback(std::function<void(int, int, int, int)> gridCallBack) {mCallBack = std::move(gridCallBack);}

 private:
  std::function<void(int, int, int, int)> mCallBack;
  std::vector<std::vector<SDL_Rect>> mGrid;
};

GridObject::GridObject(Level& level, float xPos, float yPos, int numX, int numY,
                       int xsz, int ysz,
                       std::string currentlySelected)
    : GameObject(level, xPos, yPos, numX * xsz, numY * ysz, BaseGridTag) {
  for (int ii = 0; ii < numX; ++ii) {
    gridRects.push_back(std::vector<SDL_Rect>());
    for (int jj = 0; jj < numY; ++jj) {
      SDL_Rect drawRect = {int(x() + ii * xsz), int(y() + jj * ysz), int(xsz),
                           int(ysz)};
      gridRects[ii].push_back(drawRect);
    }
  }
  auto gridComponent =
      std::make_shared<GridComponent>(*this, gridRects);
  addGenericComponent(gridComponent);
  mGridRenderComponent = std::make_shared<GridRenderPreviewComponent>(
      *this, gridRects, currentlySelected);
  setRenderComponent(mGridRenderComponent);
}

void GridObject::setGridCallBack(std::function<void(int, int, int, int)> gridCallBack) {
  getGenericComponent<GridComponent>()->setGridCallback(std::move(gridCallBack));
}

void GridObject::setCurrentlySelected(std::string currentlySelected) {
  mGridRenderComponent->setCurrentlySelected(std::move(currentlySelected));
}
