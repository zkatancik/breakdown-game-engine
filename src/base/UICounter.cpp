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
        "TD2D/Sprites/TD2D/Sprites/Editor/Next.png" : "TD2D/Sprites/TD2D/Sprites/Editor/Prev.png"));

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


UICounter::UICounter(Level &level, float x, float y, int minValue, int maxValue) : Collection(level) {
  // Add the text field
  auto counterValue = std::make_shared<GameObject>(level, x + 20, y, 32, 32, BaseTextTag);
  auto textRenderer = std::make_shared<TextureRenderComponent>(*counterValue);

  textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  counterValue->setRenderComponent(textRenderer);
  auto textComponent = std::make_shared<TextComponent>(
      *counterValue, "", 32, "Graverunner/fonts/GADAQUALI.ttf",
      textRenderer);
  counterValue->addGenericComponent(textComponent);
  auto gameVariableComponent =
  std::make_shared<GameVariableComponent<int>>(*counterValue, minValue);
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
  auto decrementButton = std::make_shared<UICounterButton>(level, x, y, UICounterButton::DECREMENT,
                                                           [counterVariable = std::weak_ptr(gameVariableComponent)] {
    auto c = counterVariable.lock();
    c->setVariable(c->getVariable() - 1);
  });
  // Add increment button
  auto incrementButton = std::make_shared<UICounterButton>(level, x, y, UICounterButton::INCREMENT,
                                                           [counterVariable = std::weak_ptr(gameVariableComponent)] {
                                                             auto c = counterVariable.lock();
                                                             c->setVariable(c->getVariable() + 1);
                                                           });
  // Add everything to the level + collection list
  mCounterValue = counterValue->weak_from_this();
  addGameObject(counterValue);
  addGameObject(decrementButton);
  addGameObject(incrementButton);

}
