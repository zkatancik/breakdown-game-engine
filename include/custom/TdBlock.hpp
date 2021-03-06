#ifndef TD_BLOCK_HPP
#define TD_BLOCK_HPP

#include <SDL.h>

#include <filesystem>
#include <map>

#include "base/GameObject.hpp"
#include "base/ResourceManager.hpp"
#include "base/SDL_DEBUG.hpp"
#include "base/TinyMath.hpp"
#include "custom/LevelData.hpp"
#include "custom/Tag.hpp"

/**
 * @brief A class representing a Block in our game, with various options (see
 * BlockType).
 */
class TdBlock : public GameObject {
 public:
  /**
   * @brief Creates a Block object to be destroyed by a ball
   *
   * @param x the location of the Block to renders' x screen position in pixels
   * @param y the location of the Block to render's y screen position in pixels
   * @param bd Blockdata read from LevelData
   * @param bs block size
   * @param tag override default block tag with this one
   */
  TdBlock(Level &level, float x, float y, TdBlockData bd, Vector2D<int> bs,
          int tag = TdBlockTag);

  /**
   * @brief Default destructor, don't forget to call shutdown()
   */
  ~TdBlock() = default;

  /**
   * @brief Get configuration data about this Block.
   *
   * @return blockData about this Block
   */
   inline TdBlockData getBlockData() const { return blockData; };

 private:
  void init(int xCoord, int yCoord, TdBlockData bd, Vector2D<int> bs);

  /**
   * @brief Helper to get the proper texture for this block.
   *
   * @return SDL_Texture* the texture this block should use
   */
  SDL_Texture *getBlockTexture();

  SDL_Texture *texture_ = nullptr;
  SDL_Rect Dest;

  TdBlockData blockData;
};
#endif