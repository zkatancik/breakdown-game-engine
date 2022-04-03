#ifndef SELECTABLE_COMPONENT_HPP
#define SELECTABLE_COMPONENT_HPP
#include "base/GenericComponent.hpp"

//! \brief A component that performs a function when it is selected by Mouse
class SelectableComponent : public GenericComponent {
 public:
  explicit SelectableComponent(GameObject& gameObject);

  SelectableComponent(GameObject& gameObject, std::function<void(void)> onSelectHook);

  SelectableComponent(GameObject& gameObject, std::function<void(void)> onSelectHook,
                      std::function<void(void)> onHoverHook);

  void update(Level &level) override;

 private:
  std::function<void(Level&, std::shared_ptr<GameObject>)> mSelectHook;
  std::function<void(Level&, std::shared_ptr<GameObject>)> mHoverHook;
};

#endif