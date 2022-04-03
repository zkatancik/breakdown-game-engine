#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <SDL.h>
#include <set>

//! \brief Class for managing (keyboard) input.
class InputManager {
private:

  InputManager() = default; // Private Singleton
  InputManager(InputManager const&) = delete; // Avoid copy constructor.
  void operator=(InputManager const&) = delete; // Don't allow copy assignment.
  
public:

  static InputManager &getInstance(); //!< Get the instance.

  void startUp();
  void shutDown();

  void resetForFrame(); //!< Reset key state for a new frame.
  void handleEvent(const SDL_Event & e); //!< Update key state based on an event.
  bool isKeyDown(SDL_Keycode k) const; //!< Get if a key is currently down.
  bool isKeyPressed(SDL_Keycode k) const; //!< Get if a key was pressed this frame.
  bool isMouseKeyDown(uint8_t mk) const; //!< Get if a mouse key is currently down.
  bool isMouseKeyPressed(uint8_t mk) const; //!< Get if a mouse key was pressed this frame.
  
private:

  std::set<SDL_Keycode> mKeysDown;
  std::set<SDL_Keycode> mKeysPressed;
  std::set<uint8_t> mMouseKeysDown;
  std::set<uint8_t> mMouseKeysPressed;
};

#endif //INPUT_MANAGER_HPP