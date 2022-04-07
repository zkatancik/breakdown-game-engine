#include <filesystem>
#include <fstream>
#include "base/ResPath.hpp"
#include "base/ResourceManager.hpp"
#include "graverunner/LevelData.hpp"

void loadLevel(LevelData *levelData, int level) {
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
        levelData->levelGrid.resize(levelData->rowCount, std::vector<LevelItem>(levelData->colCount, LevelItem::NONE));;

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
        auto data = BlockData();
        if (ch == '1') {
          data.block_Type = BlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::TILE1;
        } else if (ch == '2') {
          data.block_Type = BlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::TILE2;
        } else if (ch == '3') {
          data.block_Type = BlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::TILE3;
        } else if (ch == 'X') {
          data.block_Type = BlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::TILEX;
        } else if (ch == 'Y') {
          data.block_Type = BlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::TILEY;
        } else if (ch == 'Z') {
          data.block_Type = BlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::TILEZ;
        } else if (ch == '.') {
          data.block_Type = BlockType::NoBlock;
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::NOBLOCK;
        } else if (ch == 'W') {
          data.block_Type = BlockType::Wall;
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::WALL;
        } else if (ch == 'K') {
          data.block_Type = BlockType::Key;
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::KEY;
        } else if (ch == 'E') {
          // Enemy start position
          data.block_Type = BlockType::NoBlock;
          levelData->enemyStartPositions.push_back(
              Vector2D<int>(colCounter, lineCounter - 4));
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::PATROLZOMBIE;
        } else if (ch == 'F') {
          // Follower Enemy start position
          data.block_Type = BlockType::NoBlock;
          levelData->followerEnemyStartPositions.push_back(
              Vector2D<int>(colCounter, lineCounter - 4));
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::FOLLOWZOMBIE;
        } else if (ch == 'P') {
          data.block_Type = BlockType::NoBlock;
          levelData->playerStartPosition =
              Vector2D<int>(colCounter, lineCounter - 4);
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::JACK;
        } else if (ch == 'G') {
          data.block_Type = BlockType::Exit;
          levelData->levelEndPosition =
              Vector2D<int>(colCounter, lineCounter - 4);
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::EXIT;
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

