#ifndef GRAVE_RUNNER_LOGIC_HPP
#define GRAVE_RUNNER_LOGIC_HPP
#include <iostream>

#include "base/CenterTextComponent.hpp"
#include "base/PhysicsManager.hpp"
#include "base/SDLProgramLogic.hpp"
#include "graverunner/GraveRunnerButton.hpp"
#include "graverunner/GraveRunnerLevel.hpp"
#include "graverunner/Mouse.hpp"

/**
 * @brief Contains Subsystem management for the GraveRunner game.
 */
class GraveRunnerLogic : public SDLProgramLogic {
 public:
  GraveRunnerLogic() = default;
  explicit GraveRunnerLogic(std::string appName)
      : SDLProgramLogic(std::move(appName)){};
  GraveRunnerLogic(GraveRunnerLogic const&) =
      delete;  // Avoid copy constructor.
  void operator=(GraveRunnerLogic const&) =
      delete;  // Don't allow copy assignment.

  void startUp(SDL_Renderer* gRender, int width, int height) override;

  void shutDown() override;

  void update() override;

  bool quit() override { return mQuit; }

  void render(SDL_Renderer* renderer) override {
    mCurrentlyActiveLevel->render(renderer);
  }

 private:
  bool mQuit{false};
  std::shared_ptr<Level> mStartMenu{nullptr};
  std::shared_ptr<Level> mLanguageMenu{nullptr};
  std::shared_ptr<Level> mInstructionsMenu{nullptr};
  std::shared_ptr<Level> mLevelClearedMenu{nullptr};
  std::shared_ptr<Level> mLevelFailedMenu{nullptr};
  std::vector<std::shared_ptr<GraveRunnerLevel>> mGameLevels{nullptr, nullptr,
                                                             nullptr};
  std::shared_ptr<Level> mCurrentlyActiveLevel{
      nullptr};  //< The level that is currently being shown
  
  const static int NUM_LEVELS{3};
  int mCurrentlySelectedGameLevelIdx{0};  //< The index of the game level that
                                          // will start/is currently being played.

  void loadAllLevels(int width, int height);

  void createChangeLanguageLevel(int width, int height);

  void createInstructionsLevel(int width, int height);

  void createStartMenuLevel(int width, int height);

  void initializeLevelClearedMenu();

  void initializeLevelFailedMenu();

  void createTextMessageForLevel(const std::shared_ptr<Level>& level,
                                 const std::string& message, float x, float y,
                                 int fontSize = 64);

  inline bool isGameActive() {
    return (mCurrentlyActiveLevel ==
            std::dynamic_pointer_cast<Level>(
                mGameLevels[mCurrentlySelectedGameLevelIdx]));
  }
};

#endif