#include "Block.hpp"

#include "ResourceManager.hpp"

using namespace std;

void Block::startUp(int x, int y, int color, BlockData bd, int h) { init(x, y, color, bd, h); }

void Block::shutDown() {}

void Block::init(int xCoord, int yCoord, int c, BlockData bd, int h) {
  Dest.x = xCoord;
  Dest.y = yCoord;
  Dest.w = 64;
  Dest.h = 32;

  blockData = bd;
  health = h;

  if (0 <= c && c < 5) {
    texture_ = ResourceManager::getInstance().getTexture(colorMap[c]);
  } else if (c == 5) {
    texture_ = ResourceManager::getInstance().getTexture("element_grey_rectangle.png");
  } else if (c == 6) {
    texture_ = ResourceManager::getInstance().getTexture("element_wall_rectangle.png");
  }
}

bool Block::reduceHealth () {
  if (health > 0) {
    health--;

    //Texture updates
    if (blockData.block_Type == BlockType::HardBlock)
    {
      //TODO: Should I unload old texture?
      if (health == 2) {
        texture_ = ResourceManager::getInstance().getTexture("element_grey_health_2_rectangle.png");
      } else if (health == 1) {
        texture_ = ResourceManager::getInstance().getTexture("element_grey_health_1_rectangle.png");
      }
    }
  }
  
  return (health == 0);
}

void Block::render(SDL_Renderer *renderer) {
  SDL_RenderCopy(renderer, texture_, nullptr, &Dest);
}