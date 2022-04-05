#ifndef BALL_HPP
#define BALL_HPP

#include <SDL.h>
#include <SDL_image.h>
#include "base/GameObject.hpp"
#include "base/TextureRenderComponent.hpp"
#include "base/PhysicsComponent.hpp"
#include "base/ResourceManager.hpp"
#include "base/Tag.hpp"
#include "breakout/Tag.hpp"

/**
 * @brief A class representing a moving ball in our game.
 */
class Ball : public GameObject {
 public:

  /**
   * @brief Construct a new Ball object at position (x, y) and velocity (dx,
   * dy).
   * @details the specified position is the top left corner of a rectangle
   * around the ball image
   *
   * @param level the Level object the ball belongs to
   * @param x coord
   * @param y coord
   * @param dx rate of change of x coord
   * @param dy rate of change of y coord
   */
  Ball(Level& level, float x, float y, float dx, float dy);


  /**
   * @brief Stops the ball from moving
   *
   */
  void stop();

 private:
  std::shared_ptr<TextureRenderComponent> renderer_;
};

#endif