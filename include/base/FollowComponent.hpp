#ifndef BASE_FOLLOW_COMPONENT
#define BASE_FOLLOW_COMPONENT

#include <cmath>
#include <utility>
#include <vector>

#include "base/GenericComponent.hpp"
#include "graverunner/Jack.hpp"

//! \brief A component that causes its game object to patrol back and forth, till player is detected and follow if detected.
class FollowComponent : public GenericComponent {
 public:
  FollowComponent(GameObject& gameObject, std::vector<float> Xs,
                  std::vector<float> Ys, float speed, std::shared_ptr<Jack> j);

  virtual void update(Level& level);

  bool GetDirection();

 private:
  
  const int mGravityForce = 50000;

  std::vector<float> Xs;
  std::vector<float> Ys;
  size_t currIter;
  float speed;
  std::shared_ptr<Jack> jack;
};

#endif
