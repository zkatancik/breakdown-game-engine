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

  void update(Level & level) override; //!< Update the object.

  void collision(Level & level, std::shared_ptr<GameObject> obj) override;

  void setCallbackAtDeath(const std::function<void(void)> &callbackAtDeath);
  void addHealthModifier(int tag, int healthIncrementVal);
  int getHealth() const {return mHealth;}

 private:
  int mHealth{1};
  std::map<int, int> mHealthModifiers{};
  std::function<void(void)> mCallbackAtDeath{[]{}};
};

#endif