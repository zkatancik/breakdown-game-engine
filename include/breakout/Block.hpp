#ifndef BREAKOUT_BLOCK_HPP
#define BREAKOUT_BLOCK_HPP

#include <SDL.h>

#include <vector>
#include <base/TextureRenderComponent.hpp>
#include "base/PerformHookOnCollideComponent.hpp"
#include "breakout/LevelData.hpp"
#include "base/ResourceManager.hpp"
#include "base/GameObject.hpp"
#include "breakout/Tag.hpp"
#include "base/Level.hpp"
#include "base/HealthComponent.hpp"

/**
 * @brief A class representing a Block in our game, with various options (see
 * BlockType).
 */
class BreakoutBlock : public GameObject {
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
  BreakoutBlock(Level& level, float x, float y, BreakoutBlockData bd, int h);

  BreakoutBlockType getBlockType() const {return blockData.block_Type;};

 private:
  std::shared_ptr<TextureRenderComponent> renderer_;
  std::shared_ptr<HealthComponent> healthComponent_;
  BreakoutBlockData blockData;

  static SDL_Texture *getBlockTexture(const std::string &name)
  {
    return ResourceManager::getInstance().getTexture(
        (std::filesystem::path("2DBreakout/Graphics/") /
         ("element_rectangle_" + name + ".png"))
            .u8string());
  }

};

#endif