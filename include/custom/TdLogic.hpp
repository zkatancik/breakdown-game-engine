#ifndef TD_LOGIC_HPP
#define TD_LOGIC_HPP
#include <iostream>

#include "base/CenterTextComponent.hpp"
#include "base/PhysicsManager.hpp"
#include "base/SDLProgramLogic.hpp"
#include "custom/Mouse.hpp"
#include "custom/TdButton.hpp"
#include "custom/TdLevel.hpp"

/**
 * @brief Contains Subsystem management for the Td game.
 */
class TdLogic : public SDLProgramLogic {
 public:
  TdLogic() = default;
  explicit TdLogic(std::string appName) : SDLProgramLogic(std::move(appName)){};
  TdLogic(TdLogic const&) = delete;         // Avoid copy constructor.
  void operator=(TdLogic const&) = delete;  // Don't allow copy assignment.

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
  std::vector<std::shared_ptr<TdLevel>> mGameLevels{nullptr, nullptr, nullptr};
  std::shared_ptr<Level> mCurrentlyActiveLevel{
      nullptr};  //< The level that is currently being shown
  int mCurrentlySelectedGameLevelIdx{0};  //< The index of the game level that
                                          // will start/currently being played.

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