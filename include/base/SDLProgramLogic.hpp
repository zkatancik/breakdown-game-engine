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

  std::string framerateModerator() {
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
 private:
  std::deque<Uint32> frameTimes;
  Uint32 startTicks;
};

#endif
