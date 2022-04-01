#ifndef LEVELDATA_HPP
#define LEVELDATA_HPP

#include <iostream>
#include <vector>

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
};

/**
 * @brief Represents data of a single Block.
 * Can add color and more to be read from level file.
 */
struct BlockData {
  BlockType block_Type{PlainBlock};
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
  std::vector<BlockData> blocks;
  int rowCount;
  int colCount;
  int numOfblocks;
};

#endif