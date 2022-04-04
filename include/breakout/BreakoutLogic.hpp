#ifndef BREAKOUT_LOGIC_HPP
#define BREAKOUT_LOGIC_HPP
#include "base/SDLProgramLogic.hpp"
#include "base/PhysicsManager.hpp"
#include "breakout/GameManager.hpp"
#include "breakout/UIManager.hpp"
#include "breakout/BreakoutLevel.hpp"

/**
 * @brief Contains Subsystem management for the Breakout game.
 */
class BreakoutLogic : public SDLProgramLogic {
 public:
  BreakoutLogic() = default;
  explicit BreakoutLogic(std::string  appName) : SDLProgramLogic(std::move(appName)) {};
  BreakoutLogic(BreakoutLogic const&) = delete; // Avoid copy constructor.
  void operator=(BreakoutLogic const&) = delete; // Don't allow copy assignment.

  void startUp(SDL_Renderer* gRender, int width, int height) override {
    PhysicsManager::getInstance().startUp();
    mLevel = std::make_shared<BreakoutLevel>(width, height, BreakoutLevel::GameDifficulty::Easy, Language::ENGLISH);
    mLevel->initialize();
  }

  void shutDown() override {
    mLevel->finalize();
    PhysicsManager::getInstance().shutDown();
  }

  void update() override {
    mLevel->update();
    framerateModerator();
  }

  void render(SDL_Renderer* renderer) override {
    mLevel->render(renderer);
  }
 private:
  std::shared_ptr<Level> mLevel;

};

#endif