#ifndef BASE_RANDOM_WALK_COMPONENT
#define BASE_RANDOM_WALK_COMPONENT

#include <cmath>
#include <utility>
#include <vector>
#include <algorithm>

#include "base/GenericComponent.hpp"
#include "base/TinyMath.hpp"

//! \brief A component that causes its game object to patrol back and forth.
class RandomWalkComponent : public GenericComponent {
 public:
  RandomWalkComponent(GameObject& gameObject, std::vector<std::vector<bool>> pathGrid,
    Vector2D<int> targetPosition, Vector2D<int> blockSize, float speed);

  virtual void update(Level& level);

  bool GetDirection();

 private:
  
  bool InBounds(int x, int y);

  const float epsilon = 1.5;

  std::vector<std::vector<bool>> pathGrid;
  Vector2D<int> targetPosition;
  std::vector<Vector2D<int>> prevGridPositions;
  Vector2D<int> nextGridPosition;
  Vector2D<int> blockSize;
  size_t currIter;
  float speed;
};

#endif
