#ifndef BASE_REMOVE_ON_COLLIDE_COMPONENT
#define BASE_REMOVE_ON_COLLIDE_COMPONENT

#include "base/GenericComponent.hpp"

//! \brief A component that removes a game object (of a given tag) on collision.
class RemoveOnCollideComponent : public GenericComponent {
 public:
  RemoveOnCollideComponent(GameObject& gameObject, int tag);

  /**
   * @brief Removes game object when it collides.
   * 
   * @param level overall level data
   * @param obj the obj we are checking collision with
   */
  virtual void collision(Level& level,
                         std::shared_ptr<GameObject> obj) override;

  /**
   * @brief Has this object collided with another.
   */
  inline bool getHasCollided() const { return hasCollided; }

 private:
  int mTag;
  bool hasCollided{false};
};

#endif
