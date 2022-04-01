#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "base/SDL_DEBUG.hpp"
#include "base/ResourceManager.hpp"

/**
 * @brief A class representing a mouse cursor controllable by the user.
 */
class Mouse {
 public:
  SDL_Texture* texture_;
  SDL_Rect rect;
  SDL_Rect point;

  /**
   * @brief Construct an empty Mouse object, don't forget to call startUp().
   */
  Mouse() {}

  /**
   * @brief Destroy the Mouse object, don't forget to call shutDown().
   */
  ~Mouse() {}

  /**
   * @brief Initializes/configures this Mouse for use and display.
   */
  void startUp() {
    texture_ = ResourceManager::getInstance().getTexture("mouse/mouse.png");

    rect.w = 35;
    rect.h = 61;
    point.w = 1;
    point.h = 1;

    SDL_ShowCursor(false);
  }

  /**
   * @brief Cleans up this Mouse, 'equivalent' to our destructor.
   * @details Makes sure that any allocated resources are freed.
   */
  void shutDown() {}

  /**
   * @brief Gets the current Mouse cursor location on screen, from SDL.
   */
  void update() {
    SDL_GetMouseState(&rect.x, &rect.y);
    point.x = rect.x;
    point.y = rect.y;
  }

  /**
   * @brief Calls SDL Render to show Mouse cursor on screen.
   *
   * @param ren (in) an external SDL renderer to use
   */
  void render(SDL_Renderer* ren) {
    SDL_RenderCopy(ren, texture_, nullptr, &rect);
  }

#ifdef _TEST
  inline const bool getPointX() { return point.x; }
  inline const void setPointX(int x) { point.x = x; }
  inline const bool getPointY() { return point.y; }
  inline const void setPointY(int y) { point.y = y; }
#endif
};

#endif