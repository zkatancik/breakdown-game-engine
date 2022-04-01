#ifndef LEVELDATA_HPP
#define LEVELDATA_HPP

#include <iostream>
#include <vector>

#include "base/TinyMath.hpp"

static const int TAG_PLAYER = 1;
static const int TAG_GOAL   = 2;
static const int TAG_BLOCK  = 3;
static const int TAG_ENEMY = 4;

/**
 * @brief The types of blocks possible.
 */
enum BlockType {
  // Colored Block
  PlainBlock = 0,
  // Hole or No block
  NoBlock,
  // Unbreakable Block
  Wall,
  // Plain Block with health (multiple hits to destroy)
  HardBlock,
  // Heart
  Heart,
  // Key to unlock the exit
  Key,
  // Exit of the Level (Also the goal)
  Exit
};

/**
 * @brief The types of items present in a level.
 * - All the items you see in the LevelFile.
 */
enum LevelItem {
  NONE,
  NOBLOCK = '.',
  TILE1 = '1',
  TILE2 = '2',
  TILE3 = '3',
  TILEX = 'X',
  TILEY = 'Y',
  TILEZ = 'Z',
  BONES1,
  BONES2,
  BONES3,
  ARROWSIGN,
  BUSH1,
  BUSH2,
  CRATE,
  DEADBUSH,
  SIGN,
  SKELETON,
  TOMBSTONE1,
  TOMEBSTONE2,
  TREE,
  JACK = 'P',
  PATROLZOMBIE = 'E',
  FOLLOWZOMBIE = 'F',
  WALL = 'W',
  HARDBLOCK = 'H',
  KEY = 'K',
  EXIT = 'G',
};

/**
 * @brief Represents data of a single Block.
 * Can add color and more to be read from level file.
 */
struct BlockData {
  BlockType block_Type{PlainBlock};
  std::string blockNumber;
};

/**
 * @brief Has the data read from Level file.
 *
 * Level file data format:
 * row 1 - Row count
 * row 2 - Col Count
 * row 3 - Minimum number of Blocks to clear a level
 * row 4 onwards - List of Blocks, organized in rows
 */
struct LevelData {
  
  int levelNumber{0};
  
  std::vector<std::vector<LevelItem>> levelGrid;
  
  std::vector<BlockData> blocks;
  int rowCount;
  int colCount;
  Vector2D<int> blockSize;
  Vector2D<int> levelEndPosition{0, 0};
  Vector2D<int> playerStartPosition{0, 0};

  std::vector<Vector2D<int>> enemyStartPositions;
  std::vector<Vector2D<int>> followerEnemyStartPositions;
};

#endif