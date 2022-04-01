#ifndef BASE_PATROL_COMPONENT
#define BASE_PATROL_COMPONENT

#include <cmath>
#include <utility>
#include <vector>

#include "base/GenericComponent.hpp"

//! \brief A component that causes its game object to patrol back and forth.
class PatrolComponent : public GenericComponent {
 public:
  PatrolComponent(GameObject& gameObject, std::vector<float> Xs,
                  std::vector<float> Ys, float speed);

  virtual void update(Level& level);

  bool GetDirection();

 private:
  std::vector<float> Xs;
  std::vector<float> Ys;
  size_t currIter;
  float speed;
};

#endif
