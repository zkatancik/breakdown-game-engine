#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <SDL.h>

#include <vector>

#include "LevelData.hpp"
#include "SDL_DEBUG.hpp"
#include "TinyMath.hpp"

/**
 * @brief A class representing a Block in our game, with various options (see
 * BlockType).
 */
class Block {
 public:
  /**
   * @brief Default constructor, don't forget to call startup()
   */
  Block() = default;

  /**
   * @brief Default destructor, don't forget to call shutdown()
   */
  ~Block() = default;

  /**
   * @brief Creates a Block object to be destroyed by a ball
   *
   * @param x the location of the Block to renders' x screen position in pixels
   * @param y the location of the Block to render's y screen position in pixels
   * @param color the color as coded in our color array (0-4)(5 for wall)
   * @param bd Blockdata read from LevelData
   * @param h Block health based on BlockType
   */
  void startUp(int x, int y, int color, BlockData bd, int h);

  /**
   * @brief Cleans up and runs shut down logic when Block is to be destroyed.
   */
  void shutDown();

  /**
   * @brief Calls SDL Render to show Block on screen.
   *
   * @param renderer (in) an external SDL renderer to use
   */
  void render(SDL_Renderer *renderer);

  /**
   * @brief Get the center of the Block.
   *
   * @return Vector2D<int> location of the center as a position vector (world
   * space)
   */
  inline Vector2D<int> getCenter() const {
    return {Dest.x + Dest.w / 2, Dest.y + Dest.h / 2};
  };

  /**
   * @brief Get the dimensions of the Block.
   *
   * @return Vector2D<int> width and height (respectively) of this Block
   */
  inline Vector2D<int> getDims() const { return {Dest.w, Dest.h}; };

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
  void init(int xCoord, int yCoord, int c, BlockData bd, int h);

  SDL_Texture *texture_ = nullptr;
  SDL_Rect Dest;

  BlockData blockData;
  int health;

  static inline const std::string colorMap[5] = {
      "element_yellow_rectangle.png", "element_green_rectangle.png",
      "element_blue_rectangle.png", "element_purple_rectangle.png",
      "element_red_rectangle.png"};
};

#endif