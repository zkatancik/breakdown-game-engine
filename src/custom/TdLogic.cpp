#include "custom/TdLogic.hpp"

#include "base/InputManager.hpp"

void TdLogic::startUp(SDL_Renderer* gRender, int width, int height) {
  // Start up Physics Manager
  PhysicsManager::getInstance().startUp();
  // Create Start Menu Level and set it as the currently active level
  createStartMenuLevel(width, height);
  createChangeLanguageLevel(width, height);
  createInstructionsLevel(width, height);
  mLevelClearedMenu = std::make_shared<Level>(width, height);
  mLevelFailedMenu = std::make_shared<Level>(width, height);
  loadAllLevels(width, height);
  mCurrentlyActiveLevel = mStartMenu;

  // Music Volume adjustment
  Mix_VolumeMusic(MIX_MAX_VOLUME / 6);
  Mix_PlayMusic(ResourceManager::getInstance().getMusic(
                    "TD2D/Audio/Tracks/bloonstd4.mp3"),
                -1);
  Mix_Volume(0, MIX_MAX_VOLUME);
  Mix_Volume(1, MIX_MAX_VOLUME / 6);
}

void TdLogic::shutDown() {
  mStartMenu->finalize();
  mLanguageMenu->finalize();
  mInstructionsMenu->finalize();
  mLevelClearedMenu->finalize();
  mLevelFailedMenu->finalize();
  for (const auto& l : mGameLevels) l->finalize();
  PhysicsManager::getInstance().shutDown();
}

void TdLogic::update() {
  mCurrentlyActiveLevel->update();

  if (isGameActive()) {
    auto currGameLevel =
        std::weak_ptr<TdLevel>(mGameLevels[mCurrentlySelectedGameLevelIdx]);
    if (!currGameLevel.lock()->isLevelInProgress()) {
      if (currGameLevel.lock()->isLevelWon()) {
        initializeLevelClearedMenu();
        mCurrentlyActiveLevel = mLevelClearedMenu;
      } else {
        initializeLevelFailedMenu();
        mCurrentlyActiveLevel = mLevelFailedMenu;
      }
      currGameLevel.lock()->finalize();
    }
  }

  if (InputManager::getInstance().isKeyPressed(SDLK_n)) {
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
    mQuit = true;
  }
  framerateModerator();
}

void TdLogic::loadAllLevels(int width, int height) {
  mGameLevels[0] = std::make_shared<TdLevel>(width, height, 1);
  mGameLevels[1] = std::make_shared<TdLevel>(width, height, 2);
  mGameLevels[2] = std::make_shared<TdLevel>(width, height, 3);
  mGameLevels[3] = std::make_shared<TdLevel>(width, height, 4);
}

void TdLogic::createInstructionsLevel(int width, int height) {
  if (mInstructionsMenu != nullptr) return;
  mInstructionsMenu = std::make_shared<Level>(width, height);

//   /******************************************************************************************************************/

  auto background =
      std::make_shared<GameObject>(*mInstructionsMenu, 0, 0, width, height, 44);
  auto bgRenderer = std::make_shared<TextureRenderComponent>(*background);

  bgRenderer->setRenderMode(TextureRenderComponent::RenderMode::CUSTOM_WIDTH);
  background->setRenderComponent(bgRenderer);
  bgRenderer->setCustomH(868);
  bgRenderer->setCustomW(1480);
  bgRenderer->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/GUI/Menu/menubg.jpg"));

  mInstructionsMenu->addObject(background);

  /******************************************************************************************************************/

  // Add Instructions
  auto title =
      std::make_shared<GameObject>(*mInstructionsMenu, 10, 10, 50, 50, 22);
  auto textRenderer = std::make_shared<TextureRenderComponent>(*title);
  textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  title->setRenderComponent(textRenderer);
  auto textComponent = std::make_shared<TextComponent>(
      *title, u8"How to Play", 128, "TD2D/Fonts/madera-tygra.ttf",
      textRenderer);
  title->addGenericComponent(std::make_shared<CenterTextComponent>(
      *title, textRenderer, width, height));
  textRenderer->setOffSetY(int(100));
  title->addGenericComponent(textComponent);
  mInstructionsMenu->addObject(title);

  auto instruction1 =
      std::make_shared<GameObject>(*mInstructionsMenu, 10, 10, 50, 50, 22);
  auto textRenderer1 = std::make_shared<TextureRenderComponent>(*title);
  textRenderer1->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  instruction1->setRenderComponent(textRenderer1);
  auto textComponent1 = std::make_shared<TextComponent>(
      *instruction1, u8"Each level has three waves and each Tower costs ten coins.", 40,
      "TD2D/Fonts/madera-tygra.ttf", textRenderer1);
  textRenderer1->setOffSetX(-175);
  textRenderer1->setOffSetY(int(300));
  instruction1->addGenericComponent(textComponent1);
  mInstructionsMenu->addObject(instruction1);

  auto instruction2 =
      std::make_shared<GameObject>(*mInstructionsMenu, 10, 10, 50, 50, 22);
  auto textRenderer2 = std::make_shared<TextureRenderComponent>(*title);
  textRenderer2->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  instruction2->setRenderComponent(textRenderer2);
  auto textComponent2 = std::make_shared<TextComponent>(
      *instruction2, u8"Killing an enemy gives five coins. Click and place tower in spot.", 40,
      "TD2D/Fonts/madera-tygra.ttf", textRenderer2);
  textRenderer2->setOffSetX(-175);
  textRenderer2->setOffSetY(int(400));
  instruction2->addGenericComponent(textComponent2);
  mInstructionsMenu->addObject(instruction2);

  auto instruction3 =
      std::make_shared<GameObject>(*mInstructionsMenu, 10, 10, 50, 50, 22);
  auto textRenderer3 = std::make_shared<TextureRenderComponent>(*title);
  textRenderer3->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  instruction3->setRenderComponent(textRenderer3);
  auto textComponent3 = std::make_shared<TextComponent>(
      *instruction3, u8"'N' - next level, 'R' - Restart level", 40, "TD2D/Fonts/madera-tygra.ttf",
      textRenderer3);
  textRenderer3->setOffSetX(-175);
  textRenderer3->setOffSetY(int(500));
  instruction3->addGenericComponent(textComponent3);
  mInstructionsMenu->addObject(instruction3);

  /******************************************************************************************************************/
  // Lambda for returning to main menu
  auto changeToStartMenu = [&] { mCurrentlyActiveLevel = mStartMenu; };

  // Add the return button
  mInstructionsMenu->addObject(std::make_shared<TdButton>(
      *mInstructionsMenu, width, 2 * height / 3 + 75, width / 4, 139,
      u8"RETURN", changeToStartMenu));

  /******************************************************************************************************************/
  mInstructionsMenu->addObject(std::make_shared<Mouse>(*mInstructionsMenu));
}

void TdLogic::createChangeLanguageLevel(int width, int height) {
  if (mLanguageMenu != nullptr) return;
  mLanguageMenu = std::make_shared<Level>(width, height);
  // Lambda for changing the language to English
  auto changeLanguageToEnglish = [&] {
    mLanguageMenu->changeLanguage(Language::ENGLISH);
    mStartMenu->changeLanguage(Language::ENGLISH);
    mInstructionsMenu->changeLanguage(Language::ENGLISH);
    for (auto& l : mGameLevels) {
      l->changeLanguage(Language::ENGLISH);
    }
  };

  auto background =
      std::make_shared<GameObject>(*mLanguageMenu, 0, 0, width, height, 44);
  auto bgRenderer = std::make_shared<TextureRenderComponent>(*background);

  bgRenderer->setRenderMode(TextureRenderComponent::RenderMode::CUSTOM_WIDTH);
  background->setRenderComponent(bgRenderer);
  bgRenderer->setCustomH(868);
  bgRenderer->setCustomW(1480);
  bgRenderer->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/GUI/Menu/menubg.jpg"));

  mLanguageMenu->addObject(background);

  // Add the English button
  mLanguageMenu->addObject(std::make_shared<TdButton>(
      *mLanguageMenu, width / 2, height / 3, width / 4, 139, u8"ENGLISH",
      changeLanguageToEnglish));
  /******************************************************************************************************************/
  // Lambda for changing the language to English
  auto changeLanguageToSpanish = [&] {
    mLanguageMenu->changeLanguage(Language::SPANISH);
    mStartMenu->changeLanguage(Language::SPANISH);
    mInstructionsMenu->changeLanguage(Language::SPANISH);
    for (auto& l : mGameLevels) {
      l->changeLanguage(Language::SPANISH);
    }
  };

  // Add the Spanish button
  mLanguageMenu->addObject(std::make_shared<TdButton>(
      *mLanguageMenu, width * 1.5, height / 3, width / 4, 139, u8"SPANISH",
      changeLanguageToSpanish));
  /******************************************************************************************************************/
  // Lambda for returning to main menu
  auto changeToStartMenu = [&] { mCurrentlyActiveLevel = mStartMenu; };

  // Add the return button
  mLanguageMenu->addObject(std::make_shared<TdButton>(
      *mLanguageMenu, width, 2 * height / 3, width / 4, 139, u8"RETURN",
      changeToStartMenu));
  /******************************************************************************************************************/
  mLanguageMenu->addObject(std::make_shared<Mouse>(*mLanguageMenu));
}

void TdLogic::createStartMenuLevel(int width, int height) {
  // // Return if the level is already created.
  if (mStartMenu != nullptr) return;
  // Create a Level to hold the menu
  mStartMenu = std::make_shared<Level>(width, height);

  // // Lambda for creating a game level and setting the active level to be the
  // game itself.
  auto startGameLevelButtonHook = [&]() {
    mGameLevels[mCurrentlySelectedGameLevelIdx]->finalize();
    mGameLevels[mCurrentlySelectedGameLevelIdx]->initialize();
    mGameLevels[mCurrentlySelectedGameLevelIdx]->addObject(std::make_shared<Mouse>(*mGameLevels[mCurrentlySelectedGameLevelIdx]));
    mCurrentlyActiveLevel = mGameLevels[mCurrentlySelectedGameLevelIdx];
  };

  auto background =
      std::make_shared<GameObject>(*mStartMenu, 0, 0, width, height, 44);
  auto bgRenderer = std::make_shared<TextureRenderComponent>(*background);

  bgRenderer->setRenderMode(TextureRenderComponent::RenderMode::CUSTOM_WIDTH);
  background->setRenderComponent(bgRenderer);
  bgRenderer->setCustomH(868);
  bgRenderer->setCustomW(1480);
  bgRenderer->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/GUI/Menu/menubg.jpg"));

  mStartMenu->addObject(background);

  auto title = std::make_shared<GameObject>(*mStartMenu, 10, 10, 50, 50, 22);
  auto textRenderer = std::make_shared<TextureRenderComponent>(*title);

  textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  title->setRenderComponent(textRenderer);
  std::vector<int> color = {93, 35, 238, 0};
  auto textComponent = std::make_shared<TextComponent>(
      *title, "Tower Hour", 128, "TD2D/Fonts/madera-tygra.ttf", textRenderer,
      ENGLISH, color);

  title->addGenericComponent(std::make_shared<CenterTextComponent>(
      *title, textRenderer, width, height));

  textRenderer->setOffSetY(int(100));

  title->addGenericComponent(textComponent);

  mStartMenu->addObject(title);

  // Add the Start game button
  // Note, magic constants come from Button.cpp but also the w,h values don't
  // matter for buttons
  mStartMenu->addObject(
      std::make_shared<TdButton>(*mStartMenu, width, height / 3, 784, 295,
                                 u8"START", startGameLevelButtonHook));

  /******************************************************************************************************************/

  // Lambda for creating the language menu, and setting the active level to be
  // it
  auto changeLanguageButtonHook = [&] {
    mCurrentlyActiveLevel = mLanguageMenu;
  };

  // Add the change language button to the start menu
  mStartMenu->addObject(std::make_shared<TdButton>(
      *mStartMenu, width, (height / 2) + 50, 784, 295, u8"CHANGE LANGUAGE",
      changeLanguageButtonHook));

  /******************************************************************************************************************/

  // Lambda for creating the Instructions menu
  auto instructionsButtonHook = [&] {
    mCurrentlyActiveLevel = mInstructionsMenu;
  };

  // Add the change language button to the start menu
  mStartMenu->addObject(
      std::make_shared<TdButton>(*mStartMenu, width, (height / 2) + 250, 784,
                                 295, u8"HOW TO PLAY", instructionsButtonHook));

  /******************************************************************************************************************/

  // Add mouse pointer
  mStartMenu->addObject(std::make_shared<Mouse>(*mStartMenu));
}

void TdLogic::createTextMessageForLevel(const std::shared_ptr<Level>& level,
                                        const std::string& message, float x,
                                        float y, int fontSize) {
  auto messageObject =
      std::make_shared<GameObject>(*level, x, y, 1, 1, BaseTextTag);
  auto textRenderer = std::make_shared<TextureRenderComponent>(*messageObject);

  textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  messageObject->setRenderComponent(textRenderer);
  auto textComponent = std::make_shared<TextComponent>(
      *messageObject, message, fontSize, "Graverunner/fonts/GADAQUALI.ttf",
      textRenderer);
  messageObject->addGenericComponent(textComponent);
  messageObject->addGenericComponent(std::make_shared<CenterTextComponent>(
      *messageObject, textRenderer, x, y));
  level->addObject(messageObject);
}

void TdLogic::initializeLevelClearedMenu() {
  mLevelClearedMenu->finalize();
  // Lambda for going to next level
  auto goToNextLevelLambda = [&] {
    mGameLevels[mCurrentlySelectedGameLevelIdx]->finalize();
    mCurrentlySelectedGameLevelIdx = mCurrentlySelectedGameLevelIdx == 3
                                         ? 0
                                         : (mCurrentlySelectedGameLevelIdx + 1);
    mCurrentlyActiveLevel = mGameLevels[mCurrentlySelectedGameLevelIdx];
    mCurrentlyActiveLevel->initialize();
  };

  int width = mLevelClearedMenu->w();
  int height = mLevelClearedMenu->h();

  auto background =
      std::make_shared<GameObject>(*mLevelClearedMenu, 0, 0, width, height, 44);
  auto bgRenderer = std::make_shared<TextureRenderComponent>(*background);

  bgRenderer->setRenderMode(TextureRenderComponent::RenderMode::CUSTOM_WIDTH);
  background->setRenderComponent(bgRenderer);
  bgRenderer->setCustomH(868);
  bgRenderer->setCustomW(1480);
  bgRenderer->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/GUI/Menu/menubg.jpg"));

  mLevelClearedMenu->addObject(background);

  mLevelClearedMenu->addObject(std::make_shared<TdButton>(
      *mLevelClearedMenu, width, 2 * height / 3, width / 4, 139, u8"NEXT LEVEL",
      goToNextLevelLambda));

  createTextMessageForLevel(mLevelClearedMenu, "LEVEL CLEARED!", width,
                            height / 3, 128);

  mLevelClearedMenu->addObject(std::make_shared<Mouse>(*mLevelClearedMenu));
}

void TdLogic::initializeLevelFailedMenu() {
  mLevelFailedMenu->finalize();
  // Lambda for going back to start menu
  auto goToMainMenuLevelLambda = [&] {
    mGameLevels[mCurrentlySelectedGameLevelIdx]->finalize();
    mCurrentlyActiveLevel = mStartMenu;
  };

  int width = mLevelFailedMenu->w();
  int height = mLevelFailedMenu->h();

  auto background =
      std::make_shared<GameObject>(*mLevelFailedMenu, 0, 0, width, height, 44);
  auto bgRenderer = std::make_shared<TextureRenderComponent>(*background);

  bgRenderer->setRenderMode(TextureRenderComponent::RenderMode::CUSTOM_WIDTH);
  background->setRenderComponent(bgRenderer);
  bgRenderer->setCustomH(868);
  bgRenderer->setCustomW(1480);
  bgRenderer->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/GUI/Menu/menubg.jpg"));

  mLevelFailedMenu->addObject(background);

  mLevelFailedMenu->addObject(std::make_shared<TdButton>(
      *mLevelFailedMenu, width, 2 * height / 3, width / 4, 139, u8"RETURN",
      goToMainMenuLevelLambda));

  createTextMessageForLevel(mLevelFailedMenu, "GAME OVER!", width, height / 3,
                            128);

  mLevelFailedMenu->addObject(std::make_shared<Mouse>(*mLevelFailedMenu));
}
