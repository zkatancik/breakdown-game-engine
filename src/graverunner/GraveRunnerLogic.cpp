#include "graverunner/GraveRunnerLogic.hpp"
#include "base/InputManager.hpp"

void GraveRunnerLogic::startUp(SDL_Renderer* gRender, int width, int height) {
  // Start up Physics Manager
  PhysicsManager::getInstance().startUp();
  // Create Start Menu Level and set it as the currently active level
  createStartMenuLevel(width, height);
  createChangeLanguageLevel(width, height);
  loadAllLevels(width, height);
  mCurrentlyActiveLevel = mStartMenu;

  // Music Volume adjustment
  Mix_VolumeMusic(MIX_MAX_VOLUME / 6);
  Mix_PlayMusic(
      ResourceManager::getInstance().getMusic("Graverunner/2DPlatformer_SFX/ClassicsIV-Spooky.wav"), -1);
  Mix_Volume(0, MIX_MAX_VOLUME);
  Mix_Volume(1, MIX_MAX_VOLUME / 6);
}

void GraveRunnerLogic::shutDown() {
  mStartMenu->finalize();
  mLanguageMenu->finalize();
  for (const auto& l : mGameLevels)
    l->finalize();

  PhysicsManager::getInstance().shutDown();
}

void GraveRunnerLogic::update() {
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
    mQuit = true;
  }
  framerateModerator();
}

void GraveRunnerLogic::loadAllLevels(int width, int height) {
  for (unsigned int i = 0; i < mGameLevels.size(); i++) {
    mGameLevels[i] = std::make_shared<GraveRunnerLevel>(width, height, i + 1);
  }
}

void GraveRunnerLogic::createChangeLanguageLevel(int width, int height) {
  if (mLanguageMenu != nullptr)
    return;
  mLanguageMenu = std::make_shared<Level>(width, height);
  // Lambda for changing the language to English
  auto changeLanguageToEnglish = [&] {
    mLanguageMenu->changeLanguage(Language::ENGLISH);
    mStartMenu->changeLanguage(Language::ENGLISH);
    for (auto & l : mGameLevels) {
      l->changeLanguage(Language::ENGLISH);
    }
  };

  // Add the English button
  mLanguageMenu->addObject(std::make_shared<Button>(*mLanguageMenu, width / 4, height / 6, width / 4, 139, Button::Color::GREEN,
                                                    u8"ENGLISH", changeLanguageToEnglish));
  /******************************************************************************************************************/
  // Lambda for changing the language to English
  auto changeLanguageToSpanish = [&] {
    mLanguageMenu->changeLanguage(Language::SPANISH);
    mStartMenu->changeLanguage(Language::SPANISH);
    for (auto & l : mGameLevels) {
      l->changeLanguage(Language::SPANISH);
    }
  };

  // Add the Spanish button
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

void GraveRunnerLogic::createStartMenuLevel(int width, int height) {
  // // Return if the level is already created.
  if (mStartMenu != nullptr)
     return;
  // Create a Level to hold the menu
  mStartMenu = std::make_shared<Level>(width, height);

  // // Lambda for creating a game level and setting the active level to be the game itself.
  auto startGameLevelButtonHook = [&] () {
    mGameLevels[mCurrentlySelectedGameLevelIdx]->initialize();
    mCurrentlyActiveLevel = mGameLevels[0];
  };

  // // Add the Start game button
  mStartMenu->addObject(std::make_shared<Button>(*mStartMenu, width / 4, height / 6, width / 4, 139, Button::Color::GREEN,
                                                 u8"START", startGameLevelButtonHook));

  // /******************************************************************************************************************/

  // Lambda for creating the language menu, and setting the active level to be it
  auto changeLanguageButtonHook = [&] {
    mCurrentlyActiveLevel = mLanguageMenu;
  };

  // Add the change language button to the start menu
  mStartMenu->addObject(std::make_shared<Button>(*mStartMenu, width / 4, height / 6 + 400, 2 * width / 3, 139, Button::Color::GREEN,
                                                 u8"CHANGE LANGUAGE", changeLanguageButtonHook));

  // /******************************************************************************************************************/
  // Add mouse pointer
  mStartMenu->addObject(std::make_shared<Mouse>(*mStartMenu));
}

