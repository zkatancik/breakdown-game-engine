#include <base/TextureRenderComponent.hpp>
#include "custom/LevelTimer.hpp"
#include "base/TextComponent.hpp"
#include "base/GameVariableComponent.hpp"
#include "base/CounterComponent.hpp"

TowerDefenseLevelTimer::TowerDefenseLevelTimer(Level &level, float x, float y, int sec,
                                               std::function<void(void)> callBackWhenDone,
                                               const std::string&  timerLabel) :
                                               GameObject(level, x, y, 0, 0, hash("TDTimerTag")) {
  // Text message render component
  auto textRenderer = std::make_shared<TextureRenderComponent>(*this);
  textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  setRenderComponent(textRenderer);
  // Text Component for rendering the time on screen
  // TODO- use a font from TD2D (and/or move one from another game)
  auto textComponent = std::make_shared<TextComponent>(*this, "", 32,
                                                       "Graverunner/fonts/GADAQUALI.ttf", textRenderer);
  addGenericComponent(textComponent);
  // Counter Component that keeps track of time
  auto counterComponent = std::make_shared<CounterComponent>(*this, sec * 60, 0, CounterComponent::DECREMENT);
  addGenericComponent(counterComponent);
  // Variable that keeps track of the time in seconds
  auto secondsVarComponent = std::make_shared<GameVariableComponent<int>>(*this, sec);
  addGenericComponent(secondsVarComponent);
  // Callback that updates the first updates the secondsVarComponent based on the counter and then updates the text
  // value seen on screen
  std::weak_ptr<TextComponent> textComponentWeak(textComponent);
  secondsVarComponent->setUpdateCallBack(
      [secondsVarComponent = std::weak_ptr(secondsVarComponent),
         textComponent = std::weak_ptr(textComponent),
         counterComponent = std::weak_ptr(counterComponent),
         callBackWhenDone = std::move(callBackWhenDone),
         timerLabel] {
        // Update variable based on counter
        secondsVarComponent.lock()->setVariable(counterComponent.lock()->getCounter() / 60);
        int minutes = secondsVarComponent.lock()->getVariable() / 60;
        int seconds = secondsVarComponent.lock()->getVariable() % 60;
        if (minutes == 0 && seconds == 0)
          callBackWhenDone();
        textComponent.lock()->SetMText(timerLabel + ": " +
        std::to_string(minutes) + ":" + std::to_string(seconds));
        std::cout << minutes << ": " << seconds << std::endl;
      });
}
