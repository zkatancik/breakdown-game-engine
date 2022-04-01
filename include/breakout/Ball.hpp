#ifndef BALL_HPP
#define BALL_HPP

#include <SDL.h>
#include <SDL_image.h>
#include "base/GameObject.hpp"
#include <cassert>

#include "ResourceManager.hpp"
#include "TinyMath.hpp"
#include "resPath.hpp"

/**
 * @brief A class representing a moving ball in our game.
 */
class Ball {
 public:
  const int BALL_WIDTH = 30;
  const int BALL_HEIGHT = 30;

  /**
   * @brief Construct a new Ball object at position (x, y) and velocity (dx,
   * dy).
   * @details the specified position is the top left corner of a rectangle
   * around the ball image
   *
   * @param x coord
   * @param y coord
   * @param dx rate of change of x coord
   * @param dy rate of change of y coord
   */
  Ball(int x, int y, int dx, int dy);

  ~Ball();

  /**
   * @brief Updates the ball position based on current velocity.
   */
  void update();

  /**
   * @brief Renders the ball on screen.
   *
   * @param renderer (in) an external SDL renderer to use
   */
  void render(SDL_Renderer* renderer);

  /**
   * @brief Returns the ball's current central location.
   *
   * @return Vector2D<int> Current position [x, y]
   */
  Vector2D<int> getPosition() const;

  /**
   * @brief Returns the ball's current velocity.
   *
   * @return Vector2D<int> Current velocity [dx, dy]
   */
  Vector2D<float> getVelocity() const;

  /**
   * @brief Bounce the ball as if it just hit a horizontal wall.
   * @details Only changes the velocity, does not include a position update.
   */
  void bounceHWall();

  /**
   * @brief Bounce the ball as if it just hit a vertical wall.
   * @details Only changes the velocity, does not include a position update.
   */
  void bounceVWall();

  /**
   * @brief Stops the ball from moving
   *
   */
  void stop();

  /**
   * @brief Adds a velocity contribution to this ball's current velocity,
   * then rescales the current velocity so the magnitude remains the same
   * as before the addition.
   *
   * @param v the velocity to add to the current one
   */
  void nudgeVelocity(Vector2D<float> contrib);

 private:
  Vector2D<float> position_;  // Top-left corner of the ball texture
  Vector2D<float> velocity_;  // Current ball velocity

  SDL_Texture* texture_;  // External
  SDL_Rect dest_;  // Exclusively for where/how to render the texture on screen
};

#endif