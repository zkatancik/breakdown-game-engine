#ifndef GRAVERUNNER_KEY_BLOCK_HPP
#define GRAVERUNNER_KEY_BLOCK_HPP

#include <SDL.h>

#include "base/GameObject.hpp"
#include "base/Level.hpp"
#include "graverunner/LevelData.hpp"

/**
 * @brief A class representing a Key collectible in our game.
 */
class KeyBlock : public GameObject {
 public:
  /**
   * @brief Creates a KeyBlock object.
   *
   * @param x the x screen coordinate (pixels) of where to render this Key
   * @param y the y screen coordinate (pixels) of where to render this Key
   * @param dims width, height dimensions (pixels)
   */
  KeyBlock(Level& level, float x, float y, Vector2D<int> dims);
};

#endif