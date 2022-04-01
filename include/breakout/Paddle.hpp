#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SDL.h>

#include "SDL_DEBUG.hpp"
#include "TinyMath.hpp"

/**
 * @brief A class representing a user-controllable Paddle in our game.
 */
class Paddle {
 public:
  // const int PADDLE_WIDTH = 104;
  const int PADDLE_HEIGHT = 24;
  // const int PADDLE_SPEED = 7;

  /**
   * @brief Construct an empty Paddle object, don't forget to call startUp().
   */
  Paddle() {}

  /**
   * @brief Destroy the Paddle object, don't forget to call shutDown().
   */
  ~Paddle() {}

  /**
   * @brief Acts as a Constructor for the Paddle.
   *
   * @param sw Screen Width
   * @param sh Screen Height
   */
  void startUp(int sw, int sh, int speed, int width);

  /**
   * @brief Cleans up this Paddle, 'equivalent' to our destructor.
   * @details Makes sure that any allocated resources are freed.
   */
  void shutDown();

  /**
   * @brief Initializes/Configures the Paddle.
   *
   * @param sw Screen Width
   * @param sh Screen Height
   */
  void initPaddle(int sw, int sh, int speed, int width);

  /**
   * @brief Moves the Paddle horizontally left.
   *
   * @param deltaT deltaT from the SDL Update. Elapsed seconds between frames.
   * @param sw screen width
   */
  void MoveLeft(uint32_t deltaT, int sw);

  /**
   * @brief Moves the Paddle Right horizontally right.
   *
   * @param deltaT deltaT from the SDL Update. Elapsed seconds between frames.
   * @param sw screen width
   */
  void MoveRight(uint32_t deltaT, int sw);

  /**
   * @brief Returns the Paddle's current velocity.
   *
   * @return Vector2D<int> Current velocity [dx, dy]
   */
  inline Vector2D<int> getVelocity() const { return velocity_; }

  int getPaddleWidth() const;

  /**
   * @brief Stops the paddle from moving (velocity is zero).
   */
  void stop();

  /**
   * @brief Renders the Paddle
   *
   * @param renderer SDL main loop renderer reference.
   */
  void render(SDL_Renderer* renderer);

  inline Vector2D<int> getCenter() const {
    return {Dest.x + Dest.w / 2, Dest.y + Dest.h / 2};
  }


 private:
  SDL_Texture* texture_ = nullptr;
  Vector2D<int> position_;  // Top-left corner of the ball texture
  Vector2D<int> velocity_;

  // SDL_Rect Src;
  SDL_Rect Dest;

  int paddleSpeed;
  int paddleWidth;
};

#endif