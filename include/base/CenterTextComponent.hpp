#ifndef CENTER_TEXT_COMPONENT_HPP
#define CENTER_TEXT_COMPONENT_HPP
#include "base/GameObject.hpp"
#include "base/GenericComponent.hpp"
#include "base/ResourceManager.hpp"
#include "base/TextComponent.hpp"
#include "base/TextureRenderComponent.hpp"

/**
 * @brief Centers the textComponent to the middle of the object's rectangle.
 * Assumes the object has 2 TextureRenderComponents.
 */
class CenterTextComponent : public GenericComponent {
 public:
  CenterTextComponent(
      GameObject &gameObject,
      std::shared_ptr<TextureRenderComponent> textRenderComponent, int x,
      int y);

  void update(Level &level) override;

 private:
  std::shared_ptr<TextureRenderComponent> mTextRenderComponent;
  GameObject *mGameObject;
  int mX;
  int mY;
};

#endif