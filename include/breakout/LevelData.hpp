#pragma once
#include <iostream>
#include <vector>
#include <filesystem>
#include "base/ResourceManager.hpp"
#include "base/ResPath.hpp"
namespace filesystem = std::filesystem;

/**
 * @brief The types of blocks possible.
 */
enum class BreakoutBlockType {
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
 * @brief The types of items present in a level.
 * - All the items you see in the LevelFile.
 */
enum class BreakoutLevelItem {
  NONE,
  NOBLOCK = '.',
  BLOCKBLUE = '1',
  BLOCKRED = '2',
  BLOCKYELLOW = '3',
  BLOCKGREEN = '4',
  BLOCKPURPLE = '5',
  WALL = 'w',
  HARDBLOCK = 'h',
};

/**
 * @brief Represents data of a single Block.
 * Can add color and more to be read from level file.
 */
struct BreakoutBlockData {
  BreakoutBlockType block_Type{BreakoutBlockType::PlainBlock};
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
struct BreakoutLevelData {
  int levelNumber{0};
  std::vector<std::vector<BreakoutLevelItem>> levelGrid;
  std::vector<BreakoutBlockData> blocks;
  int rowCount;
  int colCount;
  int numOfblocks;
};



/**
 * @brief Load Level file based on the level passed to the function.
 *
 * @param blockDataList levelData loaded from the file
 * @param level level number
 */
void loadLevel(BreakoutLevelData *levelData, int level);

void updateCurrentLevel(BreakoutLevelData *levelData, Vector2D<int> gridPosition, BreakoutLevelItem item);

void updateLevelFile(BreakoutLevelData ld, Vector2D<int> gridPosition, BreakoutLevelItem item);
