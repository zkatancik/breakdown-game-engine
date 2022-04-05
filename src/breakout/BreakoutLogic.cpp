#include "breakout/BreakoutLogic.hpp"

void BreakoutLogic::startUp(SDL_Renderer* gRender, int width, int height) {
  // Start up Physics Manager
  PhysicsManager::getInstance().startUp();
  // Create Start Menu Level and set it as the currently active level
  createStartMenuLevel(width, height);
  createChangeDifficultyLevel(width, height);
  createChangeLanguageLevel(width, height);
  loadAllLevels(width, height);
  mCurrentlyActiveLevel = mStartMenu;

  // Music Volume adjustment
  Mix_VolumeMusic(MIX_MAX_VOLUME / 6);
  Mix_PlayMusic(ResourceManager::getInstance().getMusic("2DBreakout/SFX/251461__joshuaempyre__arcade-music-loop.wav"),
                -1);
}

void BreakoutLogic::shutDown() {
  mStartMenu->finalize();
  mLanguageMenu->finalize();
  mDifficultyMenu->finalize();
  for (const auto& l : mGameLevels)
    l->finalize();
  PhysicsManager::getInstance().shutDown();
}

void BreakoutLogic::update() {
  mCurrentlyActiveLevel->update();
  if(InputManager::getInstance().isKeyPressed(SDLK_x)) {
    if (isGameActive()) {
      mGameLevels[mCurrentlySelectedGameLevelIdx]->finalize();
      mCurrentlySelectedGameLevelIdx = mCurrentlySelectedGameLevelIdx == 3 ? 0 : (mCurrentlySelectedGameLevelIdx + 1);
      mCurrentlyActiveLevel = mGameLevels[mCurrentlySelectedGameLevelIdx];
      mCurrentlyActiveLevel->initialize();
    }
  }
  if (InputManager::getInstance().isKeyPressed(SDLK_q)) {
    mQuite = true;
  }
  framerateModerator();
}




void BreakoutLogic::loadAllLevels(int width, int height) {
  for (unsigned int i = 0; i < mGameLevels.size(); i++) {
    mGameLevels[i] = std::make_shared<BreakoutGameLevel>(width, height, mDifficulty, i + 1);
  }
}


void BreakoutLogic::createChangeDifficultyLevel(int width, int height) {
  if (mDifficultyMenu != nullptr)
    return;
  mDifficultyMenu = std::make_shared<Level>(width, height);
  // Lambda for changing the difficulty to easy
  auto changeDifficultyToEasy = [&] {
    for (const auto& l : mGameLevels) {
      l->setDifficulty(BreakoutGameLevel::Easy);
    }
    mCurrentlyActiveLevel = mStartMenu;
  };

  // Add the easy button
  mDifficultyMenu->addObject(std::make_shared<Button>(*mDifficultyMenu, width / 4, height / 6, width / 4, 139, Button::Color::GREEN,
                                                      u8"EASY", changeDifficultyToEasy));
  /******************************************************************************************************************/

  // Lambda for changing the difficulty to medium
  auto changeDifficultyToMedium = [&] {
    for (const auto& l : mGameLevels) {
      l->setDifficulty(BreakoutGameLevel::Medium);
    }
    mCurrentlyActiveLevel = mStartMenu;
  };

  // Add the medium button
  mDifficultyMenu->addObject(std::make_shared<Button>(*mDifficultyMenu, width / 4, height / 6 + 200, width / 4, 139, Button::Color::GREEN,
                                                      u8"MEDIUM", changeDifficultyToMedium));
  /******************************************************************************************************************/

  // Lambda for changing the difficulty to hard
  auto changeDifficultyToHard = [&] {
    for (const auto& l : mGameLevels) {
      l->setDifficulty(BreakoutGameLevel::Hard);
    }
    mCurrentlyActiveLevel = mStartMenu;
  };

  // Add the hard button
  mDifficultyMenu->addObject(std::make_shared<Button>(*mDifficultyMenu, width / 4, height / 6 + 400, width / 4, 139, Button::Color::GREEN,
                                                      u8"HARD", changeDifficultyToHard));
  /******************************************************************************************************************/


  // Lambda for returning to main menu
  auto changeToStartMenu = [&] {
    mCurrentlyActiveLevel = mStartMenu;
  };

  // Add the return button
  mDifficultyMenu->addObject(std::make_shared<Button>(*mDifficultyMenu, width / 2, height / 6 + 200, width / 4, 139, Button::Color::RED,
                                                      u8"RETURN", changeToStartMenu ));
  /******************************************************************************************************************/


  mDifficultyMenu->addObject(std::make_shared<Mouse>(*mDifficultyMenu));
}

void BreakoutLogic::createChangeLanguageLevel(int width, int height) {
  if (mLanguageMenu != nullptr)
    return;
  mLanguageMenu = std::make_shared<Level>(width, height);
  // Lambda for changing the language to English
  auto changeLanguageToEnglish = [&] {
    mLanguageMenu->changeLanguage(Language::ENGLISH);
    mStartMenu->changeLanguage(Language::ENGLISH);
    mDifficultyMenu->changeLanguage(Language::ENGLISH);
    for (auto & l : mGameLevels) {
      l->changeLanguage(Language::ENGLISH);
    }
  };

  // Add the easy button
  mLanguageMenu->addObject(std::make_shared<Button>(*mLanguageMenu, width / 4, height / 6, width / 4, 139, Button::Color::GREEN,
                                                    u8"ENGLISH", changeLanguageToEnglish));
  /******************************************************************************************************************/
  // Lambda for changing the language to English
  auto changeLanguageToSpanish = [&] {
    mLanguageMenu->changeLanguage(Language::SPANISH);
    mStartMenu->changeLanguage(Language::SPANISH);
    mDifficultyMenu->changeLanguage(Language::SPANISH);
    for (auto & l : mGameLevels) {
      l->changeLanguage(Language::SPANISH);
    }
  };

  // Add the easy button
  mLanguageMenu->addObject(std::make_shared<Button>(*mLanguageMenu, width / 4, height / 6 + 200, width / 4, 139, Button::Color::GREEN,
                                                    u8"SPANISH", changeLanguageToSpanish));
  /******************************************************************************************************************/
  // Lambda for returning to main menu
  auto changeToStartMenu = [&] {
    mCurrentlyActiveLevel = mStartMenu;
  };

  // Add the return button
  mLanguageMenu->addObject(std::make_shared<Button>(*mLanguageMenu, width / 2, height / 6 + 200, width / 4, 139, Button::Color::RED,
                                                    u8"RETURN", changeToStartMenu ));
  /******************************************************************************************************************/
  mLanguageMenu->addObject(std::make_shared<Mouse>(*mLanguageMenu));
}

void BreakoutLogic::createStartMenuLevel(int width, int height) {
  // Return if the level is already created.
  if (mStartMenu != nullptr)
    return;
  // Create a Level to hold the menu
  mStartMenu = std::make_shared<Level>(width, height);

  // Lambda for creating a game level and setting the active level to be the game itself.
  auto startGameLevelButtonHook = [&] () {
    mGameLevels[mCurrentlySelectedGameLevelIdx]->initialize();
    mCurrentlyActiveLevel = mGameLevels[0];
  };

  // Add the Start game button
  mStartMenu->addObject(std::make_shared<Button>(*mStartMenu, width / 4, height / 6, width / 4, 139, Button::Color::GREEN,
                                                 u8"START", startGameLevelButtonHook));

  /******************************************************************************************************************/

  // Lambda for creating the change Difficulty menu
  auto changeDifficultyButtonHook = [&] () {
    mCurrentlyActiveLevel = mDifficultyMenu;
  };

  // Add the select difficulty button
  mStartMenu->addObject(std::make_shared<Button>(*mStartMenu, width / 4, height / 6 + 200, 2 * width / 3, 139, Button::Color::GREEN,
                                                 u8"SELECT DIFFICULTY", changeDifficultyButtonHook));

  /******************************************************************************************************************/

  // Lambda for creating the language menu, and setting the active level to be it
  auto changeLanguageButtonHook = [&] {
    mCurrentlyActiveLevel = mLanguageMenu;
  };

  // Add the change language button to the start menu
  mStartMenu->addObject(std::make_shared<Button>(*mStartMenu, width / 4, height / 6 + 400, 2 * width / 3, 139, Button::Color::GREEN,
                                                 u8"CHANGE LANGUAGE", changeLanguageButtonHook));

  /******************************************************************************************************************/
  // Add mouse pointer
  mStartMenu->addObject(std::make_shared<Mouse>(*mStartMenu));
}

