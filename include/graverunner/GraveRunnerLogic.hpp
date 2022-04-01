#ifndef GRAVE_RUNNER_LOGIC_HPP
#define GRAVE_RUNNER_LOGIC_HPP
#include "base/SDLProgramLogic.hpp"
#include "base/PhysicsManager.hpp"
#include "graverunner/GameManager.hpp"
#include "graverunner/UIManager.hpp"

/**
 * @brief Contains Subsystem management for the GraveRunner game.
 */
class GraveRunnerLogic : public SDLProgramLogic {
 public:
  GraveRunnerLogic() = default;
  GraveRunnerLogic(GraveRunnerLogic const&) = delete; // Avoid copy constructor.
  void operator=(GraveRunnerLogic const&) = delete; // Don't allow copy assignment.

  void startUp(SDL_Renderer* gRender, int width, int height) override {
    PhysicsManager::getInstance().startUp();
    GameManager::getInstance().startUp(width, height);
    UIManager::getInstance().startUp(width, height);
  }

  void shutDown() override {
    PhysicsManager::getInstance().shutDown();
    UIManager::getInstance().shutDown();
    GameManager::getInstance().shutDown();
  }

  void update() override {
    GameManager::getInstance().update();
    UIManager::getInstance().update();
  }

  void checkButtons() override {
    UIManager::getInstance().checkButtons();
  }

  void render(SDL_Renderer* renderer) override {
    GameManager::getInstance().render(renderer);
    UIManager::getInstance().render(renderer);
  }
};

#endif