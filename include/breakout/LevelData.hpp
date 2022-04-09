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

///**
// * @brief Update the item in the current level.
// *
// * @param levelNumber  the levelNumber.txt to be updated
// * @param gridPosition the position at which to update item
// * @param item the item to add at above position
// */
//void updateLevelFile(LevelData ld, Vector2D<int> gridPosition, LevelItem item) {
//
//  std::cout << "RS:[updateLevelFile]:" << std::endl;
//
//  const filesystem::path resPath = getResourcePath("levels");
//  std::string resourceFilename =
//      (resPath / ("level" + std::to_string(ld.levelNumber) + ".txt")).string();
//
//  std::string line;
//  std::fstream *myfile = ResourceManager::getInstance().openFile(resourceFilename, std::fstream::out | std::fstream::trunc);
//
//  int lineCounter = 0;
//  int colNumber = 0;
//
//  //std::cout << "RS:updateLevelFile:" << std::endl;
//
//  if (myfile->is_open()) {
//
//    *myfile << std::to_string(ld.rowCount) << std::endl;
//
//    *myfile << std::to_string(ld.colCount) << std::endl;
//
//    *myfile << std::to_string(ld.blockSize.x) << std::endl;
//
//    *myfile << std::to_string(ld.blockSize.y) << std::endl;
//
//    int i = 0;
//    int j = 0;
//    for (i = 0; i < ld.rowCount; i++)
//    {
//      for (j = 0; j < ld.colCount; j++)
//      {
//        *myfile << (char)ld.levelGrid[i][j];
//      }
//
//      if (i != ld.rowCount - 1)
//      {
//        *myfile << std::endl;
//      }
//
//      lineCounter++;
//    }
//
//    closeFile(resourceFilename);
//  } else {
//
//    // Create a new file.
//    std::cout << "Unable to open file \n";
//    std::cout << "Creating a new file \n";
//
//  }
//}
