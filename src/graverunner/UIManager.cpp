#include "graverunner/UIManager.hpp"

UIManager &UIManager::getInstance() {
  static UIManager *instance = new UIManager();
  return *instance;
}

/**
 * @brief Acts as the contructor.
 *
 * @param screenWidth screen width
 * @param screenHeight screen height
 */
void UIManager::startUp(int screenWidth, int screenHeight) {
  mScreenHeight = screenHeight;
  mScreenWidth = screenWidth;

  mouse = new Mouse();
  mouse->startUp();

  background = ResourceManager::getInstance().getTexture(BACKGROUND_IMAGE);
  bg_dest.w = screenWidth;
  bg_dest.h = screenHeight;
  bg_dest.x = 0;
  bg_dest.y = 0;

  fpsXPadding = screenWidth - FPS_X_PADDING;

  title = ResourceManager::getInstance().getTextTexture(
      "GraveRunner", fontType,
      {TITLE_TEXT_COLOR_RED, TITLE_TEXT_COLOR_GREEN, TITLE_TEXT_COLOR_BLUE,
       TITLE_TEXT_OPACITY},
      TITLE_FONT_SIZE);

  int w, h;
  SDL_QueryTexture(title, nullptr, nullptr, &w, &h);
  title_dest.w = w;
  title_dest.h = h;
  title_dest.x = screenWidth / 2 - (title_dest.w / 2);
  title_dest.y = screenHeight / 6;

  gameOver = ResourceManager::getInstance().getTextTexture(
      getTranslation(u8"GAME OVER"), fontType,
      {TITLE_TEXT_COLOR_RED, TITLE_TEXT_COLOR_GREEN, TITLE_TEXT_COLOR_BLUE,
       TITLE_TEXT_OPACITY},
      TITLE_FONT_SIZE);

  SDL_QueryTexture(gameOver, nullptr, nullptr, &w, &h);
  gameOver_dest.w = w;
  gameOver_dest.h = h;
  gameOver_dest.x = screenWidth / 2 - (gameOver_dest.w / 2);
  gameOver_dest.y = screenHeight / 4;

  levelClear = ResourceManager::getInstance().getTextTexture(
      getTranslation(u8"LEVEL CLEARED!"), fontType,
      {TITLE_TEXT_COLOR_RED, TITLE_TEXT_COLOR_GREEN, TITLE_TEXT_COLOR_BLUE,
       TITLE_TEXT_OPACITY},
      TITLE_FONT_SIZE);
  levelClear_dest = gameOver_dest;

  fps_dest.x = 20;
  fps_dest.y = 20;

  startTicks = SDL_GetTicks();

  startButton = new Button();
  startButton->startUp(BUTTON_SRC_WIDTH, BUTTON_SRC_HEIGHT, BUTTON_SRC_X,
                       BUTTON_SRC_Y, BUTTON_SRC_CLICKED_X, BUTTON_SRC_CLICKED_Y,
                       screenWidth / 2, screenHeight / 3, u8"START");
  languageButton = new Button();
  languageButton->startUp(
      BUTTON_SRC_WIDTH, BUTTON_SRC_HEIGHT, BUTTON_SRC_X, BUTTON_SRC_Y,
      BUTTON_SRC_CLICKED_X, BUTTON_SRC_CLICKED_Y, screenWidth / 2,
      screenHeight / 2, u8"CHANGE LANGUAGE");

  returnButton = new Button();
  returnButton->startUp(BUTTON_SRC_WIDTH, BUTTON_SRC_HEIGHT, BUTTON_SRC_X,
                        BUTTON_SRC_Y, BUTTON_SRC_CLICKED_X,
                        BUTTON_SRC_CLICKED_Y, screenWidth / 2,
                        2 * screenHeight / 3, u8"RETURN");

  returnButtonMenus = new Button();
  returnButtonMenus->startUp(BUTTON_SRC_WIDTH, BUTTON_SRC_HEIGHT, BUTTON_SRC_X,
                             BUTTON_SRC_Y, BUTTON_SRC_CLICKED_X,
                             BUTTON_SRC_CLICKED_Y, screenWidth / 2,
                             screenHeight / 2 + (139 / 2), u8"RETURN");

  englishButton = new Button();
  englishButton->startUp(BUTTON_SRC_WIDTH, BUTTON_SRC_HEIGHT, BUTTON_SRC_X,
                         BUTTON_SRC_Y, BUTTON_SRC_CLICKED_X,
                         BUTTON_SRC_CLICKED_Y, screenWidth / 3,
                         screenHeight / 3, u8"ENGLISH");

  spanishButton = new Button();
  spanishButton->startUp(BUTTON_SRC_WIDTH, BUTTON_SRC_HEIGHT, BUTTON_SRC_X,
                         BUTTON_SRC_Y, BUTTON_SRC_CLICKED_X,
                         BUTTON_SRC_CLICKED_Y, screenWidth - (screenWidth / 3),
                         screenHeight / 3, u8"SPANISH");
  nextLevelButton = new Button();
  nextLevelButton->startUp(BUTTON_SRC_WIDTH, BUTTON_SRC_HEIGHT, BUTTON_SRC_X,
                           BUTTON_SRC_Y, BUTTON_SRC_CLICKED_X,
                           BUTTON_SRC_CLICKED_Y, screenWidth / 2,
                           screenHeight / 2, u8"NEXT LEVEL");
}

/**
 * @brief Acts as a destructor.
 *
 */
void UIManager::shutDown() {
  delete mouse;
  delete startButton;
  delete returnButton;
  delete returnButtonMenus;
  delete languageButton;
  delete englishButton;
  delete spanishButton;
  delete nextLevelButton;
}

/**
 * @brief Update the UI/ menu state
 */
void UIManager::update() {
  mouse->update();

  if (InputManager::getInstance().isKeyDown(SDLK_r)) {
    if (GameManager::getInstance().getGameState() ==
        GameManager::GameState::InGame) {
      GameManager::getInstance().setGameState(GameManager::GameState::PreGame);
      GameManager::getInstance().clearLevel();
    }
  }
  if (GameManager::getInstance().getGameState() ==
      GameManager::getInstance().GameState::PreGame) {
    startButton->update(mouse);
    languageButton->update(mouse);
  } else if (GameManager::getInstance().getGameState() ==
             GameManager::getInstance().GameState::GameEnd) {
    nextLevelButton->update(mouse);
    returnButton->update(mouse);
  } else if (GameManager::getInstance().getGameState() ==
             GameManager::getInstance().GameState::LanguageSelect) {
    englishButton->update(mouse);
    spanishButton->update(mouse);
    returnButtonMenus->update(mouse);
  }
}

/**
 * @brief Render a frame of the game.
 *
 * @param ren (in) Provided SDL Renderer to use for display
 */
void UIManager::render(SDL_Renderer *ren) {
  if (GameManager::getInstance().getGameState() ==
      GameManager::getInstance().GameState::PreGame) {
    // Pregame UI
    SDL_RenderCopy(ren, background, nullptr, &bg_dest);
    SDL_RenderCopy(ren, title, nullptr, &title_dest);
    startButton->render(ren);
    languageButton->render(ren);
  } else if (GameManager::getInstance().getGameState() ==
             GameManager::getInstance().GameState::InGame) {
    auto scoreTex = ResourceManager::getInstance().getTextTexture(
        getScore(), fontType,
        {TITLE_TEXT_COLOR_RED, TITLE_TEXT_COLOR_GREEN, TITLE_TEXT_COLOR_BLUE,
         TITLE_TEXT_OPACITY},
        FPS_FONT_SIZE);
    SDL_QueryTexture(scoreTex, nullptr, nullptr, &score_dest.w, &score_dest.h);
    SDL_RenderCopy(ren, scoreTex, nullptr, &score_dest);
  } else if (GameManager::getInstance().getGameState() ==
             GameManager::getInstance().GameState::GameEnd) {
    SDL_RenderCopy(ren, background, nullptr, &bg_dest);

    // End game UI
    if (GameManager::getInstance().isGameWon()) {
      SDL_RenderCopy(ren, levelClear, nullptr, &levelClear_dest);
      nextLevelButton->render(ren);
    } else {
      SDL_RenderCopy(ren, gameOver, nullptr, &gameOver_dest);
    }
    returnButton->render(ren);
  } else if (GameManager::getInstance().getGameState() ==
             GameManager::getInstance().GameState::LanguageSelect) {
    SDL_RenderCopy(ren, background, nullptr, &bg_dest);
    englishButton->render(ren);
    spanishButton->render(ren);
    returnButtonMenus->render(ren);
  }

  fps_reader = ResourceManager::getInstance().getTextTexture(
      framerateModerator(), fontType,
      {TITLE_TEXT_COLOR_RED, TITLE_TEXT_COLOR_GREEN, TITLE_TEXT_COLOR_BLUE,
       TITLE_TEXT_OPACITY},
      FPS_FONT_SIZE);

  int w, h;
  SDL_QueryTexture(fps_reader, nullptr, nullptr, &w, &h);
  fps_dest.w = w;
  fps_dest.h = h;
  fps_dest.x = fpsXPadding;
  fps_dest.y = FPS_Y_PADDING;
  SDL_RenderCopy(ren, fps_reader, nullptr, &fps_dest);

  if (GameManager::getInstance().getGameState() !=
      GameManager::getInstance().GameState::InGame) {
    mouse->render(ren);
  }
}

std::string UIManager::framerateModerator() {
  const size_t FRAME_COUNT = 60;
  const size_t DESIRED_TICKS_PER_FRAME = 1000 / FRAME_COUNT;

  Uint32 currTicks = SDL_GetTicks();
  Uint32 elapsedTicks = currTicks - startTicks;

  if (elapsedTicks < DESIRED_TICKS_PER_FRAME) {
    SDL_Delay(DESIRED_TICKS_PER_FRAME - elapsedTicks);
    currTicks = SDL_GetTicks();
    elapsedTicks = currTicks - startTicks;
  }

  startTicks = currTicks;

  frameTimes.push_back(elapsedTicks);
  if (frameTimes.size() > FRAME_COUNT) {
    frameTimes.pop_front();
  }
  assert(frameTimes.size() >= 1);
  assert(frameTimes.size() <= FRAME_COUNT);

  float avgTicksPerFrame =
      std::accumulate(frameTimes.begin(), frameTimes.end(), 0.0f) /
      frameTimes.size();
  float avgFps = 1.0f / (avgTicksPerFrame / 1000.0f);

  std::stringstream sstr;
  sstr << std::fixed << std::setprecision(1) << "Current FPS: " << avgFps;

  return sstr.str();
}

void UIManager::checkButtons() {
  if (startButton->IsSelected()) {
    startButton->isClicked();
    GameManager::getInstance().startGame();
    GameManager::getInstance().setGameState(GameManager::GameState::InGame);
  } else if (returnButton->IsSelected()) {
    returnButton->isClicked();
    GameManager::getInstance().setGameState(GameManager::GameState::PreGame);
    GameManager::getInstance().clearLevel();
  } else if (languageButton->IsSelected()) {
    languageButton->isClicked();
    GameManager::getInstance().setGameState(
        GameManager::GameState::LanguageSelect);
  } else if (returnButtonMenus->IsSelected()) {
    returnButtonMenus->isClicked();
    GameManager::getInstance().setGameState(GameManager::GameState::PreGame);
  } else if (englishButton->IsSelected()) {
    englishButton->isClicked();
    language_ = Language::ENGLISH;
    startButton->changeLanguage(language_);
    returnButton->changeLanguage(language_);
    returnButtonMenus->changeLanguage(language_);
    languageButton->changeLanguage(language_);
    englishButton->changeLanguage(language_);
    spanishButton->changeLanguage(language_);
  } else if (spanishButton->IsSelected()) {
    spanishButton->isClicked();
    language_ = Language::SPANISH;
    startButton->changeLanguage(language_);
    returnButton->changeLanguage(language_);
    returnButtonMenus->changeLanguage(language_);
    languageButton->changeLanguage(language_);
    englishButton->changeLanguage(language_);
    spanishButton->changeLanguage(language_);
  }  else if (nextLevelButton->IsSelected()) {
    nextLevelButton->isClicked();
    GameManager::getInstance().updateLevel();
    GameManager::getInstance().startGame();
    GameManager::getInstance().setGameState(GameManager::GameState::InGame);
  }
}

std::string UIManager::getTranslation(const std::string &s) {
  return ResourceManager::getInstance().getTranslation(s, language_);
}

std::string UIManager::getLevelEndMessage() {
  return GameManager::getInstance().isGameWon()
             ? ResourceManager::getInstance().getTranslation(u8"LEVEL CLEARED!",
                                                             language_)
             : ResourceManager::getInstance().getTranslation(u8"YOU LOST",
                                                             language_);
}

std::string UIManager::getLevel() {
  return ResourceManager::getInstance().getTranslation(u8"Level", language_) +
         " " + std::to_string(GameManager::getInstance().getLevelVal());
}

std::string UIManager::getScore() {
  return ResourceManager::getInstance().getTranslation(u8"Score", language_) +
         " " + std::to_string(GameManager::getInstance().getScoreVal());
}