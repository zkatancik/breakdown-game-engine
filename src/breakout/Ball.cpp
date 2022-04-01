#include "breakout/Ball.hpp"

Ball::Ball(int x, int y, int dx, int dy) {
  position_ = Vector2D(x, y);
  velocity_ = Vector2D(dx, dy);
  texture_ = ResourceManager::getInstance().getTexture("ballGrey.png");
  dest_.w = BALL_WIDTH;
  dest_.h = BALL_HEIGHT;
}

Ball::~Ball() {}

void Ball::update() { position_ += velocity_; }

void Ball::render(SDL_Renderer *renderer) {
  assert(texture_ != nullptr);
  dest_.x = position_.x;
  dest_.y = position_.y;

  int code = SDL_RenderCopy(renderer, texture_, NULL, &dest_);
  if (code != 0) {
    std::cerr << "Failed to RenderCopy: " << SDL_GetError() << "\n";
  }
}

Vector2D<int> Ball::getPosition() const {
  Vector2D<float> tmp = position_ + Vector2D<float>(dest_.w / 2, dest_.h / 2);
  return Vector2D<int>(tmp.x, tmp.y);
}

Vector2D<float> Ball::getVelocity() const {
  return Vector2D<float>(velocity_.x, velocity_.y);
}

void Ball::nudgeVelocity(Vector2D<float> contrib) {
  float oldBallVelMagnitude = Magnitude(velocity_);
  // Make contribution
  velocity_ += contrib;
  float newBallVelMagnitude = Magnitude(velocity_);
  // Rescale ball velocity to have same magnitude as originally (note, direction
  // will have changed)
  velocity_ *= (oldBallVelMagnitude / newBallVelMagnitude);
}

void Ball::bounceHWall() {
  velocity_ = Vector2D(velocity_.x, -1 * velocity_.y);
}

void Ball::bounceVWall() {
  velocity_ = Vector2D(-1 * velocity_.x, velocity_.y);
}

void Ball::stop() { velocity_ = Vector2D(0, 0); }
