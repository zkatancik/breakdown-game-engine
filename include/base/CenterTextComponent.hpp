#ifndef CENTER_TEXT_COMPONENT_HPP
#define CENTER_TEXT_COMPONENT_HPP
#include "base/GenericComponent.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/TextComponent.hpp"
#include "base/ResourceManager.hpp"
#include "base/GameObject.hpp"

/**
 * @brief Centers the textComponent to the middle of the object's rectangle. Assumes the object has 2 TextureRenderComponents.
 */
class CenterTextComponent : public GenericComponent {
 public:
  CenterTextComponent(GameObject &gameObject,
                      std::shared_ptr<TextureRenderComponent> textRenderComponent);

  void update(Level & level) override;

 private:
  std::shared_ptr<TextureRenderComponent> mTextRenderComponent;
};


#endif