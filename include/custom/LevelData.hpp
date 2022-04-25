#ifndef TD_LEVEL_DATA_HPP
#define TD_LEVEL_DATA_HPP

#include <iostream>
#include <map>
#include <vector>

#include "base/TinyMath.hpp"

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
  MAGICTOWER,
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
  ANTITANKMINE,
  BUSH1,
  BUSH2,
  BUSH3,
  FOREST1,
  GRASS1,
  GRASS2,
  GRASS3,
  GRASS4,
  STONE1,
  TREE1,
  TREE2,
  TREE3,
  TREE4,
  TREE5,
};

/**
 * @brief Represents data of a single Block in Tower Defense game.
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
 * @note Format:
 *   # rows of blocks
 *   # columns of blocks
 *   block width (pixels)
 *   block height (pixels)
 *   [array of blocks, each character maps to a specific type]
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

  // A vector of enemy possible paths.
  // Saves each path in a sparse format
  std::vector<std::vector<Vector2D<int>>> enemyPossiblePaths;

  // A vector of Level environment elements.
  std::vector<TdBlockData> levelEnvItems;
  std::vector<Vector2D<int>> levelEnvItemPositions;

  // Start and end positions of the path
  Vector2D<int> startPosition;
  Vector2D<int> endPosition;

  int rowCount;
  int colCount;
  Vector2D<int> blockSize;
};

/**
 * @brief Get the character that represents a particular item.
 *
 * @param item the item to get char of
 * @return std::string the string/char representation
 */
std::string getItemChar(TdLevelItem item);

/**
 * @brief Loads a numbered level file from filesystem into levelData.
 *
 * @param levelData [out] where to save the level
 * @param levelNum the level number, for looking up files in filesys to parse
 */
void loadLevel(TdLevelData* levelData, int levelNum);

/**
 * @brief Update the item in the current level during level editing.
 *
 * @param levelData the level data to update
 * @param gridPosition the position at which to update item
 * @param mousePosition the mouse position at which to update env item
 * @param item the item to add at above position
 */
void updateCurrentLevel(TdLevelData* levelData, Vector2D<int> gridPosition, Vector2D<int> mousePosition,
                        TdLevelItem item);

/**
 * @brief Update the item in the current level.
 *
 * @param ld the level data to update
 * @param gridPosition the position at which to update item
 * @param item the item to add at above position
 */
void updateLevelFile(TdLevelData ld, Vector2D<int> gridPosition,
                     TdLevelItem item);

#endif