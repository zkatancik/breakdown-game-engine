#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <SDL.h>

#include <vector>
#include <base/TextureRenderComponent.hpp>
#include "base/PerformHookOnCollideComponent.hpp"
#include "LevelData.hpp"
#include "base/ResourceManager.hpp"
#include "base/GameObject.hpp"
#include "breakout/Tag.hpp"
#include "SDL_DEBUG.hpp"
#include "TinyMath.hpp"

/**
 * @brief A class representing a Block in our game, with various options (see
 * BlockType).
 */
class Block : public GameObject {
 public:
  /**
 * @brief Creates a Block object to be destroyed by a ball
 *
 * @param x the location of the Block to renders' x screen position in pixels
 * @param y the location of the Block to render's y screen position in pixels
 * @param color the color as coded in our color array (0-4)(5 for wall)
 * @param bd Blockdata read from LevelData
 * @param h Block health based on BlockType
 */
  Block(Level& level, float x, float y, int color, BlockData bd, int h);

  /**
   * @brief Get configuration data about this Block.
   *
   * @return blockData about this Block
   */
  inline BlockData getBlockData() const { return blockData; };

  /**
   * @brief Reduce the health of a Block.
   *
   * @return true if health becomes 0
   * @return false otherwise
   */
  bool reduceHealth();

 private:
  std::shared_ptr<TextureRenderComponent> renderer_;
  BlockData blockData;
  int health;

  static inline const std::string colorMap[7] = {
      "element_yellow_rectangle.png", "element_green_rectangle.png",
      "element_blue_rectangle.png", "element_purple_rectangle.png",
      "element_red_rectangle.png", "element_grey_rectangle.png", "element_wall_rectangle.png"};
};

#endif