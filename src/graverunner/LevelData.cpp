#include <filesystem>
#include <fstream>
#include "base/ResPath.hpp"
#include "base/ResourceManager.hpp"
#include "graverunner/LevelData.hpp"

void loadLevel(GraveRunnerLevelData *levelData, int level) {
  levelData->levelGrid.clear();
  levelData->blocks.clear();
  levelData->enemyStartPositions.clear();

  levelData->levelNumber = level;

  const filesystem::path resPath = getResourcePath("Graverunner/levels");
  std::string resourceFilename =
      (resPath / ("level" + std::to_string(levelData->levelNumber) + ".txt")).string();

  std::string line;
  std::fstream *myfile = ResourceManager::getInstance().openFile(resourceFilename, std::ios_base::in);
  if (myfile->is_open()) {
    int lineCounter = 0;
    int colCounter = 0;
    std::string x;
    std::string y;
    while (std::getline(*myfile, line)) {
      if (lineCounter == 0) {
        levelData->rowCount = std::stoi(line);
        lineCounter++;
        continue;
      } else if (lineCounter == 1) {
        levelData->colCount = std::stoi(line);

        // specify the default value to fill the vector elements
        levelData->levelGrid.resize(levelData->rowCount, std::vector<GraveRunnerLevelItem>(levelData->colCount, GraveRunnerLevelItem::NONE));;

        lineCounter++;
        continue;
      } else if (lineCounter == 2) {
        x = line;
        lineCounter++;
        continue;
      } else if (lineCounter == 3) {
        y = line;
        lineCounter++;
        continue;
      }

      levelData->blockSize = Vector2D<int>(std::stoi(x), std::stoi(y));

      // Traverse the string
      colCounter = 0;

      for (auto &ch : line) {
        auto data = GraveRunnerBlockData();
        if (ch == '1') {
          data.block_Type = GraveRunnerBlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 4][colCounter] = GraveRunnerLevelItem::TILE1;
        } else if (ch == '2') {
          data.block_Type = GraveRunnerBlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 4][colCounter] = GraveRunnerLevelItem::TILE2;
        } else if (ch == '3') {
          data.block_Type = GraveRunnerBlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 4][colCounter] = GraveRunnerLevelItem::TILE3;
        } else if (ch == 'X') {
          data.block_Type = GraveRunnerBlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 4][colCounter] = GraveRunnerLevelItem::TILEX;
        } else if (ch == 'Y') {
          data.block_Type = GraveRunnerBlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 4][colCounter] = GraveRunnerLevelItem::TILEY;
        } else if (ch == 'Z') {
          data.block_Type = GraveRunnerBlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 4][colCounter] = GraveRunnerLevelItem::TILEZ;
        } else if (ch == '.') {
          data.block_Type = GraveRunnerBlockType::NoBlock;
          levelData->levelGrid[lineCounter - 4][colCounter] = GraveRunnerLevelItem::NOBLOCK;
        } else if (ch == 'W') {
          data.block_Type = GraveRunnerBlockType::Wall;
          levelData->levelGrid[lineCounter - 4][colCounter] = GraveRunnerLevelItem::WALL;
        } else if (ch == 'K') {
          data.block_Type = GraveRunnerBlockType::Key;
          levelData->levelGrid[lineCounter - 4][colCounter] = GraveRunnerLevelItem::KEY;
        } else if (ch == 'E') {
          // Enemy start position
          data.block_Type = GraveRunnerBlockType::NoBlock;
          levelData->enemyStartPositions.push_back(
              Vector2D<int>(colCounter, lineCounter - 4));
          levelData->levelGrid[lineCounter - 4][colCounter] = GraveRunnerLevelItem::PATROLZOMBIE;
        } else if (ch == 'F') {
          // Follower Enemy start position
          data.block_Type = GraveRunnerBlockType::NoBlock;
          levelData->followerEnemyStartPositions.push_back(
              Vector2D<int>(colCounter, lineCounter - 4));
          levelData->levelGrid[lineCounter - 4][colCounter] = GraveRunnerLevelItem::FOLLOWZOMBIE;
        } else if (ch == 'P') {
          data.block_Type = GraveRunnerBlockType::NoBlock;
          levelData->playerStartPosition =
              Vector2D<int>(colCounter, lineCounter - 4);
          levelData->levelGrid[lineCounter - 4][colCounter] = GraveRunnerLevelItem::JACK;
        } else if (ch == 'G') {
          data.block_Type = GraveRunnerBlockType::Exit;
          levelData->levelEndPosition =
              Vector2D<int>(colCounter, lineCounter - 4);
          levelData->levelGrid[lineCounter - 4][colCounter] = GraveRunnerLevelItem::EXIT;
        }

        levelData->blocks.push_back(data);
        colCounter++;
      }

      lineCounter++;
      
    }
    
    ResourceManager::getInstance().closeFile(resourceFilename);
  } else {
    std::cout << "Unable to open level file at " << resourceFilename << std::endl;
  }
}

void updateCurrentLevel(GraveRunnerLevelData *levelData, 
                        Vector2D<int> gridPosition,
                        GraveRunnerLevelItem item) {
  // Update the Level
  if (item != GraveRunnerLevelItem::NONE) {
    levelData->levelGrid[gridPosition.x][gridPosition.y] = item;

    // Update the Level File
    updateLevelFile(*levelData, gridPosition, item);
  }
}

/**
 * @brief Update the item in the current level.
 *
 * @param levelNumber  the levelNumber.txt to be updated
 * @param gridPosition the position at which to update item
 * @param item the item to add at above position
 */
void updateLevelFile(GraveRunnerLevelData ld, Vector2D<int> gridPosition, GraveRunnerLevelItem item) {
  const filesystem::path resPath = getResourcePath("Graverunner/levels");
  std::string resourceFilename =
      (resPath / ("level" + std::to_string(ld.levelNumber) + ".txt")).string();

  std::string line;
  std::fstream *myfile = ResourceManager::getInstance().openFile(resourceFilename, std::fstream::out | std::fstream::trunc);

  int lineCounter = 0;
  int colNumber = 0;

  if (myfile->is_open()) {

    *myfile << std::to_string(ld.rowCount) << std::endl;

    *myfile << std::to_string(ld.colCount) << std::endl;

    *myfile << std::to_string(ld.blockSize.x) << std::endl;

    *myfile << std::to_string(ld.blockSize.y) << std::endl;

    int i = 0;
    int j = 0;
    for (i = 0; i < ld.rowCount; i++)
    {
      for (j = 0; j < ld.colCount; j++)
      {
        *myfile << (char)ld.levelGrid[i][j];
      }

      if (i != ld.rowCount - 1)
      {
        *myfile << std::endl;
      }

      lineCounter++;
    }

    ResourceManager::getInstance().closeFile(resourceFilename);
  } else {

    // Create a new file.
    std::cout << "Unable to open file \n";
    std::cout << "Creating a new file \n";

  }
}
