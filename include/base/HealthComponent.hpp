#ifndef HEALTH_COMPONENT_HPP
#define HEALTH_COMPONENT_HPP

#include "base/GenericComponent.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"
#include <functional>
#include <map>

//! \brief A health component that remove its object once it reaches zero.
class HealthComponent: public GenericComponent {
 public:
  HealthComponent(GameObject& gameObject, int health);

  /**
   * @brief Updates this health component, does either the onDeath callback or
   * the onUpdate callback as applicable. Also removes the game object
   * automatically once health drops to zero or below.
   *
   * @param level level information
   */
  void update(Level &level) override;

  void collision(Level &level, std::shared_ptr<GameObject> obj) override;

  void setCallbackAtDeath(const std::function<void(void)> &callbackAtDeath);
  void setCallbackAtUpdate(const std::function<void(int)> &callbackAtUpdate);

  void addHealthModifier(int tag, int healthIncrementVal);
  int getHealth() const {return mHealth;}

 private:
  int mHealth{1};
  std::map<int, int> mHealthModifiers{};
  std::function<void(void)> mCallbackAtDeath{[]{}};
  std::function<void(int)> mCallbackAtUpdate;
};

#endif