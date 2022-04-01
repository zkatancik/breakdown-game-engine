#ifndef BASE_PERFORM_HOOK_ON_COLLIDE_COMPONENT_HPP
#define BASE_PERFORM_HOOK_ON_COLLIDE_COMPONENT_HPP

#include "base/GenericComponent.hpp"
#include <functional>

//! \brief A component that performs a function on collision.
class PerformHookOnCollideComponent : public GenericComponent {
 public:
  PerformHookOnCollideComponent() = delete;

  PerformHookOnCollideComponent(GameObject& gameObject, int tag, std::function<void(Level&, std::shared_ptr<GameObject>)> f);

  /**
   * @brief Runs the function if collision is detected.
   * 
   * @param level overall level data
   * @param obj the obj we are checking collision with
   */
  virtual void collision(Level& level,
                         std::shared_ptr<GameObject> obj) override;

  /**
   * @brief Has the hook been performed (ie. have we collided)
   */
  inline bool getHasPerformedHook() const { return hasPerformedHook; }

 private:
  std::function<void(Level&, std::shared_ptr<GameObject>)> mHook;
  int mTag;
  bool hasPerformedHook{false};
};


#endif