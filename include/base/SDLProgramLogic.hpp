#ifndef SDL_PROGRAM_LOGIC_HPP
#define SDL_PROGRAM_LOGIC_HPP
#include <SDL_render.h>

/**
 * @brief An interface for wrapping an SDL program's logic to get finer grained control over the subsystems used and
 * create arbitrary SDL programs
 */
class SDLProgramLogic {
 public:
  SDLProgramLogic()= default;
  SDLProgramLogic(SDLProgramLogic const&) = delete; // Avoid copy constructor.
  void operator=(SDLProgramLogic const&) = delete; // Don't allow copy assignment.

  virtual void startUp(SDL_Renderer* gRender, int width, int height) = 0; //!< Start up any required subsystems

  virtual void shutDown() = 0; //!< Shutdown all subsystems + cleanup

  virtual void update() = 0; //!< Update all systems

  virtual void render(SDL_Renderer* render) = 0; //!< Render

  virtual void checkButtons() = 0;
};

#endif
