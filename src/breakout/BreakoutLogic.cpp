#include "breakout/BreakoutLogic.hpp"

void BreakoutLogic::startUp(SDL_Renderer* gRender, int width, int height) {
  // Start up Physics Manager
  PhysicsManager::getInstance().startUp();
  // Create Start Menu Level and set it as the currently active level
  createStartMenuLevel(width, height);
  createChangeDifficultyLevel(width, height);
  createChangeLanguageLevel(width, height);
  mLevelClearedMenu = std::make_shared<Level>(width, height);
  mLevelFailedMenu = std::make_shared<Level>(width, height);
  loadAllLevels(width, height);
  mCurrentlyActiveLevel = mStartMenu;

  // Music Volume adjustment
  Mix_VolumeMusic(MIX_MAX_VOLUME / 6);
  Mix_PlayMusic(
      ResourceManager::getInstance().getMusic(
          "2DBreakout/SFX/251461__joshuaempyre__arcade-music-loop.wav"),
      -1);
}

void BreakoutLogic::shutDown() {
  mStartMenu->finalize();
  mLanguageMenu->finalize();
  mDifficultyMenu->finalize();
  for (const auto& l : mGameLevels) l->finalize();
  PhysicsManager::getInstance().shutDown();
}

void BreakoutLogic::update() {
  mCurrentlyActiveLevel->update();
  if (isGameActive()) {
    auto currGameLevel = std::weak_ptr<BreakoutGameLevel>(
        mGameLevels[mCurrentlySelectedGameLevelIdx]);
    if (!currGameLevel.lock()->isLevelInProgress()) {
      if (currGameLevel.lock()->isGameWon()) {
        initializeLevelClearedMenu(currGameLevel.lock()->getScore());
        mCurrentlyActiveLevel = mLevelClearedMenu;
      } else {
        initializeLevelFailedMenu(currGameLevel.lock()->getScore());
        mCurrentlyActiveLevel = mLevelFailedMenu;
      }
      currGameLevel.lock()->finalize();
    }
  }
  if (InputManager::getInstance().isKeyPressed(SDLK_x)) {
    if (isGameActive()) {
      mGameLevels[mCurrentlySelectedGameLevelIdx]->finalize();
      mCurrentlySelectedGameLevelIdx =
          mCurrentlySelectedGameLevelIdx == 3
              ? 0
              : (mCurrentlySelectedGameLevelIdx + 1);
      mCurrentlyActiveLevel = mGameLevels[mCurrentlySelectedGameLevelIdx];
      mCurrentlyActiveLevel->initialize();
    }
  }
  // Reset the level
  if (InputManager::getInstance().isKeyPressed(SDLK_r)) {
    if (isGameActive()) {
      mCurrentlyActiveLevel->finalize();
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
    mGameLevels[i] =
        std::make_shared<BreakoutGameLevel>(width, height, mDifficulty, i + 1);
  }
}

void BreakoutLogic::createChangeDifficultyLevel(int width, int height) {
  if (mDifficultyMenu != nullptr) return;
  mDifficultyMenu = std::make_shared<Level>(width, height);
  // Lambda for changing the difficulty to easy
  auto changeDifficultyToEasy = [&] {
    for (const auto& l : mGameLevels) {
      l->setDifficulty(BreakoutGameLevel::Easy);
    }
    mCurrentlyActiveLevel = mStartMenu;
  };

  // Add the easy button
  mDifficultyMenu->addObject(std::make_shared<BreakoutButton>(
      *mDifficultyMenu, width / 2, height / 3, width / 4, 139,
      BreakoutButton::Color::GREEN, u8"EASY", changeDifficultyToEasy));
  /******************************************************************************************************************/

  // Lambda for changing the difficulty to medium
  auto changeDifficultyToMedium = [&] {
    for (const auto& l : mGameLevels) {
      l->setDifficulty(BreakoutGameLevel::Medium);
    }
    mCurrentlyActiveLevel = mStartMenu;
  };

  // Add the medium button
  mDifficultyMenu->addObject(std::make_shared<BreakoutButton>(
      *mDifficultyMenu, width, height / 3, width, 139, BreakoutButton::Color::GREEN,
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
  mDifficultyMenu->addObject(std::make_shared<BreakoutButton>(
      *mDifficultyMenu, width * 1.5, height / 3, width / 4, 139,
      BreakoutButton::Color::GREEN, u8"HARD", changeDifficultyToHard));
  /******************************************************************************************************************/

  // Lambda for returning to main menu
  auto changeToStartMenu = [&] { mCurrentlyActiveLevel = mStartMenu; };

  // Add the return button
  mDifficultyMenu->addObject(std::make_shared<BreakoutButton>(
      *mDifficultyMenu, width, 2 * height / 3, width / 4, 139,
      BreakoutButton::Color::RED, u8"RETURN", changeToStartMenu));
  /******************************************************************************************************************/

  mDifficultyMenu->addObject(std::make_shared<Mouse>(*mDifficultyMenu));
}

void BreakoutLogic::createChangeLanguageLevel(int width, int height) {
  if (mLanguageMenu != nullptr) return;
  mLanguageMenu = std::make_shared<Level>(width, height);
  // Lambda for changing the language to English
  auto changeLanguageToEnglish = [&] {
    mLanguageMenu->changeLanguage(Language::ENGLISH);
    mStartMenu->changeLanguage(Language::ENGLISH);
    mDifficultyMenu->changeLanguage(Language::ENGLISH);
    for (auto& l : mGameLevels) {
      l->changeLanguage(Language::ENGLISH);
    }
  };

  // Add the easy button
  mLanguageMenu->addObject(std::make_shared<BreakoutButton>(
      *mLanguageMenu, width / 2, height / 3, width / 4, 139,
      BreakoutButton::Color::GREEN, u8"ENGLISH", changeLanguageToEnglish));
  /******************************************************************************************************************/
  // Lambda for changing the language to English
  auto changeLanguageToSpanish = [&] {
    mLanguageMenu->changeLanguage(Language::SPANISH);
    mStartMenu->changeLanguage(Language::SPANISH);
    mDifficultyMenu->changeLanguage(Language::SPANISH);
    for (auto& l : mGameLevels) {
      l->changeLanguage(Language::SPANISH);
    }
  };

  // Add the easy button
  mLanguageMenu->addObject(std::make_shared<BreakoutButton>(
      *mLanguageMenu, width * 1.5, height / 3, width / 4, 139,
      BreakoutButton::Color::GREEN, u8"SPANISH", changeLanguageToSpanish));
  /******************************************************************************************************************/
  // Lambda for returning to main menu
  auto changeToStartMenu = [&] { mCurrentlyActiveLevel = mStartMenu; };

  // Add the return button
  mLanguageMenu->addObject(std::make_shared<BreakoutButton>(
      *mLanguageMenu, width, 2 * height / 3, width / 4, 139, BreakoutButton::Color::RED,
      u8"RETURN", changeToStartMenu));
  /******************************************************************************************************************/
  mLanguageMenu->addObject(std::make_shared<Mouse>(*mLanguageMenu));
}

void BreakoutLogic::createStartMenuLevel(int width, int height) {
  // Return if the level is already created.
  if (mStartMenu != nullptr) return;
  // Create a Level to hold the menu
  mStartMenu = std::make_shared<Level>(width, height);

  // Lambda for creating a game level and setting the active level to be the
  // game itself.
  auto startGameLevelButtonHook = [&]() {
    mGameLevels[mCurrentlySelectedGameLevelIdx]->initialize();
    mCurrentlyActiveLevel = mGameLevels[mCurrentlySelectedGameLevelIdx];
  };

  // Add the Start game button
  std::shared_ptr<BreakoutButton> startButton = std::make_shared<BreakoutButton>(
      *mStartMenu, width, height / 6, width / 4, 139, BreakoutButton::Color::GREEN,
      u8"START", startGameLevelButtonHook);

  mStartMenu->addObject(startButton);

  /******************************************************************************************************************/

  // Lambda for creating the change Difficulty menu
  auto changeDifficultyButtonHook = [&]() {
    mCurrentlyActiveLevel = mDifficultyMenu;
  };

  // Add the select difficulty button
  mStartMenu->addObject(std::make_shared<BreakoutButton>(
      *mStartMenu, width, height / 6 + 200, 2 * width / 3, 139,
      BreakoutButton::Color::GREEN, u8"SELECT DIFFICULTY", changeDifficultyButtonHook));

  /******************************************************************************************************************/

  // Lambda for creating the language menu, and setting the active level to be
  // it
  auto changeLanguageButtonHook = [&] {
    mCurrentlyActiveLevel = mLanguageMenu;
  };

  // Add the change language button to the start menu
  mStartMenu->addObject(std::make_shared<BreakoutButton>(
      *mStartMenu, width, height / 6 + 400, 2 * width / 3, 139,
      BreakoutButton::Color::GREEN, u8"CHANGE LANGUAGE", changeLanguageButtonHook));

  /******************************************************************************************************************/
  // Add mouse pointer
  mStartMenu->addObject(std::make_shared<Mouse>(*mStartMenu));
}

void createTextMessageForLevel(const std::shared_ptr<Level>& level,
                               const std::string& message, float x, float y,
                               int fontSize = 64) {
  auto messageObject =
      std::make_shared<GameObject>(*level, x, y, 1, 1, BaseTextTag);
  auto textRenderer = std::make_shared<TextureRenderComponent>(*messageObject);

  textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  messageObject->setRenderComponent(textRenderer);
  auto textComponent = std::make_shared<TextComponent>(
      *messageObject, message, fontSize, "2DBreakout/Fonts/Gageda.ttf",
      textRenderer);
  messageObject->addGenericComponent(textComponent);
  messageObject->addGenericComponent(std::make_shared<CenterTextComponent>(
      *messageObject, textRenderer, x, y));
  level->addObject(messageObject);
}

void BreakoutLogic::initializeLevelClearedMenu(int score) {
  mLevelClearedMenu->finalize();
  // Lambda for changing the language to English
  auto goToNextLevelLambda = [&] {
    mGameLevels[mCurrentlySelectedGameLevelIdx]->finalize();
    mCurrentlySelectedGameLevelIdx = mCurrentlySelectedGameLevelIdx == 3
                                         ? 0
                                         : (mCurrentlySelectedGameLevelIdx + 1);
    mCurrentlyActiveLevel = mGameLevels[mCurrentlySelectedGameLevelIdx];
    mCurrentlyActiveLevel->initialize();
  };
  int width = mStartMenu->w();
  int height = mStartMenu->h();
  mLevelClearedMenu->addObject(std::make_shared<BreakoutButton>(
      *mLevelClearedMenu, width, 2 * height / 3, width / 4, 139,
      BreakoutButton::Color::GREEN, u8"NEXT LEVEL", goToNextLevelLambda));

  createTextMessageForLevel(mLevelClearedMenu, "LEVEL CLEARED!", width,
                            height / 3, 128);

  createTextMessageForLevel(mLevelClearedMenu,
                            "YOUR SCORE: " + std::to_string(score), width,
                            height / 2);
  mLevelClearedMenu->addObject(std::make_shared<Mouse>(*mLevelClearedMenu));
}

void BreakoutLogic::initializeLevelFailedMenu(int score) {
  mLevelFailedMenu->finalize();
  // Lambda for changing the language to English
  auto goToMainMenuLevelLambda = [&] {
    mGameLevels[mCurrentlySelectedGameLevelIdx]->finalize();
    mCurrentlyActiveLevel = mStartMenu;
  };

  int width = mLevelFailedMenu->w();
  int height = mLevelFailedMenu->h();
  mLevelFailedMenu->addObject(std::make_shared<BreakoutButton>(
      *mLevelFailedMenu, width, 2 * height / 3, width / 4, 139,
      BreakoutButton::Color::GREEN, u8"RETURN", goToMainMenuLevelLambda));

  createTextMessageForLevel(mLevelFailedMenu, "GAME OVER!", width, height / 3,
                            128);

  createTextMessageForLevel(mLevelFailedMenu,
                            "YOUR SCORE: " + std::to_string(score), width,
                            height / 2);

  mLevelFailedMenu->addObject(std::make_shared<Mouse>(*mLevelFailedMenu));
}
