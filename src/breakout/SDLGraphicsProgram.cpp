// Support Code written by Michael D. Shah
// Updated by Seth Cooper
// Last Updated: Spring 2020
// Please do not redistribute without asking permission.

#include "SDLGraphicsProgram.hpp"

float avgFps;
std::string fontType = "Gageda.ttf";

/**
 * Log an SDL error with some error message to the output stream of our choice
 * @param os The output stream to write the message to
 * @param msg The error message to write, format will be msg error:
 * SDL_GetError()
 */
void logSDLError(std::ostream &os, const std::string &msg) {
  os << msg << " error: " << SDL_GetError() << std::endl;
}

/**
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, with some desired
 * width and height
 * @param tex The source texture we want to draw
 * @param ren The renderer we want to draw to
 * @param x The x coordinate to draw to
 * @param y The y coordinate to draw to
 * @param w The width of the texture to draw
 * @param h The height of the texture to draw
 */
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w,
                   int h) {
  // Setup the destination rectangle to be at the position we want
  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  dst.w = w;
  dst.h = h;
  SDL_RenderCopy(ren, tex, NULL, &dst);
}

/**
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
 * the texture's width and height
 * @param tex The source texture we want to draw
 * @param ren The renderer we want to draw to
 * @param x The x coordinate to draw to
 * @param y The y coordinate to draw to
 */
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
  int w, h;
  SDL_QueryTexture(tex, NULL, NULL, &w, &h);
  renderTexture(tex, ren, x, y, w, h);
}

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h)
    : screenHeight(h), screenWidth(w) {
  // Initialize random number generation.
  srand(time(NULL));

  // Initialization flag
  bool success = true;
  // String to hold any errors that occur.
  std::stringstream errorStream;
  // The window we'll be rendering to
  gWindow = NULL;
  // Render flag

  // Initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError()
                << "\n";
    success = false;
  }

  // Also need to init SDL_ttf
  if (TTF_Init() < 0) {
    errorStream << "TTF could not initialize! SDL Error: " << SDL_GetError()
                << "\n";
    // logSDLError(std::cout, "TTF_Init");
    SDL_Quit();
    success = false;
  }

  // Initialize SDL_mixer
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    errorStream << "SDL_mixer could not initialize! SDL_mixer Error: "
                << Mix_GetError() << "\n";
    success = false;
  }

  // Create window
  gWindow = SDL_CreateWindow("Breakout by Breakdown!", 100, 100, screenWidth,
                             screenHeight, SDL_WINDOW_SHOWN);

  // Check if Window did not create.
  if (gWindow == NULL) {
    errorStream << "Window could not be created! SDL Error: " << SDL_GetError()
                << "\n";
    success = false;
  }

  // Create a Renderer to draw on
  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
  // Check if Renderer did not create.
  if (gRenderer == NULL) {
    errorStream << "Renderer could not be created! SDL Error: "
                << SDL_GetError() << "\n";
    success = false;
  }

  ResourceManager::getInstance().startUp(gRenderer);
  GameManager::getInstance().startUp(screenWidth, screenHeight);

  // If initialization did not work, then print out a list of errors in the
  // constructor.
  if (!success) {
    errorStream << "Failed to initialize!\n";
    std::string errors = errorStream.str();
    std::cout << errors << "\n";
  } else {
#ifdef _DEBUG
    std::cout << "No SDL errors Detected in during init\n\n";
#endif  //_DEBUG
  }
}

// Proper shutdown and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram() {
  GameManager::getInstance().shutDown();
  ResourceManager::getInstance().shutDown();

  // Destroy Renderer
  SDL_DestroyRenderer(gRenderer);
  // Destroy window
  SDL_DestroyWindow(gWindow);
  Mix_CloseAudio();
  Mix_Quit();
  // Point gWindow to NULL to ensure it points to nothing.
  gRenderer = nullptr;
  gWindow = nullptr;
  // Quit SDL subsystems
  SDL_Quit();
}

// Update OpenGL
void SDLGraphicsProgram::update() {
  GameManager::getInstance().update();
}

// Render
// The render function gets called once per loop
void SDLGraphicsProgram::render() {
  SDL_SetRenderDrawColor(gRenderer, 0x22, 0x22, 0x22, 0xFF);
  SDL_RenderClear(gRenderer);

  GameManager::getInstance().render(gRenderer);
  renderUI();

  SDL_RenderPresent(gRenderer);
}

void SDLGraphicsProgram::renderUI() {
  SDL_Color color = {255, 255, 255, 0};

  {
    stringstream sstr;
    sstr << fixed << setprecision(3) << "FPS: " << avgFps;
    SDL_Texture *FPSText = ResourceManager::getInstance().getTextTexture(
        sstr.str(), fontType, color, 32);

    if (FPSText == nullptr) {
      if (!gRenderer) {
        return;
      }
      SDL_DestroyRenderer(gRenderer);

      if (!gWindow) {
        return;
      }
      SDL_DestroyWindow(gWindow);

      TTF_Quit();
      SDL_Quit();
      return;
    }

    int tiW, tiH;
    SDL_QueryTexture(FPSText, NULL, NULL, &tiW, &tiH);

    renderTexture(FPSText, gRenderer, screenWidth - 200, 10);
  }

  if (GameManager::getInstance().isGameStarted()) {
    SDL_Color color = {255, 255, 255, 0};

    SDL_Texture *levelText = ResourceManager::getInstance().getTextTexture(
        GameManager::getInstance().getLevel(), fontType, color, 45);
    SDL_Texture *scoreText = ResourceManager::getInstance().getTextTexture(
        GameManager::getInstance().getScore(), fontType, color, 45);
    SDL_Texture *livesText = ResourceManager::getInstance().getTextTexture(
        GameManager::getInstance().getLives(), fontType, color, 45);
    SDL_Texture *highScoreText = ResourceManager::getInstance().getTextTexture(
        GameManager::getInstance().getHighScore(), fontType, color, 45);

    if (levelText == nullptr || scoreText == nullptr || livesText == nullptr || highScoreText == nullptr) {
      if (!gRenderer) {
        return;
      }
      SDL_DestroyRenderer(gRenderer);

      if (!gWindow) {
        return;
      }
      SDL_DestroyWindow(gWindow);

      TTF_Quit();
      SDL_Quit();
      return;
    }

    // Get the texture w/h so we can center it in the screen
    int tiW, tiH;
    SDL_QueryTexture(levelText, NULL, NULL, &tiW, &tiH);
    SDL_QueryTexture(scoreText, NULL, NULL, &tiW, &tiH);
    SDL_QueryTexture(livesText, NULL, NULL, &tiW, &tiH);
    int tx = 10;

    // Render Text in top left.
    renderTexture(levelText, gRenderer, tx, 2);
    renderTexture(scoreText, gRenderer, tx, 42);
    renderTexture(livesText, gRenderer, tx, 82);
    renderTexture(highScoreText, gRenderer, tx, 122);
  } else if (GameManager::getInstance().getGameState() ==
  GameManager::GameState::GameEnd || GameManager::getInstance().getGameState() == GameManager::GameState::HighScoreEntry) {
    SDL_Texture *levelCompleteText =
        ResourceManager::getInstance().getTextTexture(GameManager::getInstance().getLevelEndMessage(),
            fontType, color, 64);
    SDL_Texture *scoreText = ResourceManager::getInstance().getTextTexture(
        GameManager::getInstance().getScore(), fontType, color, 64);


    if (scoreText == nullptr || levelCompleteText == nullptr) {
      if (!gRenderer) {
        return;
      }
      SDL_DestroyRenderer(gRenderer);

      if (!gWindow) {
        return;
      }
      SDL_DestroyWindow(gWindow);

      TTF_Quit();
      SDL_Quit();
      return;
    }

    int tiW, tiH;
    SDL_QueryTexture(scoreText, NULL, NULL, &tiW, &tiH);
    SDL_QueryTexture(levelCompleteText, NULL, NULL, &tiW, &tiH);

    renderTexture(levelCompleteText, gRenderer, screenWidth / 2 - (tiW / 2),
                  screenHeight / 2 - (2 * tiH));
    renderTexture(scoreText, gRenderer, screenWidth / 2 - (tiW / 2),
                  screenHeight / 2 - tiH);

    if (GameManager::getInstance().getGameState() == GameManager::GameState::HighScoreEntry) {
      std::string highScoreMessage = GameManager::getInstance().getTranslation(u8"New High Score!");
      SDL_Texture *highScoreMessageTexture = ResourceManager::getInstance().getTextTexture(
          highScoreMessage, fontType, color, 64);
      SDL_QueryTexture(highScoreMessageTexture, NULL, NULL, &tiW, &tiH);
      renderTexture(highScoreMessageTexture, gRenderer, screenWidth / 2 - (tiW / 2),
                    screenHeight / 2);
      std::string inputScoreMessage = GameManager::getInstance().getTranslation(u8"Enter your name:");
      std::string highScoreName = GameManager::getInstance().getHighScoreInputText();
      if (highScoreName.length() != 0)
        inputScoreMessage = inputScoreMessage + " " + highScoreName;
      SDL_Texture *highScoreNameTexture = ResourceManager::getInstance().getTextTexture(
          inputScoreMessage, fontType, color, 64);
      SDL_QueryTexture(highScoreNameTexture, NULL, NULL, &tiW, &tiH);
      renderTexture(highScoreNameTexture, gRenderer, screenWidth / 2 - (tiW / 2),
                    screenHeight / 2 + tiH);
    }



  }
}

// Loops forever!
void SDLGraphicsProgram::loop() {
  // Main loop flag
  // If this is quit = 'true' then the program terminates.
  bool quit = false;
  bool clearBlocks = false;
  // Event handler that handles various events in SDL
  // that are related to input and output
  SDL_Event e;
  // Enable text input
  SDL_StartTextInput();

  deque<Uint32> frameTimes;
  const size_t FRAME_COUNT = 60;
  size_t desiredFps = 60;

  Uint32 startTicks = SDL_GetTicks();
  Uint32 blockClearStartTicks = SDL_GetTicks();
  Uint32 elapsedTicks = 0;

  GameManager::getInstance().update();

  // Music Volume adjustment
  Mix_VolumeMusic(MIX_MAX_VOLUME / 6);
  Mix_PlayMusic(ResourceManager::getInstance().getMusic(
                    "251461__joshuaempyre__arcade-music-loop.wav"),
                -1);
  // While application is running
  while (!quit) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_RIGHT]) {
      GameManager::getInstance().movePaddleRight(elapsedTicks, screenWidth);
    } else if (state[SDL_SCANCODE_LEFT]) {
      GameManager::getInstance().movePaddleLeft(elapsedTicks, screenWidth);
    } else {
      GameManager::getInstance().stopPaddle();
    }
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
      // User posts an event to quit
      // An example is hitting the "x" in the corner of the window.
      if (e.type == SDL_QUIT) {
        quit = true;
      }
      // If user presses any key
      if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          // Terminate Program.
          case SDLK_q:
            if (GameManager::getInstance().getGameState() != GameManager::HighScoreEntry)
              quit = true;
            break;
          case SDLK_x:
            if (GameManager::getInstance().isGameStarted()) {
              GameManager::getInstance().clearBlock();
              clearBlocks = true;
            }
            break;
          case SDLK_BACKSPACE:
            if (GameManager::getInstance().getGameState() == GameManager::HighScoreEntry) {
              std::string highScoreEntryText = GameManager::getInstance().getHighScoreInputText();
              if (highScoreEntryText.length() > 0) {
                highScoreEntryText.pop_back();
                GameManager::getInstance().setHighScoreInputText(highScoreEntryText);
              }
            }
            break;
          default:
            break;
        }
      }

      // Enable typing when at high score entry screen
      if( e.type == SDL_TEXTINPUT )
      {
        if (GameManager::getInstance().getGameState() == GameManager::HighScoreEntry) {
          std::string highScoreEntryText = GameManager::getInstance().getHighScoreInputText();
          if (highScoreEntryText.length() < 3) {
            highScoreEntryText += e.text.text;
            GameManager::getInstance().setHighScoreInputText(highScoreEntryText);
          }
        }
      }

      // Mouse Clicks.
      if (e.type == SDL_MOUSEBUTTONUP) {
        GameManager::getInstance().checkButtons();
      }
    }

    Uint32 newBallTicks = SDL_GetTicks();
    if (GameManager::getInstance().isNeedNewBall()) {
      int newBallElapsedTicks =
          newBallTicks - GameManager::getInstance().getNeedNewBallTicks();
      if (newBallElapsedTicks > 2000) {
        GameManager::getInstance().spawnNewBall();
      }
    }

    Uint32 blockClearTicks = SDL_GetTicks();
    if (clearBlocks) {
      GameManager::getInstance().stopBall();
      GameManager::getInstance().stopPaddle();
      int blockClearElapsedTicks = blockClearTicks - blockClearStartTicks;
      if (blockClearElapsedTicks > 120) {
        GameManager::getInstance().clearBlock();
        blockClearStartTicks = SDL_GetTicks();
        if (GameManager::getInstance().getGameState() == GameManager::GameState::HighScoreEntry 
        || GameManager::getInstance().getGameState() == GameManager::GameState::GameEnd) {
          clearBlocks = false;
        }
      }
    }

    Uint32 DesiredTicksPerFrame = 1000 / desiredFps;

    // Update our scene
    update();

    // Render using OpenGL
    render();

    // Update screen of our specified window
    Uint32 currTicks = SDL_GetTicks();
    elapsedTicks = currTicks - startTicks;

    if (elapsedTicks < DesiredTicksPerFrame) {
      SDL_Delay(DesiredTicksPerFrame - elapsedTicks);
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
        accumulate(frameTimes.begin(), frameTimes.end(), 0.0f) /
        frameTimes.size();
    avgFps = 1.0f / (avgTicksPerFrame / 1000.0f);
  }

  // Disable text input
  SDL_StopTextInput();
}

// Get Pointer to Window
SDL_Window *SDLGraphicsProgram::getSDLWindow() { return gWindow; }

// Get Pointer to Renderer
SDL_Renderer *SDLGraphicsProgram::getSDLRenderer() { return gRenderer; }
