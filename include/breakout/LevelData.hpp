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
enum BreakoutBlockType {
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
enum BreakoutLevelItem {
  NONE,
  NOBLOCK = '.',
  PLAINBLOCK = 'b',
  // TILE1 = '1',
  // TILE2 = '2',
  // TILE3 = '3',
  // TILEX = 'X',
  // TILEY = 'Y',
  // TILEZ = 'Z',
  // BONES1,
  // BONES2,
  // BONES3,
  // ARROWSIGN,
  // BUSH1,
  // BUSH2,
  // CRATE,
  // DEADBUSH,
  // SIGN,
  // SKELETON,
  // TOMBSTONE1,
  // TOMEBSTONE2,
  // TREE,
  // JACK = 'P',
  // PATROLZOMBIE = 'E',
  // FOLLOWZOMBIE = 'F',
  WALL = 'w',
  HARDBLOCK = 'h',
  // KEY = 'K',
  EXIT = 'g',
};

/**
 * @brief Represents data of a single Block.
 * Can add color and more to be read from level file.
 */
struct BreakoutBlockData {
  BreakoutBlockType block_Type{PlainBlock};
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
