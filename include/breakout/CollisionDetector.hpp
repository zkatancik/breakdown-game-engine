#ifndef COLLISION_DETECTOR_HPP
#define COLLISION_DETECTOR_HPP
#include "Ball.hpp"
#include "Block.hpp"
#include "Paddle.hpp"

/**
 * All collision detection goes here. The result of each function should be a
 * vector approximately normal to the point of collision. If no collision is
 * detected, a zero 2D vector is returned.
 */

/**
 * Detects collision between a paddle object and a ball object.
 * @param paddle Paddle object
 * @param ball Ball object
 * @return a Vector2D normal to the collision surface. If no collision is
 * detected, a zero 2D vector is returned.
 */
Vector2D<int> detect_collision(const Paddle& paddle, const Ball& ball);

/**
 * Detects collision between a paddle object and a ball object.
 * @param ball Ball object
 * @param paddle Paddle object
 * @return a Vector2D normal to the collision surface. If no collision is
 * detected, a zero 2D vector is returned.
 */
inline Vector2D<int> detect_collision(const Ball& ball, const Paddle& paddle) {
  return detect_collision(paddle, ball);
}

/**
 * Detects collision between a ball object and a block object.
 * @param ball Ball object
 * @param block Block object
 * @return a Vector2D normal to the collision surface. If no collision is
 * detected, a zero 2D vector is returned.
 */
Vector2D<int> detect_collision(const Ball& ball, const Block& block);

/**
 * Detects collision between a ball object and a block object.
 * @param block Block object
 * @param ball Ball object
 * @return a Vector2D normal to the collision surface. If no collision is
 * detected, a zero 2D vector is returned.
 */
inline Vector2D<int> detect_collision(const Block& block, const Ball& ball) {
  return detect_collision(ball, block);
}

#endif