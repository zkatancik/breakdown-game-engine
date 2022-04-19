#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SDL.h>

#include "base/GameObject.hpp"
#include "base/PerformHookOnCollideComponent.hpp"
#include "base/ResourceManager.hpp"
#include "base/TextureRenderComponent.hpp"
#include "breakout/InputBreakoutComponent.hpp"
#include "breakout/Tag.hpp"

/**
 * @brief A class representing a user-controllable Paddle.
 */
class Paddle : public GameObject {
 public:
  /**
   * @brief Construct a new Paddle object
   *
   * @param level level information
   * @param sw screen width, will center the paddle on it horizontally
   * @param sh screen heigh, will place paddle a little above the bottom edge of
   * the screen
   * @param width paddle width
   * @param speed paddle speed
   */
  Paddle(Level& level, float sw, float sh, float width, float speed);

 private:
  std::shared_ptr<TextureRenderComponent> mRenderer;
};

#endif