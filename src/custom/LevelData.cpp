#include "custom/LevelData.hpp"

#include <filesystem>
#include <fstream>

#include "base/ResPath.hpp"
#include "base/ResourceManager.hpp"

// void loadLevel(TdLevelData *levelData, int level) {
//   levelData->levelGrid.clear();
//   levelData->blocks.clear();
//   levelData->enemyStartPositions.clear();

//   levelData->levelNumber = level;

//   const filesystem::path resPath = getResourcePath("Graverunner/levels");
//   std::string resourceFilename =
//       (resPath / ("level" + std::to_string(levelData->levelNumber) + ".txt"))
//           .string();

//   std::string line;
//   std::fstream *myfile = ResourceManager::getInstance().openFile(
//       resourceFilename, std::ios_base::in);
//   if (myfile->is_open()) {
//     int lineCounter = 0;
//     int colCounter = 0;
//     std::string x;
//     std::string y;
//     while (std::getline(*myfile, line)) {
//       if (lineCounter == 0) {
//         levelData->rowCount = std::stoi(line);
//         lineCounter++;
//         continue;
//       } else if (lineCounter == 1) {
//         levelData->colCount = std::stoi(line);

//         // // specify the default value to fill the vector elements
//         // levelData->levelGrid.resize(
//         //     levelData->rowCount,
//         //     std::vector<TdLevelItem>(levelData->colCount,
//         //     TdLevelItem::NONE));
//         // ;

//         lineCounter++;
//         continue;
//       } else if (lineCounter == 2) {
//         x = line;
//         lineCounter++;
//         continue;
//       } else if (lineCounter == 3) {
//         y = line;
//         lineCounter++;
//         continue;
//       }

//       levelData->blockSize = Vector2D<int>(std::stoi(x), std::stoi(y));

//       // Traverse the string
//       colCounter = 0;

//       for (auto &ch : line) {
//         auto data = TdBlockData();
//         if (ch == '1') {
//           data.block_Type = TdBlockType::PlainBlock;
//           data.blockNumber = ch;
//           levelData->levelGrid[lineCounter - 4][colCounter] =
//               TdLevelItem::TILE1;
//         } else if (ch == '2') {
//           data.block_Type = TdBlockType::PlainBlock;
//           data.blockNumber = ch;
//           levelData->levelGrid[lineCounter - 4][colCounter] =
//               TdLevelItem::TILE2;
//         } else if (ch == '3') {
//           data.block_Type = TdBlockType::PlainBlock;
//           data.blockNumber = ch;
//           levelData->levelGrid[lineCounter - 4][colCounter] =
//               TdLevelItem::TILE3;
//         } else if (ch == 'X') {
//           data.block_Type = TdBlockType::PlainBlock;
//           data.blockNumber = ch;
//           levelData->levelGrid[lineCounter - 4][colCounter] =
//               TdLevelItem::TILEX;
//         } else if (ch == 'Y') {
//           data.block_Type = TdBlockType::PlainBlock;
//           data.blockNumber = ch;
//           levelData->levelGrid[lineCounter - 4][colCounter] =
//               TdLevelItem::TILEY;
//         } else if (ch == 'Z') {
//           data.block_Type = TdBlockType::PlainBlock;
//           data.blockNumber = ch;
//           levelData->levelGrid[lineCounter - 4][colCounter] =
//               TdLevelItem::TILEZ;
//         } else if (ch == '.') {
//           data.block_Type = TdBlockType::NoBlock;
//           levelData->levelGrid[lineCounter - 4][colCounter] =
//               TdLevelItem::NOBLOCK;
//         } else if (ch == 'W') {
//           data.block_Type = TdBlockType::Wall;
//           levelData->levelGrid[lineCounter - 4][colCounter] =
//           TdLevelItem::WALL;
//         } else if (ch == 'K') {
//           data.block_Type = TdBlockType::Key;
//           levelData->levelGrid[lineCounter - 4][colCounter] =
//           TdLevelItem::KEY;
//         } else if (ch == 'E') {
//           // Enemy start position
//           data.block_Type = TdBlockType::NoBlock;
//           levelData->enemyStartPositions.push_back(
//               Vector2D<int>(colCounter, lineCounter - 4));
//           levelData->levelGrid[lineCounter - 4][colCounter] =
//               TdLevelItem::PATROLZOMBIE;
//         } else if (ch == 'F') {
//           // Follower Enemy start position
//           data.block_Type = TdBlockType::NoBlock;
//           levelData->followerEnemyStartPositions.push_back(
//               Vector2D<int>(colCounter, lineCounter - 4));
//           levelData->levelGrid[lineCounter - 4][colCounter] =
//               TdLevelItem::FOLLOWZOMBIE;
//         } else if (ch == 'P') {
//           data.block_Type = TdBlockType::NoBlock;
//           levelData->playerStartPosition =
//               Vector2D<int>(colCounter, lineCounter - 4);
//           levelData->levelGrid[lineCounter - 4][colCounter] =
//           TdLevelItem::JACK;
//         } else if (ch == 'G') {
//           data.block_Type = TdBlockType::Exit;
//           levelData->levelEndPosition =
//               Vector2D<int>(colCounter, lineCounter - 4);
//           levelData->levelGrid[lineCounter - 4][colCounter] =
//           TdLevelItem::EXIT;
//         }

//         levelData->blocks.push_back(data);
//         colCounter++;
//       }

//       lineCounter++;
//     }

//     ResourceManager::getInstance().closeFile(resourceFilename);
//   } else {
//     std::cout << "Unable to open level file at " << resourceFilename
//               << std::endl;
//   }
// }

// void updateCurrentLevel(TdLevelData *levelData, Vector2D<int> gridPosition,
//                         TdLevelItem item) {
//   // Update the Level
//   if (item != TdLevelItem::NONE) {
//     levelData->levelGrid[gridPosition.x][gridPosition.y] = item;

//     // std::cout << "EM:[After - updateCurrentLevel]:" << std::endl;

//     // Update the Level File
//     updateLevelFile(*levelData, gridPosition, item);
//   }
// }

/**
 * @brief Update the item in the current level.
 *
 * @param levelNumber  the levelNumber.txt to be updated
 * @param gridPosition the position at which to update item
 * @param item the item to add at above position
 */
// void updateLevelFile(TdLevelData ld, Vector2D<int> gridPosition,
//                      TdLevelItem item) {
//   std::cout << "RS:[updateLevelFile]:" << std::endl;

//   const filesystem::path resPath = getResourcePath("Graverunner/levels");
//   std::string resourceFilename =
//       (resPath / ("level" + std::to_string(ld.levelNumber) +
//       ".txt")).string();

//   std::string line;
//   std::fstream *myfile = ResourceManager::getInstance().openFile(
//       resourceFilename, std::fstream::out | std::fstream::trunc);

//   int lineCounter = 0;
//   int colNumber = 0;

//   // std::cout << "RS:updateLevelFile:" << std::endl;

//   if (myfile->is_open()) {
//     *myfile << std::to_string(ld.rowCount) << std::endl;

//     *myfile << std::to_string(ld.colCount) << std::endl;

//     *myfile << std::to_string(ld.blockSize.x) << std::endl;

//     *myfile << std::to_string(ld.blockSize.y) << std::endl;

//     int i = 0;
//     int j = 0;
//     for (i = 0; i < ld.rowCount; i++) {
//       for (j = 0; j < ld.colCount; j++) {
//         *myfile << (char)ld.levelGrid[i][j];
//       }

//       if (i != ld.rowCount - 1) {
//         *myfile << std::endl;
//       }

//       lineCounter++;
//     }

//     ResourceManager::getInstance().closeFile(resourceFilename);
//   } else {
//     // Create a new file.
//     std::cout << "Unable to open file \n";
//     std::cout << "Creating a new file \n";
//   }
// }
