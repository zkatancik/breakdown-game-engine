// Support Code written by Michael D. Shah
// Updated by Seth Cooper
// Last Updated: Spring 2020
// Please do not redistribute without asking permission.

#include "base/SDLGraphicsProgram.hpp"

// Initialization function
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(std::shared_ptr<SDLProgramLogic> logic, int w, int h)
    : screenHeight(h), screenWidth(w), gLogic(logic) {
  // Initialize random number generation.
  srand(time(NULL));

  // Initialization flag
  bool success = true;
  // String to hold any errors that occur.
  std::stringstream errorStream;
  // The window we'll be rendering to
  gWindow = nullptr;

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
  gWindow = SDL_CreateWindow("GraveRunner", 100, 100, screenWidth, screenHeight,
                             SDL_WINDOW_SHOWN);

  // Check if Window did not create.
  if (gWindow == nullptr) {
    errorStream << "Window could not be created! SDL Error: " << SDL_GetError()
                << "\n";
    success = false;
  }

  // Create a Renderer to draw on
  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
  // Check if Renderer did not create.
  if (gRenderer == nullptr) {
    errorStream << "Renderer could not be created! SDL Error: "
                << SDL_GetError() << "\n";
    success = false;
  }

  // If initialization did not work, then print out a list of errors in the
  // constructor.
  if (!success) {
    errorStream << "Failed to initialize!\n";
    std::string errors = errorStream.str();
    std::cerr << errors << "\n";
  } else {
#ifdef _DEBUG
    std::cout << "No SDL errors Detected in during init\n\n";
#endif  //_DEBUG
  }

  ResourceManager::getInstance().startUp(gRenderer);
  gLogic->startUp(gRenderer, screenWidth, screenHeight);
  InputManager::getInstance().startUp();
}

// Proper shutdown and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram() {
  InputManager::getInstance().shutDown();
  ResourceManager::getInstance().shutDown();
  gLogic->shutDown();

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
  gLogic->update();
}

// Render
// The render function gets called once per loop
void SDLGraphicsProgram::render() {
  SDL_SetRenderDrawColor(gRenderer, 0x22, 0x22, 0x22, 0xFF);
  SDL_RenderClear(gRenderer);
  gLogic->render(gRenderer);
  SDL_RenderPresent(gRenderer);
}

// Loops forever!
void SDLGraphicsProgram::loop() {
  // Event handler that handles various events in SDL
  // that are related to input and output
  SDL_Event e;
  // Enable text input
  SDL_StartTextInput();

  bool quit = false;

  // Initial update
  update();

  // While application is running
  while (!quit) {
    InputManager::getInstance().resetForFrame();

    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
      // User posts an event to quit
      // An example is hitting the "x" in the corner of the window.
      if (e.type == SDL_QUIT) {
        quit = true;
      }
      InputManager::getInstance().handleEvent(e);

      if (InputManager::getInstance().isKeyDown(SDLK_q)) {
        quit = true;
      }
      // Mouse Clicks.
      if (e.type == SDL_MOUSEBUTTONUP) {
        gLogic->checkButtons();
      }
    }

    // Update our scene
    update();

    // Render using OpenGL
    render();
  }

  // Disable text input
  SDL_StopTextInput();
}

// Get Pointer to Window
SDL_Window *SDLGraphicsProgram::getSDLWindow() { return gWindow; }

// Get Pointer to Renderer
SDL_Renderer *SDLGraphicsProgram::getSDLRenderer() { return gRenderer; }