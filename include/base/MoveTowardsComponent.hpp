#ifndef BASE_MOVETOWARDS_COMPONENT
#define BASE_MOVETOWARDS_COMPONENT

#include <cmath>
#include <utility>
#include <vector>

#include "base/GenericComponent.hpp"
#include "base/TinyMath.hpp"

//! \brief A component that causes its game object to patrol back and forth.
class MoveTowardsComponent : public GenericComponent {
 public:
  MoveTowardsComponent(GameObject& gameObject, Vector2D<int> targetPosition, float speed);

  virtual void update(Level& level);

  bool GetDirection();

 private:
  Vector2D<int> targetPosition;
  size_t currIter;
  float speed;
};

#endif
