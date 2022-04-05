#ifndef BREAKOUT_LOGIC_HPP
#define BREAKOUT_LOGIC_HPP
#include "base/SDLProgramLogic.hpp"
#include "base/PhysicsManager.hpp"
#include "breakout/GameManager.hpp"
#include "breakout/UIManager.hpp"
#include "breakout/BreakoutGameLevel.hpp"
#include "breakout/Mouse.hpp"
#include "breakout/Button.hpp"

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
    // Start up Physics Manager
    PhysicsManager::getInstance().startUp();
    // Create Start Menu Level and set it as the currently active level
    createStartMenuLevel(width, height);
    mCurrentlyActiveLevel = mStartMenu;

    // Music Volume adjustment
    Mix_VolumeMusic(MIX_MAX_VOLUME / 6);
    Mix_PlayMusic(ResourceManager::getInstance().getMusic("2DBreakout/SFX/251461__joshuaempyre__arcade-music-loop.wav"),
                  -1);
  }

  void shutDown() override {
    if (mStartMenu != nullptr) {
      mStartMenu->finalize();
    }
    if (mLanguageMenu != nullptr) {
      mLanguageMenu->finalize();
    }
    if (mDifficultyMenu != nullptr) {
      mDifficultyMenu->finalize();
    }
    if (mGameLevel != nullptr) {
      mGameLevel->finalize();
    }
    PhysicsManager::getInstance().shutDown();
  }

  void update() override {
    mCurrentlyActiveLevel->update();
    framerateModerator();
  }

  void render(SDL_Renderer* renderer) override {
    mCurrentlyActiveLevel->render(renderer);
  }
 private:
  std::shared_ptr<BreakoutLevel> mStartMenu{nullptr};
  std::shared_ptr<BreakoutLevel> mLanguageMenu{nullptr};
  std::shared_ptr<BreakoutLevel> mDifficultyMenu{nullptr};
  std::shared_ptr<BreakoutGameLevel> mGameLevel{nullptr};
  std::shared_ptr<BreakoutLevel> mCurrentlyActiveLevel{nullptr};
  Language mLanguage{Language::ENGLISH};
  BreakoutGameLevel::GameDifficulty mDifficulty{BreakoutGameLevel::Easy};

  void createStartMenuLevel(int width, int height) {
    mStartMenu = std::make_shared<BreakoutLevel>(width, height, mLanguage);
    // Add mouse


    auto startGameLevelButtonHook = [&] () {
      Mix_PlayChannel(
          1, ResourceManager::getInstance().getChunk("2DBreakout/SFX/ButtonClick_SFX.wav"), 0);
      mGameLevel = std::make_shared<BreakoutGameLevel>(width, height, mDifficulty, mLanguage);
      mGameLevel->initialize();
      mCurrentlyActiveLevel = mGameLevel;
    };

    mStartMenu->addObject(std::make_shared<Button>(*mStartMenu, width / 4, height / 6, width / 4, 139, Button::Color::GREEN,
                                                   u8"START", startGameLevelButtonHook));
    mStartMenu->addObject(std::make_shared<Mouse>(*mStartMenu));

//    difficultyButton = new Button();
//    difficultyButton->startUp(513, 177, 635, 1122, 400, 139, screenWidth / 2,
//                              screenHeight - (screenHeight / 1.7),
//                              u8"SELECT DIFFICULTY");
//
//    languageButton = new Button();
//    languageButton->startUp(513, 177, 635, 1122, 400, 139, screenWidth / 2,
//                            screenHeight - (screenHeight / 3),
//                            u8"CHANGE LANGUAGE");
//
//    returnButton = new Button();
//    returnButton->startUp(513, 177, 510, 860, 400, 139, screenWidth / 2,
//                          screenHeight / 2 + (139 / 2), u8"RETURN");
  }

};

#endif