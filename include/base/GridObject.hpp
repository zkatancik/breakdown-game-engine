#ifndef BASE_GRID_OBJECT
#define BASE_GRID_OBJECT
#include <functional>

#include "base/GameObject.hpp"
#include "base/GridRenderComponent.hpp"
#include "base/GridRenderPreviewComponent.hpp"

class GridObject : public GameObject {
 public:
  GridObject(Level &level, float xPos, float yPos, int numX, int numY, int xsz,
             int ysz, std::function<void(int, int)> gridCallBack,
             std::string currentlySelected = "TD2D/Sprites/Tiles/Empty.png");

  void setCurrentlySelected(std::string currentlySelected);

 private:
  std::vector<std::vector<SDL_Rect>> gridRects;
  std::vector<std::vector<std::shared_ptr<GameObject>>> gridObjs;
  std::shared_ptr<GridRenderPreviewComponent> mGridRenderComponent;
};

#endif