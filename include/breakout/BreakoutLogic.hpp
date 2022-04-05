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
    createChangeDifficultyLevel(width, height);
    createChangeLanguageLevel(width, height);

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

  void createChangeDifficultyLevel(int width, int height) {
    if (mDifficultyMenu != nullptr)
      return;
    mDifficultyMenu = std::make_shared<BreakoutLevel>(width, height, mLanguage);
    // Lambda for changing the difficulty to easy
    auto changeDifficultyToEasy = [&] {
      Mix_PlayChannel(
          1, ResourceManager::getInstance().getChunk("2DBreakout/SFX/ButtonClick_SFX.wav"), 0);
      mDifficulty = BreakoutGameLevel::Easy;
    };

    // Add the easy button
    mDifficultyMenu->addObject(std::make_shared<Button>(*mDifficultyMenu, width / 4, height / 6, width / 4, 139, Button::Color::GREEN,
                                                   u8"EASY", changeDifficultyToEasy));
    /******************************************************************************************************************/

    // Lambda for changing the difficulty to medium
    auto changeDifficultyToMedium = [&] {
      Mix_PlayChannel(
          1, ResourceManager::getInstance().getChunk("2DBreakout/SFX/ButtonClick_SFX.wav"), 0);
      mDifficulty = BreakoutGameLevel::Medium;
    };

    // Add the medium button
    mDifficultyMenu->addObject(std::make_shared<Button>(*mDifficultyMenu, width / 4, height / 6 + 200, width / 4, 139, Button::Color::GREEN,
                                                   u8"MEDIUM", changeDifficultyToMedium));
    /******************************************************************************************************************/

    // Lambda for changing the difficulty to hard
    auto changeDifficultyToHard = [&] {
      Mix_PlayChannel(
          1, ResourceManager::getInstance().getChunk("2DBreakout/SFX/ButtonClick_SFX.wav"), 0);
      mDifficulty = BreakoutGameLevel::Hard;
    };

    // Add the hard button
    mDifficultyMenu->addObject(std::make_shared<Button>(*mDifficultyMenu, width / 4, height / 6 + 400, width / 4, 139, Button::Color::GREEN,
                                                   u8"HARD", changeDifficultyToHard));
    /******************************************************************************************************************/


    // Lambda for returning to main menu
    auto changeToStartMenu = [&] {
      Mix_PlayChannel(
          1, ResourceManager::getInstance().getChunk("2DBreakout/SFX/ButtonClick_SFX.wav"), 0);
      mCurrentlyActiveLevel = mStartMenu;
    };

    // Add the return button
    mDifficultyMenu->addObject(std::make_shared<Button>(*mDifficultyMenu, width / 2, height / 6 + 200, width / 4, 139, Button::Color::RED,
                                                        u8"RETURN", changeToStartMenu ));
    /******************************************************************************************************************/


    mDifficultyMenu->addObject(std::make_shared<Mouse>(*mDifficultyMenu));
  }

  void createChangeLanguageLevel(int width, int height) {
    if (mLanguageMenu != nullptr)
      return;
    mLanguageMenu = std::make_shared<BreakoutLevel>(width, height, mLanguage);
    // Lambda for changing the language to English
    auto changeLanguageToEnglish = [&] {
      Mix_PlayChannel(
          1, ResourceManager::getInstance().getChunk("2DBreakout/SFX/ButtonClick_SFX.wav"), 0);
      mLanguage = Language::ENGLISH;
    };

    // Add the easy button
    mLanguageMenu->addObject(std::make_shared<Button>(*mLanguageMenu, width / 4, height / 6, width / 4, 139, Button::Color::GREEN,
                                                        u8"ENGLISH", changeLanguageToEnglish));
    /******************************************************************************************************************/
    // Lambda for changing the language to English
    auto changeLanguageToSpanish = [&] {
      Mix_PlayChannel(
          1, ResourceManager::getInstance().getChunk("2DBreakout/SFX/ButtonClick_SFX.wav"), 0);
      mLanguage = Language::SPANISH;
    };

    // Add the easy button
    mLanguageMenu->addObject(std::make_shared<Button>(*mLanguageMenu, width / 4, height / 6 + 200, width / 4, 139, Button::Color::GREEN,
                                                      u8"SPANISH", changeLanguageToSpanish));
    /******************************************************************************************************************/
    // Lambda for returning to main menu
    auto changeToStartMenu = [&] {
      Mix_PlayChannel(
          1, ResourceManager::getInstance().getChunk("2DBreakout/SFX/ButtonClick_SFX.wav"), 0);
      mCurrentlyActiveLevel = mStartMenu;
    };

    // Add the return button
    mLanguageMenu->addObject(std::make_shared<Button>(*mLanguageMenu, width / 2, height / 6 + 200, width / 4, 139, Button::Color::RED,
                                                        u8"RETURN", changeToStartMenu ));
    /******************************************************************************************************************/
    mLanguageMenu->addObject(std::make_shared<Mouse>(*mLanguageMenu));
  }

  void createStartMenuLevel(int width, int height) {
    // Return if the level is already created.
    if (mStartMenu != nullptr)
      return;
    // Create a BreakoutLevel to hold the menu
    mStartMenu = std::make_shared<BreakoutLevel>(width, height, mLanguage);

    // Lambda for creating a game level and setting the active level to be the game itself.
    auto startGameLevelButtonHook = [&] () {
      Mix_PlayChannel(
          1, ResourceManager::getInstance().getChunk("2DBreakout/SFX/ButtonClick_SFX.wav"), 0);
      mGameLevel = std::make_shared<BreakoutGameLevel>(width, height, mDifficulty, mLanguage);
      mGameLevel->initialize();
      mCurrentlyActiveLevel = mGameLevel;
    };

    // Add the Start game button
    mStartMenu->addObject(std::make_shared<Button>(*mStartMenu, width / 4, height / 6, width / 4, 139, Button::Color::GREEN,
                                                   u8"START", startGameLevelButtonHook));

    /******************************************************************************************************************/

    // Lambda for creating the change Difficulty menu
    auto changeDifficultyButtonHook = [&] () {
      Mix_PlayChannel(
          1, ResourceManager::getInstance().getChunk("2DBreakout/SFX/ButtonClick_SFX.wav"), 0);
      mCurrentlyActiveLevel = mDifficultyMenu;
    };

    // Add the select difficulty button
    mStartMenu->addObject(std::make_shared<Button>(*mStartMenu, width / 4, height / 6 + 200, width / 2, 139, Button::Color::GREEN,
                                                   u8"SELECT DIFFICULTY", changeDifficultyButtonHook));

    /******************************************************************************************************************/

    // Lambda for creating the language menu, and setting the active level to be it
    auto changeLanguageButtonHook = [&] {
      Mix_PlayChannel(
          1, ResourceManager::getInstance().getChunk("2DBreakout/SFX/ButtonClick_SFX.wav"), 0);

      mCurrentlyActiveLevel = mLanguageMenu;
    };

    // Add the change language button to the start menu
    mStartMenu->addObject(std::make_shared<Button>(*mStartMenu, width / 4, height / 6 + 400, width / 2, 139, Button::Color::GREEN,
                                                   u8"CHANGE LANGUAGE", changeLanguageButtonHook));

    /******************************************************************************************************************/
    // Add mouse pointer
    mStartMenu->addObject(std::make_shared<Mouse>(*mStartMenu));
  }

};

#endif