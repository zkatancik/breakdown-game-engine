#ifndef TD_LEVELDATA_HPP
#define TD_LEVELDATA_HPP

#include <iostream>
#include <vector>

#include "base/TinyMath.hpp"

/**
 * @brief The types of blocks possible.
 */
enum class TdBlockType {
  Plain = 0,
  Path
};

/**
 * @brief The types of items present in a level.
 * - All the items you see in the LevelFile.
 */
enum class TdLevelItem {
  NONE,
  NOBLOCK,
  PLAINBLOCK,
  PATHBLOCK
};

/**
 * @brief Represents data of a single Block.
 * Can add color and more to be read from level file.
 */
struct TdBlockData {
  TdBlockType block_Type{TdBlockType::Plain};
  std::string blockNumber;
};

/**
 * @brief Has the data read from Level file.
 *
 * TODO- write the file format here
 */
struct TdLevelData {
  int levelNumber{0};

  std::vector<std::vector<TdLevelItem>> levelGrid;

  std::vector<TdBlockData> blocks;
  int rowCount;
  int colCount;
  Vector2D<int> blockSize;
};

/**
 * @brief Load Level file based on the level passed to the function.
 *
 * @param blockDataList levelData loaded from the file
 * @param level level number
 */
void loadLevel(TdLevelData *levelData, int levelNum);

/* TODO- add these back as needed
void updateCurrentLevel(TdLevelData *levelData,
                        Vector2D<int> gridPosition, TdLevelItem item);

void updateLevelFile(TdLevelData ld, Vector2D<int> gridPosition,
                     TdLevelItem item);
*/

#endif