#ifndef GRAVERUNNER_LEVELDATA_HPP
#define GRAVERUNNER_LEVELDATA_HPP

#include <iostream>
#include <vector>

#include "base/TinyMath.hpp"

/**
 * @brief The types of blocks possible.
 */
enum class GraveRunnerBlockType {
  // Colored Block
  PlainBlock = 0,
  // Hole or No block
  NoBlock,
  // Unbreakable Block
  Wall,
  // Key to unlock the exit
  Key,
  // Exit of the Level (Also the goal)
  Exit
};

/**
 * @brief The types of items present in a level.
 * - All the items you see in the LevelFile.
 */
enum class GraveRunnerLevelItem {
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
  KEY = 'K',
  EXIT = 'G',
};

/**
 * @brief Represents data of a single Block.
 * Can add color and more to be read from level file.
 */
struct GraveRunnerBlockData {
  GraveRunnerBlockType block_Type{GraveRunnerBlockType::PlainBlock};
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
struct GraveRunnerLevelData {
  
  int levelNumber{0};
  
  std::vector<std::vector<GraveRunnerLevelItem>> levelGrid;
  
  std::vector<GraveRunnerBlockData> blocks;
  int rowCount;
  int colCount;
  Vector2D<int> blockSize;
  Vector2D<int> levelEndPosition{0, 0};
  Vector2D<int> playerStartPosition{0, 0};

  std::vector<Vector2D<int>> enemyStartPositions;
  std::vector<Vector2D<int>> followerEnemyStartPositions;
};

/**
 * @brief Load Level file based on the level passed to the function.
 *
 * @param blockDataList levelData loaded from the file
 * @param level level number
 */
void loadLevel(GraveRunnerLevelData *levelData, int level);

void updateCurrentLevel(GraveRunnerLevelData *levelData, Vector2D<int> gridPosition, GraveRunnerLevelItem item);

void updateLevelFile(GraveRunnerLevelData ld, Vector2D<int> gridPosition, GraveRunnerLevelItem item);

#endif