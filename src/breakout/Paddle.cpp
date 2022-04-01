#include "Paddle.hpp"

#include "ResourceManager.hpp"

void Paddle::startUp(int sw, int sh, int speed, int width) {
  initPaddle(sw, sh, speed, width);
}

void Paddle::shutDown() {
  // Textures is deleted by the ResourceManager.
}

void Paddle::initPaddle(int sw, int sh, int speed, int width) {
  texture_ = ResourceManager::getInstance().getTexture("paddleRed.png");
  paddleSpeed = speed;
  paddleWidth = width;

  position_ = Vector2D(sw / 2 - (paddleWidth / 2), sh - 50);
  velocity_ = Vector2D(paddleSpeed, 0);
}

void Paddle::MoveLeft(uint32_t deltaT, int sw) {
  velocity_ = Vector2D(-1 * paddleSpeed, 0);
  position_ += velocity_;
  if (position_.x <= 0) {
    position_.x = 0;
  }
}

void Paddle::MoveRight(uint32_t deltaT, int sw) {
  velocity_ = Vector2D(paddleSpeed, 0);
  position_ += velocity_;

  if (position_.x + paddleWidth > sw) {
    position_.x = sw - paddleWidth;
  }
}

int Paddle::getPaddleWidth() const { return paddleWidth; }

void Paddle::stop() { velocity_ = Vector2D(0, 0); }

void Paddle::render(SDL_Renderer *renderer) {
  Dest.w = paddleWidth;
  Dest.h = PADDLE_HEIGHT;
  Dest.x = position_.x;
  Dest.y = position_.y;
  SDL_RenderCopy(renderer, texture_, nullptr, &Dest);
}
