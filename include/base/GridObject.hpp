#ifndef BASE_GRID_OBJECT
#define BASE_GRID_OBJECT
#include "base/GameObject.hpp"
#include <functional>
#include "base/GridRenderComponent.hpp"


class GridObject : public GameObject {
 public:
  GridObject(Level &level,
             float xPos,
             float yPos,
             int numX,
             int numY,
             int xsz,
             int ysz, std::function<void(int, int)> gridCallBack);

 private:
  std::vector<std::vector<SDL_Rect>> gridRects;

};

#endif