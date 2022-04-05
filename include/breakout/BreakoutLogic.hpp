#ifndef BREAKOUT_LOGIC_HPP
#define BREAKOUT_LOGIC_HPP
#include "base/SDLProgramLogic.hpp"
#include "base/PhysicsManager.hpp"
#include "breakout/BreakoutGameLevel.hpp"
#include "breakout/Mouse.hpp"
#include "breakout/Button.hpp"
#include <iostream>

/**
 * @brief Contains Subsystem management for the Breakout game.
 */
class BreakoutLogic : public SDLProgramLogic {
 public:
  BreakoutLogic() = default;
  explicit BreakoutLogic(std::string  appName) : SDLProgramLogic(std::move(appName)) {};
  BreakoutLogic(BreakoutLogic const&) = delete; // Avoid copy constructor.
  void operator=(BreakoutLogic const&) = delete; // Don't allow copy assignment.

  void startUp(SDL_Renderer* gRender, int width, int height) override;

  void shutDown() override;

  void update() override {
    mCurrentlyActiveLevel->update();
    std::cout << "is game active: " << isGameActive() << std::endl;
    framerateModerator();
  }

  void render(SDL_Renderer* renderer) override {
    mCurrentlyActiveLevel->render(renderer);
  }
 private:
  std::shared_ptr<Level> mStartMenu{nullptr};
  std::shared_ptr<Level> mLanguageMenu{nullptr};
  std::shared_ptr<Level> mDifficultyMenu{nullptr};
  std::vector<std::shared_ptr<BreakoutGameLevel>> mGameLevels{nullptr, nullptr, nullptr, nullptr};
  std::shared_ptr<Level> mCurrentlyActiveLevel{nullptr}; //< The level that is currently being shown
  int mCurrentlySelectedGameLevelIdx{0}; //< The index of the game level that will start/currently being played.
  BreakoutGameLevel::GameDifficulty mDifficulty{BreakoutGameLevel::Easy};

  void loadAllLevels(int width, int height);

  void createChangeDifficultyLevel(int width, int height);

  void createChangeLanguageLevel(int width, int height);

  void createStartMenuLevel(int width, int height);

  inline bool isGameActive() { return (mCurrentlyActiveLevel == std::dynamic_pointer_cast<Level>(mGameLevels[mCurrentlySelectedGameLevelIdx]));}

};

#endif