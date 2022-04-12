#ifndef BREAKOUT_LOGIC_HPP
#define BREAKOUT_LOGIC_HPP
#include "base/CenterTextComponent.hpp"
#include "base/PhysicsManager.hpp"
#include "base/SDLProgramLogic.hpp"
#include "breakout/BreakoutGameLevel.hpp"
#include "breakout/BreakoutButton.hpp"
#include "breakout/Mouse.hpp"

/**
 * @brief Contains Subsystem management for the Breakout game.
 */
class BreakoutLogic : public SDLProgramLogic {
 public:
  BreakoutLogic() = default;
  explicit BreakoutLogic(std::string appName)
      : SDLProgramLogic(std::move(appName)){};
  BreakoutLogic(BreakoutLogic const&) = delete;  // Avoid copy constructor.
  void operator=(BreakoutLogic const&) =
      delete;  // Don't allow copy assignment.

  void startUp(SDL_Renderer* gRender, int width, int height) override;

  void shutDown() override;

  void update() override;

  bool quit() override {return mQuite;}

  void render(SDL_Renderer* renderer) override {
    mCurrentlyActiveLevel->render(renderer);
  }

 private:
  bool mQuite{false};
  std::shared_ptr<Level> mStartMenu{nullptr};
  std::shared_ptr<Level> mLanguageMenu{nullptr};
  std::shared_ptr<Level> mDifficultyMenu{nullptr};
  std::shared_ptr<Level> mInstructionsMenu{nullptr};
  std::shared_ptr<Level> mLevelClearedMenu{nullptr};
  std::shared_ptr<Level> mLevelFailedMenu{nullptr};
  std::vector<std::shared_ptr<BreakoutGameLevel>> mGameLevels{nullptr, nullptr,
                                                              nullptr, nullptr};
  std::shared_ptr<Level> mCurrentlyActiveLevel{
      nullptr};  //< The level that is currently being shown
  static const int NUM_LEVELS = 4;
  int mCurrentlySelectedGameLevelIdx{0};  //< The index of the game level that
                                          //will start/currently being played.
  BreakoutGameLevel::GameDifficulty mDifficulty{BreakoutGameLevel::Easy};

  void loadAllLevels(int width, int height);

  void createChangeDifficultyLevel(int width, int height);

  void createChangeLanguageLevel(int width, int height);

  void createInstructionsLevel(int width, int height);

  void initializeLevelClearedMenu(int score);

  void initializeLevelFailedMenu(int score);

  void createStartMenuLevel(int width, int height);

  inline bool isGameActive() {
    return (mCurrentlyActiveLevel ==
            std::dynamic_pointer_cast<Level>(
                mGameLevels[mCurrentlySelectedGameLevelIdx]));
  }
};

#endif