#ifndef GAME_VARIABLE_COMPONENT_HPP
#define GAME_VARIABLE_COMPONENT_HPP
#include "base/GenericComponent.hpp"
#include <functional>
#include <utility>

template <typename T>
class GameVariableComponent : public GenericComponent {
 public:
  GameVariableComponent(GameObject &gameObject,
                        T initValue) : GenericComponent(gameObject), mVal(initValue) {};

  inline void setUpdateCallBack(std::function<void(void)> f) {mUpdateCallback = std::move(f);}

  inline T getVariable() {return mVal;}

  inline void setVariable(T val) {mVal = val;}

  void update(Level & level) override {
    mUpdateCallback();
  };

 private:
  T mVal;
  std::function<void(void)> mUpdateCallback{[&]{}};
};


#endif