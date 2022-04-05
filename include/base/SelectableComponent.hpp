#ifndef SELECTABLE_COMPONENT_HPP
#define SELECTABLE_COMPONENT_HPP
#include "base/GenericComponent.hpp"
#include "functional"
#include "base/InputManager.hpp"

//! \brief A component that performs a function when it is selected by Mouse
class SelectableComponent : public GenericComponent {
 public:
  explicit SelectableComponent(GameObject& gameObject);

  SelectableComponent(GameObject& gameObject, std::function<void(void)> onSelectHook);

  SelectableComponent(GameObject& gameObject, std::function<void(void)> onSelectHook,
                      std::function<void(void)> onHoverHook);

  SelectableComponent(GameObject& gameObject, std::function<void(void)> onSelectHook,
                      std::function<void(void)> onHoverHook, std::function<void(void)> onNotSelectHook);

  void update(Level &level) override;

 private:
  std::function<void(void)> mSelectHook;
  std::function<void(void)> mHoverHook;
  std::function<void(void)> mNotSelectHook;
};

#endif