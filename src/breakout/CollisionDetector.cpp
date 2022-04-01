#include "CollisionDetector.hpp"

Vector2D<int> detect_collision(const Paddle& jack, const Ball& block) {
  auto jackCenter = jack.getCenter();

  int jackXMin = jackCenter.x - jack.getPaddleWidth() / 2;
  int jackXMax = jackCenter.x + jack.getPaddleWidth() / 2;

  int jackYMin = jackCenter.y - jack.PADDLE_HEIGHT / 2;
  int jackYMax = jackCenter.y + jack.PADDLE_HEIGHT / 2;

  auto blockCenter = block.getPosition();
  int blockXMin = blockCenter.x - block.BALL_WIDTH / 2;
  int blockXMax = blockCenter.x + block.BALL_WIDTH / 2;

  int blockYMin = blockCenter.y - block.BALL_HEIGHT / 2;
  int blockYMax = blockCenter.y + block.BALL_HEIGHT / 2;

  // collision detection here
  if (  // Check for rectangle overlap on the x side
      ((jackXMin < blockXMin && blockXMin < jackXMax) ||
       (blockXMin < jackXMin && jackXMin < blockXMax)) &&
      // Check for rectangle overlap on the y side
      ((jackYMin < blockYMin && blockYMin < jackYMax) ||
       (blockYMin < jackYMin && jackYMin < blockYMax))) {
    int xOverlap =
        jackXMin < blockXMin ? jackXMax - blockXMin : blockXMax - jackXMin;
    int yOverlap =
        jackYMin < blockYMin ? jackYMax - blockYMin : blockYMax - jackYMin;
    if (xOverlap > yOverlap)
      return {1, 0};
    else
      return {0, 1};
  }

  return {0, 0};
}

Vector2D<int> detect_collision(const Ball& ball, const Block& block) {
  auto blockCenter = block.getCenter();
  auto blockDims = block.getDims();
  int blockXMin = blockCenter.x - blockDims.x / 2;
  int blockXMax = blockCenter.x + blockDims.x / 2;

  int blockYMin = blockCenter.y - blockDims.y / 2;
  int blockYMax = blockCenter.y + blockDims.y / 2;

  auto ballCenter = ball.getPosition();
  int ballXMin = ballCenter.x - ball.BALL_WIDTH / 2;
  int ballXMax = ballCenter.x + ball.BALL_WIDTH / 2;

  int ballYMin = ballCenter.y - ball.BALL_HEIGHT / 2;
  int ballYMax = ballCenter.y + ball.BALL_HEIGHT / 2;

  // collision detection here
  if (  // Check for rectangle overlap on the x side
      ((blockXMin < ballXMin && ballXMin < blockXMax) ||
       (ballXMin < blockXMin && blockXMin < ballXMax)) &&
      // Check for rectangle overlap on the y side
      ((blockYMin < ballYMin && ballYMin < blockYMax) ||
       (ballYMin < blockYMin && blockYMin < ballYMax))) {
    int xOverlap =
        blockXMin < ballXMin ? blockXMax - ballXMin : ballXMax - blockXMin;
    int yOverlap =
        blockYMin < ballYMin ? blockYMax - ballYMin : ballYMax - blockYMin;
    if (xOverlap > yOverlap)
      return {1, 0};
    else
      return {0, 1};
  }

  return {0, 0};
}