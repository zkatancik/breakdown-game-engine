#ifndef GRAVE_RUNNER_LOGIC_HPP
#define GRAVE_RUNNER_LOGIC_HPP
#include "base/SDLProgramLogic.hpp"
#include "base/PhysicsManager.hpp"
#include "graverunner/GameManager.hpp"
#include "graverunner/UIManager.hpp"
#include "graverunner/GraveRunnerLevel.hpp"
#include "graverunner/Mouse.hpp"
#include "graverunner/Button.hpp"
#include <iostream>

/**
 * @brief Contains Subsystem management for the GraveRunner game.
 */
class GraveRunnerLogic : public SDLProgramLogic {
 public:
  GraveRunnerLogic() = default;
  explicit GraveRunnerLogic(std::string  appName) : SDLProgramLogic(std::move(appName)) {};
  GraveRunnerLogic(GraveRunnerLogic const&) = delete; // Avoid copy constructor.
  void operator=(GraveRunnerLogic const&) = delete; // Don't allow copy assignment.

  void startUp(SDL_Renderer* gRender, int width, int height) override;

  void shutDown() override;

  void update() override {
    GameManager::getInstance().update();
    UIManager::getInstance().update();
  }

  bool quit() override {return mQuit;}

  void checkButtons() {
    UIManager::getInstance().checkButtons();
  }

  void render(SDL_Renderer* renderer) override {
    GameManager::getInstance().render(renderer);
    UIManager::getInstance().render(renderer);
  }
 private:
  bool mQuit{false};
};

#endif