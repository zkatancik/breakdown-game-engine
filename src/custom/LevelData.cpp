#include "custom/LevelData.hpp"

#include <filesystem>
#include <fstream>

#include "base/ResPath.hpp"
#include "base/ResourceManager.hpp"

void loadLevel(TdLevelData *levelData, int level) {
  levelData->levelGrid.clear();
  levelData->placableBlockGrid.clear();
  //levelData->blocks.clear();
  levelData->levelNumber = level;

  const filesystem::path resPath = getResourcePath("TD2D/Levels");
  std::string resourceFilename =
      (resPath / ("level" + std::to_string(levelData->levelNumber) + ".txt"))
          .string();

  std::string towerMapFilename =
      (resPath / ("level" + std::to_string(levelData->levelNumber) + "-TowerMap.txt"))
          .string();

  std::string line;
  std::string towerMapline;
  std::fstream *myfile = ResourceManager::getInstance().openFile(
      resourceFilename, std::ios_base::in);
  std::fstream *towerMapfile = ResourceManager::getInstance().openFile(
      towerMapFilename, std::ios_base::in);

  if (myfile->is_open() && towerMapfile->is_open()) {
    
    int lineCounter = 0;
    int colCounter = 0;
    std::string x;
    std::string y;

    while (std::getline(*myfile, line) && std::getline(*towerMapfile, towerMapline)) {
      if (lineCounter == 0) {
        levelData->rowCount = std::stoi(line);
        lineCounter++;
        continue;
      } else if (lineCounter == 1) {
        levelData->colCount = std::stoi(line);
        // Resize and fill with default level items
        levelData->levelGrid.resize(
            levelData->rowCount,
            std::vector<TdBlockData>(levelData->colCount));

        levelData->placableBlockGrid.resize(
            levelData->rowCount,
            std::vector<TdBlockData>(levelData->colCount));

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
      // Done reading metadata, parse & add level items

      levelData->blockSize = Vector2D<int>(std::stoi(x), std::stoi(y));
      colCounter = 0;
      char ch = 0;
      char tmch = 0;

      // Traverse the string
      for (auto idx = 0; idx < line.size() ; idx++) {
        ch = line[idx];
        tmch = towerMapline[idx];

        auto data = TdBlockData();
        auto towerPlacableData = TdBlockData();

        // Read Level File.
        if (ch == '.') {
          data.levelItemType = TdLevelItem::PLAINBLOCK;
          data.blockNumber = ch;
        } else if (ch == '1' || ch == '2' || ch == '3' || ch == '4' ||
                   ch == '5' || ch == '6') {
          data.levelItemType = TdLevelItem::PATHBLOCK;
          data.blockNumber = ch;
        } else if (ch == 'T') {
          data.levelItemType = TdLevelItem::ROCKTHROWER;
          data.blockNumber = ch;
        } else {
          std::cerr << "Error- Failed to parse character \"" << ch
                    << "\" in level file at (" << lineCounter << ","
                    << colCounter << ")" << std::endl;
        }

        // Read Tower Map.
        if (tmch == 'X') {
          data.isTowerPlacable = false;

          towerPlacableData.levelItemType = TdLevelItem::NOBLOCK;
          towerPlacableData.isTowerPlacable = false;
          towerPlacableData.blockNumber = ch;

        } else if (tmch == 'O') {
          data.isTowerPlacable = true;

          towerPlacableData.levelItemType = TdLevelItem::PLACETOWER;
          towerPlacableData.isTowerPlacable = true;
          towerPlacableData.blockNumber = ch;

        } else if (tmch == 'S') {
          // Enemy start position
          data.isTowerPlacable = false;
          
          towerPlacableData.levelItemType = TdLevelItem::START;
          towerPlacableData.isTowerPlacable = false;
          towerPlacableData.blockNumber = ch;

          levelData->startPosition = Vector2D<int>(colCounter, lineCounter - 4);

        } else if (tmch == 'E') {
          // Enemy end position
          data.isTowerPlacable = false;
          
          towerPlacableData.levelItemType = TdLevelItem::END;
          towerPlacableData.isTowerPlacable = false;
          towerPlacableData.blockNumber = ch;

          levelData->endPosition = Vector2D<int>(colCounter, lineCounter - 4);

        } else {
          std::cerr << "Error- Failed to parse character \"" << tmch
                    << "\" in tower map file at (" << lineCounter << ","
                    << colCounter << ")" << std::endl;
        }

        levelData->levelGrid[lineCounter - 4][colCounter] = data;
        levelData->placableBlockGrid[lineCounter - 4][colCounter] = towerPlacableData;

        colCounter++;
      }

      lineCounter++;
    }

    ResourceManager::getInstance().closeFile(resourceFilename);
    ResourceManager::getInstance().closeFile(towerMapFilename);
  } else {
    std::cerr << "Unable to open level file and/or tower map file at "
              << resourceFilename << " and " << towerMapFilename << std::endl;
  }
}
