// Support Code written by Michael D. Shah
// Updated by Seth Cooper
// Last Updated: Spring 2020
// Please do not redistribute without asking permission.

#ifndef SDL_GRAPHICS_PROGRAM_HPP
#define SDL_GRAPHICS_PROGRAM_HPP

// ==================== Libraries ==================
// Depending on the operating system we use
// The paths to SDL are actually different.
// The #define statement should be passed in
// when compiling using the -D argument.
// This gives an example of how a programmer
// may support multiple platforms with different
// dependencies.
//
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <time.h>

#include <cassert>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>

#include "base/SDL_DEBUG.hpp"
#include "base/ResourceManager.hpp"
#include "base/SDLProgramLogic.hpp"
#include "base/InputManager.hpp"

/**
 * @brief This class sets up a full graphics program
 */
class SDLGraphicsProgram {
 public:
  // Constructor
  /**
   * @brief Construct a new SDLGraphicsProgram within a new window.
   *
   * @param logic Logic of the program
   * @param w window width
   * @param h window height
   */
  SDLGraphicsProgram(const std::shared_ptr<SDLProgramLogic>& logic, int w, int h);

  /**
   * @brief Clean up the SDLGraphicsProgram object.
   */
  ~SDLGraphicsProgram();

  /**
   * @brief Updates the graphics program by one tick.
   */
  void update();

  /**
   * @brief Renders shapes to the screen.
   */
  void render();

  /**
   * @brief The main game/window loop.
   * @warning Will run forever until the user exits the window/program!
   */
  void loop();

  /**
   * @brief Get a pointer to the window used for this graphics program.
   *
   * @return SDL_Window* (out) pointer
   */
  SDL_Window* getSDLWindow();

  /**
   * @brief Get a pointer to the renderer used for this graphics program.
   *
   * @return SDL_Renderer* (out) pointer
   */
  SDL_Renderer* getSDLRenderer();

 private:
  // Screen dimension constants
  int screenHeight;
  int screenWidth;
  // The window we'll be rendering to
  SDL_Window* gWindow{nullptr};
  // SDL Renderer
  SDL_Renderer* gRenderer{nullptr};

  std::shared_ptr<SDLProgramLogic> gLogic{nullptr};
};

#endif
