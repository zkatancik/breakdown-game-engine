#ifndef TD_LEVEL_DATA_HPP
#define TD_LEVEL_DATA_HPP

#include <iostream>
#include <vector>
#include <map>

#include "base/TinyMath.hpp"

/**
 * @brief The types of blocks possible.
 *
 * - USE TdLevelItem instead. The enum is confusing and
 * a repetition of whatever in TdLevelItem.
 */
// enum class TdBlockType {
//   Plain = 0,
//   Path
// };

/**
 * @brief The types of items present in a level.
 * - All the items you see in the LevelFile.
 */
enum class TdLevelItem {
  NONE,
  NOBLOCK,
  PLAINBLOCK,
  PATHBLOCK0,
  PATHBLOCK1,
  PATHBLOCK2,
  PATHBLOCK3,
  PATHBLOCK4,
  PATHBLOCK5,
  PATHBLOCK6,
  PATHBLOCK7,
  PATHBLOCK8,
  PATHBLOCK9,
  PATHBLOCKA,
  PLACETOWER,
  ROCKTHROWER,
  START,
  END,
  SCORPIONS,
  WIZARD,
  OGRE,
  HELMETSWORDSMAN,
  HELMETOGRE,
  SWORDCAT,
  ETCAT,
  MOONOGRE,
  ETSHURIKEN,
  HELMETOGRESWORDSMAN,
};

/**
 * @brief Represents data of a single Block.
 * Can get additional granularity (e.g. for rendering) by storing info from the
 * level file into the various fields.
 */
struct TdBlockData {
  TdLevelItem levelItemType{TdLevelItem::NONE};
  std::string blockNumber;
  // If X then false, if O then true.
  bool isTowerPlacable;
};

/**
 * @brief Has the data read from Level file.
 *
 * TODO- write the file format here
 */
struct TdLevelData {
  int levelNumber{0};

  // Takes care of the BG tiles.
  std::vector<std::vector<TdBlockData>> levelGrid;

  // Will be modified in runtime.
  // Holds the towers and other placable blocks.
  std::vector<std::vector<TdBlockData>> placableBlockGrid;

  // A vector of enemy waves.
  // Saves each wave in a sparse format
  std::vector<std::map<TdLevelItem, int>> enemyWaves;

  Vector2D<int> startPosition;
  Vector2D<int> endPosition;

  int rowCount;
  int colCount;
  Vector2D<int> blockSize;
};

std::string getItemChar(TdLevelItem item);

/**
 * @brief Load Level file based on the level passed to the function.
 *
 * @param blockDataList levelData loaded from the file
 * @param level level number
 */
void loadLevel(TdLevelData *levelData, int levelNum);

void updateCurrentLevel(TdLevelData *levelData, Vector2D<int> gridPosition, TdLevelItem item);

void updateLevelFile(TdLevelData ld, Vector2D<int> gridPosition, TdLevelItem item);

#endif