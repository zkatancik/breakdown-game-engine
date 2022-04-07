#ifndef GRAVERUNNER_EXIT_BLOCK_HPP
#define GRAVERUNNER_EXIT_BLOCK_HPP

#include <SDL.h>

#include "base/GameObject.hpp"
#include "base/Level.hpp"
#include "graverunner/LevelData.hpp"

/**
 * @brief A class representing an exit in our game.
 */
class ExitBlock : public GameObject {
 public:
  /**
   * @brief Creates an ExitBlock object.
   *
   * @param x the x screen coordinate (pixels) of where to render this Key
   * @param y the y screen coordinate (pixels) of where to render this Key
   * @param dims width, height dimensions (pixels)
   */
  ExitBlock(Level& level, float x, float y, Vector2D<int> dims);
};

#endif