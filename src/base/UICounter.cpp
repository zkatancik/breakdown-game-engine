#include "base/UICounter.hpp"
#include "base/GameObject.hpp"
#include "base/Tag.hpp"
#include "base/SelectableComponent.hpp"
#include "base/GameVariableComponent.hpp"

class UICounterButton : public GameObject {
 public:
  enum CounterOp {DECREMENT, INCREMENT};
  UICounterButton(Level& level, float x, float y, CounterOp counterOp, std::function<void(void)> clickCallBack) : GameObject(level, x, y, 64, 32, BaseButtonTag) {
    // Load sprite sheet for the buttons
    auto buttonRenderer = std::make_shared<TextureRenderComponent>(*this);
    buttonRenderer->setTexture(ResourceManager::getInstance().getTexture(counterOp == INCREMENT ?
        "TD2D/Sprites/Editor/Next.png" : "TD2D/Sprites/Editor/Prev.png"));
    setRenderComponent(buttonRenderer);
    // Set event handlers for the SelectableComponent

    auto addedSoundWithSelectHook = [selectHook = std::move(clickCallBack)] {
      Mix_PlayChannel(
          1,
          ResourceManager::getInstance().getChunk("TD2D/Audio/Common/Click1.mp3"),
          0);
      selectHook();
    };
    auto selectableComponent = std::make_shared<SelectableComponent>(
        *this, addedSoundWithSelectHook);
    addGenericComponent(selectableComponent);
  }
};


UICounter::UICounter(Level &level, float x, float y, int currentValue, int minValue, int maxValue) : Collection(level) {
  // Add the text field
  auto counterValue = std::make_shared<GameObject>(level, x + 40, y, 32, 32, BaseTextTag);
  auto textRenderer = std::make_shared<TextureRenderComponent>(*counterValue);

  textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  counterValue->setRenderComponent(textRenderer);
  auto textComponent = std::make_shared<TextComponent>(
      *counterValue, std::to_string(currentValue), 32, "TD2D/Fonts/madera-tygra.ttf",
      textRenderer);
  counterValue->addGenericComponent(textComponent);
  auto gameVariableComponent =
  std::make_shared<GameVariableComponent<int>>(*counterValue, currentValue);
  counterValue->addGenericComponent(gameVariableComponent);
  std::weak_ptr<GameVariableComponent<int>> gameVariableComponentWeak(
      gameVariableComponent);
  std::weak_ptr<TextComponent> textComponentWeak(textComponent);
  gameVariableComponent->setUpdateCallBack(
      [gameVariableComponentWeak, textComponentWeak] {
        textComponentWeak.lock()->SetMText(
                std::to_string(gameVariableComponentWeak.lock()->getVariable()));
      });
  // Add decrement button
  auto decrementButton = std::make_shared<UICounterButton>(level, x - 40, y, UICounterButton::DECREMENT,
                                                           [counterVariable = std::weak_ptr(gameVariableComponent), minValue] {
    auto c = counterVariable.lock();
    if (c->getVariable() > minValue)
      c->setVariable(c->getVariable() - 1);
  });
  // Add increment button
  auto incrementButton = std::make_shared<UICounterButton>(level, x + 80, y, UICounterButton::INCREMENT,
                                                           [counterVariable = std::weak_ptr(gameVariableComponent), maxValue] {
                                                             auto c = counterVariable.lock();
                                                             if (c->getVariable() < maxValue)
                                                              c->setVariable(c->getVariable() + 1);
                                                           });
  // Add everything to the level + collection list
  mCounterValue = counterValue->weak_from_this();
  level.addObject(counterValue);
  level.addObject(decrementButton);
  level.addObject(incrementButton);
}
int UICounter::getCounterValue() {
  return mCounterValue.lock()->getGenericComponent<GameVariableComponent<int>>()->getVariable();
}
