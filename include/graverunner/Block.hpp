#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <SDL.h>

#include <filesystem>
#include <map>

#include "base/GameObject.hpp"
#include "base/SDL_DEBUG.hpp"
#include "base/TinyMath.hpp"
#include "graverunner/LevelData.hpp"
#include "base/ResourceManager.hpp"
#include "graverunner/Tag.hpp"

/**
 * @brief A class representing a Block in our game, with various options (see
 * BlockType).
 */
class Block : public GameObject
{
public:
  /**
   * @brief Default constructor, don't forget to call startup()
   */
  Block(Level& level) : GameObject(level) {};

  /**
   * @brief Creates a Block object to be destroyed by a ball
   *
   * @param x the location of the Block to renders' x screen position in pixels
   * @param y the location of the Block to render's y screen position in pixels
   * @param bd Blockdata read from LevelData
   * @param h Block health based on BlockType
   * @param bs block size
   */
  Block(Level& level, float x, float y, BlockData bd, int h, Vector2D<int> bs);
  
  /**
   * @brief Default destructor, don't forget to call shutdown()
   */
  ~Block() = default;

  /**
   * @brief Get the center of the Block.
   *
   * @return Vector2D<int> location of the center as a position vector (world
   * space)
   */
  inline Vector2D<int> getCenter() const
  {
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
  void init(int xCoord, int yCoord, BlockData bd, int h, Vector2D<int> bs);

  static SDL_Texture *getBlockTexture(const std::string &name)
  {
    return ResourceManager::getInstance().getTexture(
        (std::filesystem::path("Graverunner/graveyardtiles/png/Tiles/") /
         ("Tile" + name + ".png"))
            .string());
  }

  SDL_Texture *texture_ = nullptr;
  SDL_Rect Dest;

  BlockData blockData;
  int health;
};
#endif