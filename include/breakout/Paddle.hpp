#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SDL.h>
#include <base/TextureRenderComponent.hpp>
#include "base/GameObject.hpp"
#include "breakout/Tag.hpp"
#include "breakout/InputBreakoutComponent.hpp"

/**
 * @brief A class representing a user-controllable Paddle.
 */
class Paddle : public GameObject {
 public:
  Paddle(Level& level, float sw, float sh, float width, float speed);


 private:
  std::shared_ptr<TextureRenderComponent> mRenderer;
};

#endif